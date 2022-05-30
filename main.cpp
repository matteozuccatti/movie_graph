#include "SQL_parser.hh"
#include <iostream>
#include "graph_drawer.hh"
#include "canvas.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>



int main(int argc, char** argv){
/*
    std::vector<std::pair<std::string, std::string>> movieVec; 
    movieParser(movieVec);

    std::vector<Actor> actors;
    actorParser(movieVec,actors);
    movieCounter(actors);
    printActorMap(actors);
*/
/*
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
*/
/*
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.resize(800,600);
    window.set_title("Cairo tutorial C++");

    CCanvas area;
    window.add(area);
    area.show();

    return app->run(window);
*/
    runWindow();
    //testFunction();

    return 0; 
}
























