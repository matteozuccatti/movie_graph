#include "SQL_parser.hh"
#include <iostream>
#include "canvas.h"
#include "actors.hh"



int main(int argc, char** argv){

    //std::cout << "Main Actor :" << argv[1] << "\n";

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);
    printActorMap(actors);

    //runWindow();
    return 0; 
}
























