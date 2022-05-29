#include "SQL_parser.hh"
#include <iostream>
#include "CImg.h"

using namespace cimg_library;

int main(){
/*
    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);
    movieCounter(actors);
    printActorMap(actors);
*/

    unsigned int w = 300; 
    unsigned int h = 400; 
    const unsigned char blue[] = {0, 255,10}; 

    CImg<unsigned char> background(w,h,1,3, 255); 

    background.draw_circle(w/2, h/2, 100, blue); 

    CImgDisplay dsp(w,h,"hello",0);
    dsp.display(background);

    while(!dsp.is_closed()){


        dsp.wait();
    }
    std::getchar();


    return 0; 
}
























