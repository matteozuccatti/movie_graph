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



    Node n1,n2,n3,n4; 
    n1.x0 = 350;    n1.x = Vector(100,100);
    n2.x0 = 350;    n2.x = Vector(-100,0);
    n3.x0 = 450;    n3.x = Vector(100,-200); 
    n4.x0 = 500;    n4.x = Vector(100,0);


    std::vector<Node> act = {n1,n2,n3,n4};
    runWindow(act); 


    //testEuler();

    return 0; 
}
























