#pragma once

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

void test();



class CCanvas : public Gtk::DrawingArea
{
public:
    CCanvas()
        {

        }

    virtual ~CCanvas() { };

protected:
    // Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

}; // CCanvas

int runWindow();