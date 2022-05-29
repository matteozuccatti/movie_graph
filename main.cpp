#include "SQL_parser.hh"
#include <iostream>

int main(){

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);
    movieCounter(actors);
    printActorMap(actors);

    return 0; 
}
























