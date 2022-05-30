#include "../include/canvas.h"


bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    Gtk::Allocation allocation{ get_allocation() };
    auto const width { (double)allocation.get_width() };
    auto const height{ (double)allocation.get_height() };

    cr->set_source_rgb(1.,.5,.0);
    cr->set_line_width(3);

    // line crossing the whole window
    cr->move_to(    0,      0);
    cr->line_to(width, height);
    cr->stroke();

    // circle gray
    cr->set_source_rgb(.7,.7,.7);
    cr->arc(width/2, height/2, 50, 0, 2*M_PI);
    cr->fill();

    // circle gray
    cr->set_source_rgb(1,.1,.0);
    cr->arc(0, 0, 100, 0, 2*M_PI);
    cr->fill();

    // circle gray
    cr->set_source_rgb(1,.1,.0);
    cr->arc(width, height, 100, 0, 2*M_PI);
    cr->fill();
    

    return true;
}

int runWindow()
{
    int argc = 0; 
    char** argv = {}; 
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.fullscreen();
    window.set_title("Cairo tutorial C++");

    CCanvas area;
    window.add(area);
    area.show();

    return app->run(window);
}