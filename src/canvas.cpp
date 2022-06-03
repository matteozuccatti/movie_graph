#include "../include/canvas.h"


bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    Gtk::Allocation allocation{ get_allocation() };
    auto const width { (double)allocation.get_width() };
    auto const height{ (double)allocation.get_height() };
/*
    cr->set_source_rgb(1.,.5,.0);
    cr->set_line_width(3);

    // line crossing the whole window
    cr->move_to(width/4, height/4);
    cr->line_to(width/2, height/2);
    cr->stroke();

     // line crossing the whole window
    cr->move_to(width/2, height/2);
    cr->line_to(width-100, height/2);
    cr->stroke();


    // circle gray
    cr->set_source_rgb(1,.1,.0);
    cr->arc(width/4, height/4, 35, 0, 2*M_PI);
    cr->fill();

    // circle gray
    cr->set_source_rgb(1,.1,.0);
    cr->arc(width-100, height/2, 25, 0, 2*M_PI);
    cr->fill();

    cr->set_source_rgb(1.,.5,.0);
    cr->set_line_width(3);


    // circle gray
    cr->set_source_rgb(.7,.7,.7);
    cr->arc(width/2, height/2, 50, 0, 2*M_PI);
    cr->fill();
*/  
    Vector origin = Vector(width/2, height/2);
    for(int k=0; k<1000; k++){
        euler_method(actors);

        for(std::vector<Node>::iterator it=actors.begin(); it!=actors.end(); it++){
            // Normal nodes 
            // circle orange
            cr->set_source_rgb(1.,.5,.0);
            cr->arc(origin.getX()+it->x.getX(),
                    origin.getY()+it->x.getY(),
                    15, 0, 2*M_PI);
            cr->fill();

            // line 
            cr->set_source_rgb(1.,.5,.0);
            cr->set_line_width(3);
            cr->move_to(origin.getX(), origin.getY());
            cr->line_to(origin.getX()+it->x.getX(),
                        origin.getY()+it->x.getY());
            cr->stroke();
            
        }
        
        cr->set_source_rgb(.7,.7,.7);
        cr->arc(origin.getX(), origin.getY(),35, 0, 2*M_PI);
        cr->fill();
    }
    
    return true;
}

int runWindow(std::vector<Node>  &actors)
{
    int argc = 0; 
    char** argv = {}; 
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.set_default_size(1920,1080);
    window.set_title("Cairo tutorial C++");

    CCanvas area;
    area.actors = actors;

    window.add(area);
    area.show();

    return app->run(window);
}