/**
 * @file SpartyBootsView.cpp
 * @author tiend
 */

#include "pch.h"
#include "SpartyBootsView.hpp"
#include <string>
#include <vector>
#include <wx/dcbuffer.h>
#include "AndGate.hpp"
#include "ids.hpp"
#include "NotGate.hpp"
#include "OrGate.hpp"
#include "SRFlipFlop.h"
#include "DFlipFlop.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialization of our view object and declaring the parent frame
 * @param parent frame parent
 */
void SpartyBootsView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SpartyBootsView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SpartyBootsView::OnLeftDown, this);
    Bind(wxEVT_MOTION, &SpartyBootsView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &SpartyBootsView::OnTimer, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnOrGate, this, IDM_ORGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnAndGate, this, IDM_ANDGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnNotGate, this, IDM_NOTGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnSRFlipFlop, this, IDM_SRFLIPFLOP);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnDFlipFlop, this, IDM_DFLIPFLOP);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel3, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel4, this, IDM_LEVEL4);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel5, this, IDM_LEVEL5);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel6, this, IDM_LEVEL6);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel7, this, IDM_LEVEL7);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnLevel8, this, IDM_LEVEL8);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartyBootsView::OnExit, this, wxID_EXIT);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartyBootsView::OnPaint(wxPaintEvent &event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mSpartyBoots.Update(elapsed);

    wxAutoBufferedPaintDC dc(this);

    // wxBrush background(*wxGREEN);//230, 255, 230 rgb
    wxBrush background(wxColour(230, 255, 230));
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mSpartyBoots.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * on orgate event
 * @param event
 */
void SpartyBootsView::OnOrGate(wxCommandEvent &event)
{
    auto orGate = std::make_shared<OrGate>(&mSpartyBoots);
    mSpartyBoots.Add(orGate);

    // Refresh();
}

/**
 * On AndGate Event
 * @param event
 */
void SpartyBootsView::OnAndGate(wxCommandEvent &event)
{
    auto andGate = std::make_shared<AndGate>(&mSpartyBoots);
    mSpartyBoots.Add(andGate);

    // Refresh();
}
/**
 * On NotGate event
 * @param event
 */
void SpartyBootsView::OnNotGate(wxCommandEvent &event)
{
    auto notGate = std::make_shared<NotGate>(&mSpartyBoots);
    notGate->SetLocation(150, 150);
    mSpartyBoots.Add(notGate);

    // Refresh();
}
/**
 * On SRFlipFlop event
 * @param event
 */
void SpartyBootsView::OnSRFlipFlop(wxCommandEvent &event)
{
    auto sRFlipFlop = std::make_shared<SRFlipFlop>(&mSpartyBoots);
    mSpartyBoots.Add(sRFlipFlop);

    // Refresh();
}
/**
 * On DFlipFlop event
 * @param event
 */
void SpartyBootsView::OnDFlipFlop(wxCommandEvent &event)
{
    auto dFlipFlop = std::make_shared<DFlipFlop>(&mSpartyBoots);
    mSpartyBoots.Add(dFlipFlop);

    // Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event The moust click event
 */
void SpartyBootsView::OnLeftDown(wxMouseEvent &event)
{
    mGrabbedItem = mSpartyBoots.HitTest(event.GetX(), event.GetY());
}

/**
 * Handle when mouse is moving and grabbing item
 * @param event the mouse moving
 */
void SpartyBootsView::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            double virtualX = (event.GetX() - mSpartyBoots.getXOffset()) / mSpartyBoots.getScale();
            double virtualY = (event.GetY() - mSpartyBoots.getYOffset()) / mSpartyBoots.getScale();
            mGrabbedItem->SetLocation(virtualX, virtualY);
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem->Release();
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        // Refresh();
    }
}

/**
 * on level1 event
 * @param event
 */
void SpartyBootsView::OnLevel1(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(1);
    // Refresh();
}

/**
 * on level2 event
 * @param event
 */
void SpartyBootsView::OnLevel2(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(2);
    // Refresh();
}

/**
 * on level3 event
 * @param event
 */
void SpartyBootsView::OnLevel3(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(3);
    // Refresh();
}

/**
 * on level4 event
 * @param event
 */
void SpartyBootsView::OnLevel4(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(4);
    // Refresh();
}

/**
 * on level5 event
 * @param event
 */
void SpartyBootsView::OnLevel5(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(5);
    // Refresh();
}

/**
 * on level6 event
 * @param event
 */
void SpartyBootsView::OnLevel6(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(6);
    // Refresh();
}

/**
 * on level7 event
 * @param event
 */
void SpartyBootsView::OnLevel7(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(7);
    // Refresh();
}

/**
 * on level8 event
 * @param event
 */
void SpartyBootsView::OnLevel8(wxCommandEvent &event)
{
    mSpartyBoots.OnLevelSelect(8);
    // Refresh();
}

/**
 * Handle the timer event
 * @param event The timer event fired
 */
void SpartyBootsView::OnTimer(wxTimerEvent &event)
{
    if (mClose)
    {
        mTimer.Stop();
        wxQueueEvent(this, new wxCommandEvent(wxEVT_CLOSE_WINDOW));
        // Close(true);
        return;
    }
    Refresh();
}

/**
 * on exit event
 * @param event
 */
void SpartyBootsView::OnExit(wxCommandEvent &event)
{
    mClose = true;
    // wxQueueEvent(this, new wxCommandEvent(wxEVT_CLOSE_WINDOW));
    // Close(true);
    // Destroy();
}
