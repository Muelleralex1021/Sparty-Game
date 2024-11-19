/**
 * Conveyor class definition
 * @file Conveyor.cpp
 * @author Jack Bruienne
 */

#include "pch.h"
#include "Conveyor.hpp"
#include <string>
#include "SpartyBoots.hpp"

/// Image for the background (base) of the conveyor
const std::wstring ConveyorBackgroundImage = L"conveyor-back.png";

/// Image for the conveyor belt
const std::wstring ConveyorBeltImage = L"conveyor-belt.png";

/// Image for the conveyor control panel when stopped.
const std::wstring ConveyorPanelStoppedImage = L"conveyor-switch-stop.png";

/// Image for the conveyor control panel when started.
const std::wstring ConveyorPanelStartedImage = L"conveyor-switch-start.png";

/// Rectangle representing the location of the start button relative to the panel
///@return wxRect
const wxRect StartButtonRect(35, 29, 95, 36);

/// Rectangle representing the location of the stop button relative to the panel
///@return wxRect
const wxRect StopButtonRect(35, 87, 95, 36);

/// Width of the conveyor
const int ConveyorWidth = 150;

/// Width of the panel
const int PanelWidth = 138;

/// Height of the panel
const int PanelHeight = 156;

/**
 * Conveyor constructor
 * @param game
 * @param x
 * @param y
 * @param height
 * @param speed
 * @param panelX
 * @param panelY
 */
Conveyor::Conveyor(SpartyBoots *game, double x, double y, int height, int speed, int panelX, int panelY)
    : Item(game), mHeight(height), mSpeed(speed), mPanelX(panelX), mPanelY(panelY),
      mBackgroundImage(L"images/" + ConveyorBackgroundImage, wxBITMAP_TYPE_ANY), mBackgroundBitmap(mBackgroundImage),
      mBeltImage(L"images/" + ConveyorBeltImage, wxBITMAP_TYPE_ANY), mBeltBitmap(mBeltImage),
      mPanelStartImage(L"images/" + ConveyorPanelStartedImage, wxBITMAP_TYPE_ANY), mPanelStartBitmap(mPanelStartImage),
      mPanelStopImage(L"images/" + ConveyorPanelStoppedImage, wxBITMAP_TYPE_ANY), mPanelStopBitmap(mPanelStopImage)
{
    SetLocation(x, y);
}

/**
 * Draw the conveyor.
 * @param graphics
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    int x = GetX(), y = GetY();
    if (mRunning)
    {
        graphics->DrawBitmap(mPanelStopBitmap, x + mPanelX, y + mPanelY, PanelWidth, PanelHeight);
    }
    else
    {
        graphics->DrawBitmap(mPanelStartBitmap, x + mPanelX, y + mPanelY, PanelWidth, PanelHeight);
    }
    graphics->DrawBitmap(mBackgroundBitmap, x - (ConveyorWidth / 2), y - (mHeight / 2), ConveyorWidth, mHeight);

    graphics->PushState();
    graphics->Clip(x - (ConveyorWidth / 2), y - (mHeight / 2), ConveyorWidth, mHeight);
    graphics->DrawBitmap(mBeltBitmap, x - (ConveyorWidth / 2), y - (mHeight / 2) + (mBeltOffset % mHeight) - mHeight, ConveyorWidth,
                         mHeight);
    graphics->DrawBitmap(mBeltBitmap, x - (ConveyorWidth / 2), y - (mHeight / 2) + (mBeltOffset % mHeight), ConveyorWidth, mHeight);
    graphics->PopState();
}

/**
 * Check if the location is on the conveyor.
 * @param x The X position of the click
 * @param y The Y position of the click
 * @return

 * * Whether the mouse was hit
 */
bool Conveyor::HitTest(int x, int y)
{
    x -= GetX() + mPanelX;
    y -= GetY() + mPanelY;

    if (StopButtonRect.Contains(x, y) && mRunning)
    {
        mRunning = false;
    }
    else if (StartButtonRect.Contains(x, y) && !mRunning)
    {
        mRunning = true;
    }

    return false;
}

/**
 * Update the conveyor position.
 * @param elapsed The amount of time elapsed since the last update
 */
void Conveyor::Update(double elapsed)
{
    if (mRunning)
    {
        int offset = elapsed * mSpeed;
        mBeltOffset += offset;
    }
}

/**
 * Set a product's clip region with this conveyor's rect.
 * @param item The item to add
 */
void Conveyor::SetProductClip(std::shared_ptr<Product> item)
{
    item->UpdateClipRegion(wxRect(GetX() - ConveyorWidth / 2, GetY() - mHeight / 2, ConveyorWidth, mHeight));
}
