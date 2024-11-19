/**
 * @file SpartyBootsView.hpp
 * @author tiend
 *
 *
 */

#ifndef CONVEYORVIEW_H
#define CONVEYORVIEW_H
#include "SpartyBoots.hpp"

/**
 * View of the program
 */
class SpartyBootsView : public wxWindow {
private:
    /// to show that gae shoud exit
    bool mClose = false;
    /// The game object
    SpartyBoots mSpartyBoots;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    /// Any item we are currently dragging
    std::shared_ptr<IDraggable> mGrabbedItem;

public:
    /**
     * construct mSpartyBoots with wxWindow parent
     */
    SpartyBootsView(): mSpartyBoots(this) {};
    void Initialize(wxFrame *parent);
    void OnPaint(wxPaintEvent &event);
    void OnLeftDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnLevel1(wxCommandEvent &event);
    void OnLevel2(wxCommandEvent &event);
    void OnLevel3(wxCommandEvent &event);
    void OnLevel4(wxCommandEvent &event);
    void OnLevel5(wxCommandEvent &event);
    void OnLevel6(wxCommandEvent &event);
    void OnLevel7(wxCommandEvent &event);
    void OnLevel8(wxCommandEvent &event);
    void OnTimer(wxTimerEvent &event);
    void OnOrGate(wxCommandEvent &event);
    void OnAndGate(wxCommandEvent &event);
    void OnNotGate(wxCommandEvent &event);
    void OnSRFlipFlop(wxCommandEvent &event);
    void OnDFlipFlop(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    /**
     * stops the timer
     */
    void Stop()
    {
        mTimer.Stop();
    }
};

#endif // CONVEYORVIEW_H
