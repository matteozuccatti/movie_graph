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

void mainParse(){
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
    res = mysql_perform_query(con, "select person_name from person where person_id in (select person_id from movie_cast where movie_id in (select movie_id from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_name = \"Johnny Depp\"))));");

    std::cout << ("Database Output:\n") << std::endl;
    std::map<MYSQL_ROW, int> actorsMap; 
    std::map<MYSQL_ROW, int>::iterator actorsMap_it = actorsMap.begin();

    while ((row = mysql_fetch_row(res)) != NULL){
        // the below row[] parametes may change depending on the size of the table and your objective
        std::cout.width(35); std::cout << std::left << row[0]; 
        std::cout << std::endl;
    }
    // clean up the database result
    mysql_free_result(res);
    
    // close database connection
    mysql_close(con);

}

//select movie_id, person_id from movie_cast where person_id =  (select person_id from person where person_name = "George Lucas");
//select title from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_name = "George Lucas"));
