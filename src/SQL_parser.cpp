//https://www.databasestar.com/sample-database-movies/

#include "../include/SQL_parser.hh"

/*
    Setup connection with a given SQL file 
*/
MYSQL* mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL); // mysql instance
    
    //connect database
    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)){
        std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1); 
    }

    return connection;
}

/*
    Exectue a given query and output an array of selected values 
*/
MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query){
    //send query to db
    if(mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }

    return mysql_use_result(connection);
}

void movieParser(std::vector<std::pair<std::string, std::string>> &movieVec){

    MYSQL *con;	// the connection
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    struct connection_details mysqlD;
    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "root"; // user
    mysqlD.password = "1L0ck3D97"; // the password for the database
    mysqlD.database = "movies";	// the databse

    // connect to the mysql database
    con = mysql_connection_setup(mysqlD);

    // get the results from executing commands
    res = mysql_perform_query(con, "select movie_id,title from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_name = \"Leonardo DiCaprio\"));");

    std::cout << ("\nMovie list:\n") << std::endl;

    while ((row = mysql_fetch_row(res)) != NULL){
        movieVec.push_back(std::make_pair(row[0],row[1]));
    }

    // clean up the database result
    mysql_free_result(res);
    // close database connection
    mysql_close(con);
}


void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::vector<Actor> &actors){

    MYSQL *con;	// the connection
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    struct connection_details mysqlD;
    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "root"; // user
    mysqlD.password = "1L0ck3D97"; // the password for the database
    mysqlD.database = "movies";	// the databse

    // connect to the mysql database
    con = mysql_connection_setup(mysqlD);

    const char *sql_query1 = "select all person_name,person_id from person where person_id in (select person_id from movie_cast where movie_id in (\"";
    const char *sql_query2 = "\"));";

     std::vector<Actor>::iterator it = actors.begin(); 
     std::string actorName, actorId;

    for(int i=0; i<movieVec.size(); i++){

        const char *movie_id = movieVec[i].first.c_str(); 
        char sql_query_tmp[250];
        std::strcpy(sql_query_tmp,sql_query1); 
        std::strcat(sql_query_tmp,movie_id); 
        std::strcat(sql_query_tmp,sql_query2); 

        const char *sql_query = sql_query_tmp; 

        res = mysql_perform_query(con, sql_query);

        while ((row = mysql_fetch_row(res)) != NULL){
            actorName = row[0];
            actorId   = row[1];
            Actor act(actorName, actorId); 

            it = std::find(actors.begin(), actors.end(), act);
            if(it==actors.end()){
                // New actor
                act.commonMovies.push_back(movieVec[i].second);
                actors.push_back(act);
            }else{
                // Exsistent
                it->commonMovies.push_back(movieVec[i].second);
            }
        }
    }
    // clean up the database result
    mysql_free_result(res);
    // close database connection
    mysql_close(con);
}

void movieCounter(std::vector<Actor> &actors){

    // Initialize SQL connection 
    MYSQL *con;	// the connection
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    struct connection_details mysqlD;
    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "root"; // user
    mysqlD.password = "1L0ck3D97"; // the password for the database
    mysqlD.database = "movies";	// the databse

    // connect to the mysql database
    con = mysql_connection_setup(mysqlD);

    // SQL query
    const char *sql_query1 = "select movie_id from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_id = \"";
    const char *sql_query2 = "\"));"; 

    std::vector<Actor>::iterator it = actors.begin(); 
    while(it != actors.end()){

        const char *actorId = it->actorId.c_str(); 
        char sql_query_tmp[250];
        std::strcpy(sql_query_tmp,sql_query1); 
        std::strcat(sql_query_tmp,actorId); 
        std::strcat(sql_query_tmp,sql_query2); 

        const char *sql_query = sql_query_tmp; 
        res = mysql_perform_query(con, sql_query);

        while ((row = mysql_fetch_row(res)) != NULL){
            it->allMovies++;
        }
        it->commonMovies_number = it->commonMovies.size();
        it++; 
    }
}

void printActorMap(std::vector<Actor> &actors){

    std::sort(actors.begin(), actors.end());

    std::vector<Actor>::iterator it = actors.begin(); 
    while(it!=actors.end()){
        std::cout.width(26); std::cout<< std::left << it->actorName << "(";
        std::cout.width(2);  std::cout<< std::right << it->allMovies; 
        std::cout << ") | "; 

        for(int i=0; i<it->commonMovies.size(); i++){
            if(i!=0)
                std::cout.width(33); std::cout << "";
            std::cout << it->commonMovies[i] << "\n"; 
        }
        it++;
    }
}