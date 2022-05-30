#include "../include/canvas.h"



void test();



bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
cr->set_source_rgb(1.,.5,.0);
cr->set_line_width(3);

cr->move_to( 11, 11);
cr->line_to(111,111);
cr->stroke();

return true;
}

int runWindow(){
    int argc = 0; 
    char** argv = {}; 
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.resize(800,600);
    window.set_title("Cairo tutorial C++");

    CCanvas area;
    window.add(area);
    area.show();

    return app->run(window);
    //return app->run(window);
}