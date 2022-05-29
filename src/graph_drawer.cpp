#include "../include/CImg.h"
#include "../include/graph_drawer.hh"

using namespace cimg_library;

void testFunction(){
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
}