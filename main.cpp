#include "SQL_parser.hh"
#include <iostream>

int main(){

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::map<std::string, std::vector<std::string>> actorMap;
    actorParser(movieVec,actorMap);

    //std::cout << movieVec[0].first << " || " << movieVec[0].second << std::endl;

    return 0; 
}
























