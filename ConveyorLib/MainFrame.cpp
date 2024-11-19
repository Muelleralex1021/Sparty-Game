/**
 * @file MainFrame.cpp
 * @author tiend
 */

#include "pch.h"
#include "MainFrame.hpp"
#include "ids.hpp"
#include "SpartyBootsView.hpp"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty's Boots", wxDefaultPosition, wxSize(1000, 800));
    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer(wxVERTICAL);
    // Create the view class object as a child of MainFrame
    mSpartyBootsView = new SpartyBootsView();
    mSpartyBootsView->Initialize(this);


    // Add it to the sizer
    sizer->Add(mSpartyBootsView, 1, wxEXPAND | wxALL);
    // Set the sizer for this frame
    SetSizer(sizer);
    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar();

    auto levelMenu = new wxMenu();
    auto gateMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(levelMenu, L"&Level Select");
    menuBar->Append(gateMenu, L"&Gates");
    menuBar->Append(helpMenu, L"&Help");

    levelMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    gateMenu->Append(IDM_ORGATE, "&Or Gate");
    gateMenu->Append(IDM_ANDGATE, "&And Gate");
    gateMenu->Append(IDM_NOTGATE, "&Not Gate");
    gateMenu->Append(IDM_SRFLIPFLOP, "&SR Flip Flop");
    gateMenu->Append(IDM_DFLIPFLOP, "&D Flip Flop");
    levelMenu->Append(IDM_LEVEL1, "Level 1");
    levelMenu->Append(IDM_LEVEL2, "Level 2");
    levelMenu->Append(IDM_LEVEL3, "Level 3");
    levelMenu->Append(IDM_LEVEL4, "Level 4");
    levelMenu->Append(IDM_LEVEL5, "Level 5");
    levelMenu->Append(IDM_LEVEL6, "Level 6");
    levelMenu->Append(IDM_LEVEL7, "Level 7");
    levelMenu->Append(IDM_LEVEL8, "Level 8");

    SetMenuBar(menuBar);

    // Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);

    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}


/**
 * on about event
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(L"Welcome to the Sparty Boots!", L"About Sparty Boots", wxOK, this);
}


/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mSpartyBootsView->Stop();
    Destroy();
}