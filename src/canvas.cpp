#include "../include/canvas.h"



bool CCanvas::on_button_press_event(GdkEventButton *event){
    m_tMouseColor = { .0,.0,.9 };
    if (event->type == GDK_BUTTON_PRESS ){
        m_tEventPress = *event;
        m_tShiftStart = m_tShift;
    }

    queue_draw();
    return true;
}
    
bool CCanvas::on_motion_notify_event(GdkEventMotion *event){
    m_tMousePos = (*event - m_tShift)/m_dScale;

    if ( event->type & GDK_MOTION_NOTIFY  && event->state & GDK_BUTTON3_MASK )
        m_tShift = m_tShiftStart - (m_tEventPress - *event);
    
    queue_draw();
    return true;
}
    
bool CCanvas::on_button_release_event(GdkEventButton* event){
    queue_draw();
    return true;
}
    
bool CCanvas::on_scroll_event(GdkEventScroll *event){
    if ( event->delta_y>0 )
        m_tMouseColor = { .9,.0,.0 };
    else
        m_tMouseColor = { .0,.9,.0 };

    SPoint const p0{ (*event - m_tShift)/m_dScale };
    m_dScale *= (event->delta_y>0)?.9:1.1; if (m_dScale<.01) m_dScale=.01;
    SPoint const p1{ (*event - m_tShift)/m_dScale };
    m_tShift -= (p0-p1)*m_dScale;

    queue_draw();
    return true;
}

bool CCanvas::updateGraph(int tick){

    updateLayout(nodes);


    queue_draw();
    return true;
}

bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    
    // ---------------------------------------------------------
    
    Cairo::Matrix matrix(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    matrix.scale(m_dScale,m_dScale);
    matrix.translate(m_tShift.x/m_dScale, m_tShift.y/m_dScale);
    cr->transform(matrix);

    Gtk::Allocation allocation{ get_allocation() };
    auto const width { (double)allocation.get_width() };
    auto const height{ (double)allocation.get_height() };
    Vector origin = Vector(width/2, height/2);
    

    for(std::vector<Node>::iterator it=nodes.begin(); it!=nodes.end(); it++){
        // Normal nodes 
        // circle orange
        cr->set_source_rgb(1.,.5,.0);
        cr->arc(origin.getX()+it->x.getX(),
                origin.getY()-it->x.getY(),
                it->size, 0, 2*M_PI);
        cr->fill();

        // line 
        cr->set_source_rgb(1.,.5,.0);
        cr->set_line_width(2);
        cr->move_to(origin.getX(), origin.getY());
        cr->line_to(origin.getX()+it->x.getX(),
                    origin.getY()-it->x.getY());
        cr->stroke();
        
    }
    
    cr->set_source_rgb(.7,.7,.7);
    cr->arc(origin.getX(), origin.getY(),100, 0, 2*M_PI);
    cr->fill();
    
    return true;
}

int runWindow()
{
    int argc = 0; 
    char** argv = {}; 
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.set_default_size(1920,1080);
    window.set_title("Actors graph plot");

    CCanvas area;
    area.nodes = get_sample_vector_nodes();

    window.add(area);
    area.show();

    return app->run(window);
}