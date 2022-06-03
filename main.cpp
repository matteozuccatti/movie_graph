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



    Node n1,n2; 
    std::vector<Node> act = {n1,n2};
    //runWindow(act); 


    testEuler();

    return 0; 
}
























