/**
 * @file Sparty.cpp
 * @author Alex Mueller
 */

#include "pch.h"
#include "Sparty.hpp"
#include "SpartyBoots.hpp"

/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = L"sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = L"sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = L"sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

/// The maximum rotation for Sparty's boot in radians
const double SpartyBootMaxRotation = 0.8;

/// The point in the kick animation when the product
/// actually is kicked. If the kick duration is 0.25,
/// we kick when 0.25 * 0.35 seconds have elapsed.
const double SpartyKickPoint = 0.35;

/// What percentage of the way down Sparty do we find the tip of his boot?
/// This means the location of the boot when kicking is 80% of the
/// way from the top of the Sparty image.
const double SpartyBootPercentage = 0.80;

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
 * initialization function for sparty
 * @param spartyBoots SpartyBoots
 * @param x int
 * @param y int
 * @param height int
 * @param
 * pinX int
 * @param pinY int
 * @param kickDuration float
 * @param kickSpeed float
 */
Sparty::Sparty(SpartyBoots *spartyBoots, int x, int y, int height, int pinX, int pinY, double kickDuration, int kickSpeed)
    : LogicItem(spartyBoots), mSpartyBackImage(L"images/" + SpartyBackImage, wxBITMAP_TYPE_ANY), mSpartyBackBitmap(mSpartyBackImage),
      mSpartyBootImage(L"images/" + SpartyBootImage, wxBITMAP_TYPE_ANY), mSpartyBootBitmap(mSpartyBootImage),
      mSpartyFrontImage(L"images/" + SpartyFrontImage, wxBITMAP_TYPE_ANY), mSpartyFrontBitmap(mSpartyFrontImage)

{
    mX = x;
    mY = y;
    mHeight = height;
    mPinX = pinX;
    mPinY = pinY;
    mKickDuration = kickDuration;
    mKickSpeed = kickSpeed;
    mWidth = (double)mHeight / 2;
    SetLocation(x, y);

    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));
    spartyBoots->Add(mInputPins[0]);
}

/**
 * Draw Sparty.
 * @param graphics
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    int x = GetX(), y = GetY();

    //Change color according to input pin value
    if (mInputPins[0]->isConnected())
    {
        if (mInputPins[0]->getValue())
        {
            graphics->SetPen(graphics->CreatePen(wxGraphicsPenInfo (ConnectionColorOne, 3)));
        }
        else
        {
            graphics->SetPen(graphics->CreatePen(wxGraphicsPenInfo (ConnectionColorZero, 3)));
        }
    }
    else
    {
        graphics->SetPen(graphics->CreatePen(wxGraphicsPenInfo (ConnectionColorUnknown, 3)));
    }


    graphics->StrokeLine(mX, mY, mX + 100, mY);
    graphics->StrokeLine(mX + 100, mY, mX + 100, mY - 200);

    if (mIsSensor)
    {
        graphics->StrokeLine(mX + 100, mY - 200, mX + 775, mY - 200);
        graphics->StrokeLine(mX + 775, mY - 200, mX + 775, mY + 60);
        graphics->StrokeLine(mX + 775 - DefaultLineLength, mY + 60, mX + 775, mY + 60);
    }
    else
    {
        graphics->StrokeLine(mX + 100, mY - 200, mX + 830, mY - 200);
        graphics->StrokeLine(mX + 830, mY - 200, mX + 830, mY + 60);
        graphics->StrokeLine(mX + 830 - DefaultLineLength, mY + 60, mX + 830, mY + 60);
    }

    graphics->DrawBitmap(mSpartyBackBitmap, mX - (mWidth / 3), mY - (mHeight / 2), mWidth, mHeight);
    graphics->DrawBitmap(mSpartyFrontBitmap, mX - (mWidth / 3), mY - (mHeight / 2), mWidth, mHeight);

    mInputPins[0]->SetLocation(mPinX,mPinY);
    mInputPins[0]->DrawPins(graphics, mPinX,mPinY, mPinX,mPinY);

    if(mIsKicking)
    {
        graphics->PushState();

        double bootPivotX = mX - (mWidth / 3) + (mWidth * SpartyBootPivot.m_x);
        double bootPivotY = mY - (mWidth) + (mHeight * SpartyBootPivot.m_y);

        graphics->Translate(bootPivotX, bootPivotY);

        graphics->Rotate(mBootAngle);

        graphics->Translate(-bootPivotX, -bootPivotY);

        graphics->DrawBitmap(mSpartyBootBitmap, mX - (mWidth / 3), mY - (mHeight / 2), mWidth, mHeight);

        graphics->PopState();
    }
    else
    {
        graphics->DrawBitmap(mSpartyBootBitmap, mX - (mWidth / 3), mY - (mWidth), mWidth, mHeight);
    }

}


/**
 * Update Sparty.
 * @param elapsed The amount of time elapsed since the last update
 */
void Sparty::Update(double elapsed)
{
    if (mBootAngle >= SpartyBootMaxRotation)
    {
        mReturning = true;
    }
    if (mBootAngle <= 0.0)
    {
        mBootAngle = 0.0;
        mReturning = false;
    }

    if (mIsKicking)
    {
        if (!mReturning)
        {
            mBootAngle += elapsed * (SpartyBootMaxRotation / mKickDuration);
        }
        else
        {
            mBootAngle -= elapsed * (SpartyBootMaxRotation / mKickDuration);
            if (mBootAngle <= 0.0)
            {
                mIsKicking = false;
                mBootAngle = 0.0;
            }
        }
    }
}
