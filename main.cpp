// g++ main.cpp -o output -L/usr/include/mariadb/mysql -lmariadbclient
#include <iostream>
#include <iomanip>
#include <mysql/mysql.h> // /usr/includes/mariadb/mysql.h
#include <bits/stdc++.h>
#include <string>
#include <map>
//g++ main.cpp -o output -L/usr/include/mysql/mysql -lmysqlclient

struct connection_details
{
    const char *server, *user, *password, *database;
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL); // mysql instance
    
    //connect database
    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)){
        std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1); 
    }

    return connection;
}

// mysql_res = mysql result
MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query){
    //send query to db
    if(mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }

    return mysql_use_result(connection);
}

void printMap(std::map<MYSQL_ROW, int> &myMap){
    std::cout << "\n\n MAP PRINT : \n";

    std::map<MYSQL_ROW, int>::iterator it = myMap.begin(); 
    while(it!=myMap.end()){
        std::cout.width(35); std::cout << std::left << it->first; 
        std::cout << " | "; 
        std::cout.width(3); std::cout << std::right << it->second; 
    }
}

int main(int argc, char const *argv[])
{
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

        std::string name = "Johnny Depp";
        if(row[0]==  name){
            std::cout << "******************************************************************************\n";
        }

        /*
        // Insert in map if not present 
        actorsMap_it = actorsMap.find(row[0]);
        if(actorsMap_it==actorsMap.end()){
            actorsMap.insert({row[0],1});
        }else{
            actorsMap_it->second++;
        } 
        */

    }
    // clean up the database result
    mysql_free_result(res);
    
    // close database connection
    mysql_close(con);


    printMap(actorsMap);

    return 0;
}


//select movie_id, person_id from movie_cast where person_id =  (select person_id from person where person_name = "George Lucas");
//select title from movie where movie_id in (select movie_id from movie_cast where person_id =  (select person_id from person where person_name = "George Lucas"));