/**
 * @file MainFrame.hpp
 * @author Alex Mueller
 *
 *
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "SpartyBootsView.hpp"

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    SpartyBootsView* mSpartyBootsView;
    void OnAbout(wxCommandEvent &event);
    void OnClose(wxCloseEvent& event);
    /**
     * sets Close to true
     * @param event
     */
    void OnExit(wxCommandEvent &event)
    {
        Close(true);
    }

public:
    void Initialize();
};

#endif // MAINFRAME_H
