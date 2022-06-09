#pragma once

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "actors.hh"
#include <vector>
#include "typesNmath.h"

using CairoCtx = Cairo::RefPtr<Cairo::Context> const &;


/*
inline bool operator == (SPoint const & p1, SPoint const & p2)
{
    return (p1.x==p2.x) && (p1.y==p2.y);
}

inline bool operator != (SPoint const & p1, SPoint const & p2)
{
    return !(p1==p2);
}

inline SPoint operator - (SPoint const & p1, SPoint const & p2)
{
    return {p1.x-p2.x, p1.y-p2.y};
}

inline SPoint operator + (SPoint const & p1, SPoint const & p2)
{
    return {p2.x+p1.x, p2.y+p1.y};
}

inline SPoint operator / (SPoint const & p, double const & d)
{
    return {p.x/d, p.y/d};
}

inline SPoint operator * (SPoint const & p, double const & d)
{
    return {p.x*d, p.y*d};
}
*/

inline void LineWidth( CairoCtx cr, SLineWidth const & w, double const & s=1 )
        {
        cr->set_line_width(w.w / ((s==0)?1:s));
        }

inline void Color( CairoCtx cr, SColor const & c )
        {
        cr->set_source_rgb( c.r, c.g, c.b );
        }

inline void Color( CairoCtx cr, SColor const & c, double const & a )
        {
        cr->set_source_rgba( c.r, c.g, c.b, a );
        }

inline void Color( CairoCtx cr, double const & r, double const & g, double const & b )
        {
        cr->set_source_rgb( r, g, b );
        }

inline void Color( CairoCtx cr, double const & r, double const & g, double const & b, double const & a )
        {
        cr->set_source_rgba( r, g, b, a );
        }

template<typename P>
    void MoveTo(CairoCtx cr, P const & tPoint)
        {
        cr->move_to(tPoint.x, tPoint.y);
        }

template<typename P>
    void LineTo(CairoCtx cr, P const & tPoint)
        {
        cr->line_to(tPoint.x, tPoint.y);
        }

inline void Line(CairoCtx cr, SLine const & tLine )
        {
        MoveTo(cr, tLine.a);
        LineTo(cr, tLine.b);
        cr->stroke();
        }

template<typename C>
    void LineStrip(CairoCtx cr, C const & tPoints )
        {
        bool b{true};
        for ( auto const & a:tPoints )
            {
            if (b)
                {
                MoveTo(cr, a);
                b = false;
                }
            else
                {
                LineTo(cr, a);
                }
            }
        cr->stroke();
        }

template<typename P>
    void Circle(CairoCtx cr, P const & tPoint, double const & dRadius )
        {
        cr->arc(tPoint.x, tPoint.y, dRadius, 0, 2*M_PI);
        cr->fill();
        }

template<typename P>
    void Ring(CairoCtx cr, P const & tPoint, double const & dRadius )
        {
        cr->arc(tPoint.x, tPoint.y, dRadius, 0, 2*M_PI);
        cr->stroke();
        }

template<typename P, typename S>
    void Rectangle(CairoCtx cr, P const & tPoint, S const & tSize )
        {
        cr->rectangle(tPoint.x, tPoint.y, tSize.x, tSize.y);
        cr->fill();
        }

template<typename P, typename S>
    void Frame(CairoCtx cr, P const & tPoint, S const & tSize )
        {
        cr->rectangle(tPoint.x, tPoint.y, tSize.x, tSize.y);
        cr->stroke();
        }

SPoint draw_text(CairoCtx cr,
                 SPoint const & pos,
                 std::string const & crsText, 
                 double const & dScale = 1.0,
                 bool const & label = false);







class CCanvas : public Gtk::DrawingArea
{
public:
    CCanvas()
        {
            add_events(Gdk::BUTTON_PRESS_MASK | Gdk::SCROLL_MASK | Gdk::SMOOTH_SCROLL_MASK);
            add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
            add_events(Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
            add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);

            m_fSlot[0]         = sigc::bind(sigc::mem_fun(*this, &CCanvas::updateGraph), 0);
            m_afConnections[0] = Glib::signal_timeout().connect(m_fSlot[0], 50);
        }

    virtual ~CCanvas() 
        { 
            m_afConnections[0].disconnect();
        };

    std::vector<Node> nodes;

protected:
    // Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_scroll_event(GdkEventScroll *event) override;
    bool on_button_press_event(GdkEventButton * event) override;
    bool on_motion_notify_event(GdkEventMotion *event) override;
    bool on_button_release_event(GdkEventButton* release_event) override;

    
    double   m_dScale       { 1.0 };
    SPoint   m_tShift       { .0,.0 };
    SPoint   m_tEventPress  { .0,.0 };
    SPoint   m_tShiftStart  { .0,.0 };

    SPoint   m_tMousePos;
    SColor   m_tMouseColor{ .5,.5,.5 };

    // -----------------------------------------------------------------

    // animation
    bool             m_Animate{true};
    sigc::slot<bool> m_fSlot[1];
    sigc::connection m_afConnections[1];

    bool updateGraph(int tick); 


}; // CCanvas

int runWindow();