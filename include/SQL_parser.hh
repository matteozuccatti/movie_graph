#pragma once

#include <iostream>
#include <iomanip>
#include <mysql/mysql.h>  //usr/includes/mariadb/mysql.h
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <map>


struct connection_details
{
    const char *server, *user, *password, *database;
};

class Actor{
public:
    std::string actorName = ""; 
    std::vector<std::string> commonMovies = {}; 
    int allMovies = 0; 
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details);
MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query);

void movieParser(std::vector<std::pair<std::string, std::string>> &movieVec);
void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::map<std::string, Actor> &actorMap);

void printActorMap(std::map<std::string, Actor> &actorMap);