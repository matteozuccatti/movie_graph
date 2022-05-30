#include "SQL_parser.hh"
#include <iostream>
#include "canvas.h"




int main(int argc, char** argv){

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);
    movieCounter(actors);
    //printActorMap(actors);


    runWindow();

    return 0; 
}
























