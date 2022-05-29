#include "SQL_parser.hh"
#include <iostream>

int main(){

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::map<std::string, Actor> actorMap;
    actorParser(movieVec,actorMap);
    
    printActorMap(actorMap);

    return 0; 
}
























