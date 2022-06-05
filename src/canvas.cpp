#include "../include/canvas.h"


bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    Gtk::Allocation allocation{ get_allocation() };
    auto const width { (double)allocation.get_width() };
    auto const height{ (double)allocation.get_height() };
  
    Vector origin = Vector(width/2, height/2);
    

    for(std::vector<Node>::iterator it=actors.begin(); it!=actors.end(); it++){
        // Normal nodes 
        // circle orange
        cr->set_source_rgb(1.,.5,.0);
        cr->arc(origin.getX()+it->x.getX(),
                origin.getY()-it->x.getY(),
                15, 0, 2*M_PI);
        cr->fill();

        // line 
        cr->set_source_rgb(1.,.5,.0);
        cr->set_line_width(3);
        cr->move_to(origin.getX(), origin.getY());
        cr->line_to(origin.getX()+it->x.getX(),
                    origin.getY()-it->x.getY());
        cr->stroke();
        
    }
    
    cr->set_source_rgb(.7,.7,.7);
    cr->arc(origin.getX(), origin.getY(),25, 0, 2*M_PI);
    cr->fill();

    //Orbit 
    cr->set_source_rgb(1.,.5,.0);
    cr->arc(origin.getX(), origin.getY(),350, 0, 2*M_PI);
    cr->stroke();



    
    return true;
}

int runWindow(std::vector<Node>  &actors)
{
    int argc = 0; 
    char** argv = {}; 
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.set_default_size(1920,1080);
    window.set_title("Actors graph plot");

    CCanvas area;
    area.actors = actors;
    compute_graph_layout(area.actors);

    window.add(area);
    area.show();

    return app->run(window);
}