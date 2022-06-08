#pragma once

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "actors.hh"
#include <vector>


struct SPoint
{
    SPoint() = default;
    SPoint(SPoint const & src) = default;
    template<typename T>
        SPoint(T const & x, T const & y) : x(x), y(y) {}
    template<typename T>
        SPoint(T const & t) : x(t.x), y(t.y) {}
    double x{0}, y{0};
    template<typename P>
        SPoint operator = (P const & p)
            {
            x = p.x;
            y = p.y;
            return *this;
            }
    template<typename P>
        SPoint operator -= (P const & p)
            {
            x -= p.x;
            y -= p.y;
            return *this;
            }
    template<typename P>
        SPoint operator += (P const & p)
            {
            x += p.x;
            y += p.y;
            return *this;
            }
};

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


struct SFleck
{
    double x{0}, y{0}, r{0};
    template<typename P>
        SFleck operator -= (P const & p)
            {
            x -= p.x;
            y -= p.y;
            return *this;
            }
    template<typename P>
        SFleck operator += (P const & p)
            {
            x += p.x;
            y += p.y;
            return *this;
            }
    template<typename P>
        SFleck operator = (P const & p)
            {
            x = p.x;
            y = p.y;
            return *this;
            }
};

struct SColor
{
    double r{0},g{0},b{0};
};

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