#pragma once

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "actors.hh"

class CCanvas : public Gtk::DrawingArea
{
public:
    CCanvas()
        {

        }

    virtual ~CCanvas() { };
    std::vector<Actor> actors;
protected:
    // Override default signal handler:
    //bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) ;


}; // CCanvas

int runWindow(std::vector<Actor>  &actors);