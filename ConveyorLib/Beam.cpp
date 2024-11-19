/**
 * @file Beam.cpp
 * @author trevo
 */

#include "pch.h"
#include "Beam.hpp"

/// Image for the beam sender and receiver when red
const std::wstring BeamRedImage = L"beam-red.png";

/// Image for the beam sender and receiver when green
const std::wstring BeamGreenImage = L"beam-green.png";

/// X offset for the beam pin in pixels
/// This is larger than normal to get it past Sparty's feet
const int BeamPinOffset = 80;

/// Width of the conveyor
const int ConveyorWidth = 150;

/// Width of the conveyor
const int BeamPinHeight = 30;

/// Width of the conveyor
const int BeamPinWidth = 40;


/// Diameter to draw the pin in pixels
const int PinSize = 10;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown = wxColour(128, 128, 128);

/// Maximum offset of Bezier control points relative to line ends
static constexpr double BezierMaxOffset = 200;

/// Line with for drawing lines between pins
static const int LineWidth = 3;

/// Default length of line from the pin
static const int DefaultLineLength = 20;

/**
 * Initialization function for Beam
 * @param spartyBoots SpartyBoots
 * @param x int
 * @param y int
 * @param sender int
 */
Beam::Beam(SpartyBoots *spartyBoots, int x, int y, int sender) : LogicItem(spartyBoots),
    mBeamRedImage(L"images/" + BeamRedImage, wxBITMAP_TYPE_ANY), mBeamRedBitmap(mBeamRedImage),
    mBeamGreenImage(L"images/" + BeamGreenImage, wxBITMAP_TYPE_ANY), mBeamGreenBitmap(mBeamGreenImage),
    mBeamGreenImageMirrored(L"images/" + BeamGreenImage, wxBITMAP_TYPE_ANY), mBeamGreenBitmapMirrored(mBeamGreenImage.Mirror(true)),
    mBeamRedImageMirrored(L"images/" + BeamGreenImage, wxBITMAP_TYPE_ANY), mBeamRedBitmapMirrored(mBeamRedImage.Mirror(true))


{
     mX = x;
     mY = y;
     mSender = sender;
    SetLocation(x, y);
    mOutputPins.push_back(std::make_shared<OutputPin>(spartyBoots));
    spartyBoots->Add(mOutputPins[0]);
    mOutputPins[0]->setConnect((true));
}

/**
 * Draw the beam.
 * @param graphics
 */
void Beam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    wxPen laser1(wxColour(255, 200, 200, 100), 8);
    wxPen laser2(wxColour(255, 0, 0, 175), 4);

    graphics->SetPen(laser1);
    graphics->StrokeLine(mX - ConveyorWidth - BeamPinOffset + 5, mY,
                     mX, mY);

    graphics->SetPen(laser2);
    graphics->StrokeLine(mX - ConveyorWidth - BeamPinOffset + 5, mY,
                     mX, mY);

    mOutputPins[0]->SetLocation(mX + 25 + BeamPinOffset,mY);
    mOutputPins[0]->DrawPins(graphics, mX + 50,mY, mX + 25 + BeamPinOffset,mY);

    if(!mItemTouchingBeam)
    {
        wxPen wirePen(ConnectionColorZero,3);
        graphics->SetPen(wirePen);
        graphics->StrokeLine(mX, mY,mX + 100, mY);

        graphics->DrawBitmap(mBeamGreenBitmap, mX - ConveyorWidth - BeamPinOffset, mY - (BeamPinHeight/2), BeamPinWidth, BeamPinHeight);
        graphics->DrawBitmap(mBeamGreenBitmapMirrored, mX, mY - (BeamPinHeight/2), BeamPinWidth, BeamPinHeight);

    }
    else
    {
        wxPen wirePen(ConnectionColorOne,3);
        graphics->SetPen(wirePen);
        graphics->StrokeLine(mX, mY,mX + 100, mY);

        graphics->DrawBitmap(mBeamRedBitmap, mX - ConveyorWidth - BeamPinOffset, mY - (BeamPinHeight/2), BeamPinWidth, BeamPinHeight);
        graphics->DrawBitmap(mBeamRedBitmapMirrored, mX, mY - (BeamPinHeight/2), BeamPinWidth, BeamPinHeight);
    }
}
/**
 * setter for the boolean that indicates whether or not an item is passing the beam
 * @param itemTouching
 */
void Beam::SetItemTouchingBeam(bool itemTouching)
{
    mItemTouchingBeam = itemTouching;
    ///set output pin value to true or false when item comes by
    mOutputPins[0]->setValue(itemTouching);
}