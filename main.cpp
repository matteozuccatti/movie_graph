#include "SQL_parser.hh"
#include <iostream>
#include "canvas.h"
#include "actors.hh"



int main(int argc, char** argv){

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);
    //printActorMap(actors);

    std::vector<Actor>  act = testFunction();
    printActorVec(act);
    actorComputeForces(act);
    printActorVec(act);

    runWindow(act);


    return 0; 
}
























