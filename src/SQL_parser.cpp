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
    res = mysql_perform_query(con, "select movie_id,title from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_name = \"Johnny Depp\"));");

    std::cout << ("\nMovie list:\n") << std::endl;

    while ((row = mysql_fetch_row(res)) != NULL){
        // the below row[] parametes may change depending on the size of the table and your objective
        std::cout.width(7); std::cout << std::right << row[0]; 
        std::cout << " | "; 
        std::cout.width(25); std::cout << std::left << row[1];
        std::cout << std::endl;

        movieVec.push_back(std::make_pair(row[0],row[1]));
    }

    // clean up the database result
    mysql_free_result(res);
    // close database connection
    mysql_close(con);

    std::cout << " ------------------------------------------------------\n";
}


void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::map<std::string, std::vector<std::string>> &actorMap){

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

    const char *sql_query1 = "select all person_name from person where person_id in (select person_id from movie_cast where movie_id in (\"";
    const char *sql_query2 = "\"));";

    for(int i=0; i<movieVec.size(); i++){

        const char *movie_id = movieVec[i].first.c_str(); 
        char sql_query_tmp[250];
        std::strcpy(sql_query_tmp,sql_query1); 
        std::strcat(sql_query_tmp,movie_id); 
        std::strcat(sql_query_tmp,sql_query2); 

        const char *sql_query = sql_query_tmp; 

        res = mysql_perform_query(con, sql_query);

        std::cout << ("\nActors list: ") << movieVec[i].second.c_str() << std::endl;

        while ((row = mysql_fetch_row(res)) != NULL){
            // the below row[] parametes may change depending on the size of the table and your objective
            std::cout.width(40); std::cout << std::left << row[0]; 
            std::cout << std::endl;

            //movieVec.push_back(std::make_pair(row[0],row[1]));
        }
    }

    // clean up the database result
    mysql_free_result(res);
    // close database connection
    mysql_close(con);

}