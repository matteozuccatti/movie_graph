#pragma once

#include <iostream>
#include <iomanip>
#include <mysql/mysql.h>  //usr/includes/mariadb/mysql.h
#include <bits/stdc++.h>
#include <string>

struct connection_details
{
    const char *server, *user, *password, *database;
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details);
MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query);

void mainParse();