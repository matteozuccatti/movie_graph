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

    Actor(std::string actorName_, std::string actorId_)
    {
        this->actorId =actorId_; 
        this->actorName =actorName_;
    }

    std::string actorId = "";
    std::string actorName = ""; 
    std::vector<std::string> commonMovies = {}; 
    int commonMovies_number = 0; 
    int allMovies = 0; 

    bool operator==(const Actor &a) const {
        return(this->actorId == a.actorId);
    }

};

MYSQL* mysql_connection_setup(struct connection_details mysql_details);
MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query);

void movieParser(std::vector<std::pair<std::string, std::string>> &movieVec);
void actorParser(std::vector<std::pair<std::string, std::string>> &movieVec,
                 std::vector<Actor> &actors);
void movieCounter(std::vector<Actor> &actors);
void printActorMap(std::vector<Actor> &actors);