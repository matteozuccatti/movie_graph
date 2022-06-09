#include "SQL_parser.hh"
#include <iostream>
#include "canvas.h"
#include "actors.hh"



int main(int argc, char** argv){

    //std::cout << "Main Actor :" << argv[1] << "\n";

    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);
    moviePrinter(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);
    printActorMap(actors);

    //std::vector<Node> nodes(MAX_ACTORS);
    // actorToNodes(actors,nodes);
    
    runWindow();
    return 0; 
}
























