/**
 * @file SpartyBootsApp.cpp
 * @author Alex Mueller
 */

#include "pch.h"
#include "SpartyBootsApp.hpp"
#include "MainFrame.hpp"

/**
 * Initialize the application.
 * @return
 */
bool SpartyBootsApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
