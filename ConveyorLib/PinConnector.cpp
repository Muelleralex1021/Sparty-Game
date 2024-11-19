/**
 * @file PinConnector.cpp
 * @author tiend
 */
 
#include "pch.h"
#include "PinConnector.h"
#include "SpartyBoots.hpp"
#include "OutputPin.h"
#include <cmath>


///Pin radius to click
int pinRadius = 5;

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

PinConnector::PinConnector(SpartyBoots *spartyBoots, OutputPin* ownerPin)
    : Item(spartyBoots), mOwner(ownerPin) {
    // Constructor body (if needed)
}
/**
 *Function to draw set the location of the end of the pinConnector
 *@param y
 *@param x
** */
void PinConnector::SetLocation(double x, double y)
{
    mDragging = true;
    if (mCaught != nullptr)
    {
        // Release any previous catch
        mCaught->SetLine(nullptr);
        mCaught = nullptr;
    }
    mLineEnd = wxPoint(int(x), int(y));
}

/**
 * Draw this fishing rod.
 *
 * This is just used in development to see where the
 * rod end is supposed to be.
 *
 * @param graphics graphics to draw on
 */
void PinConnector::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double connectorX = mOwner->GetX();
    double connectorY = mOwner->GetY();

    graphics->SetPen(graphics->CreatePen(wxGraphicsPenInfo (ConnectionColorUnknown, 3)));

    if (mDragging)
    {
        // Define points p1 and p4
        wxPoint2DDouble p1(connectorX, connectorY);
        wxPoint2DDouble p4(mLineEnd.x, mLineEnd.y);

        // Calculate offset
        double distance = std::hypot(p4.m_x - p1.m_x, p4.m_y - p1.m_y);
        double offset = std::min(BezierMaxOffset, distance);

        // Define points p2 and p3 for curvature control
        wxPoint2DDouble p2(p1.m_x + offset, p1.m_y);
        wxPoint2DDouble p3(p4.m_x - offset, p4.m_y);

        // Create and draw Bezier curve path
        wxGraphicsPath path = graphics->CreatePath();
        path.MoveToPoint(p1.m_x, p1.m_y);
        path.AddCurveToPoint(p2.m_x, p2.m_y, p3.m_x, p3.m_y, p4.m_x, p4.m_y);

        graphics->StrokePath(path);
    }

    if (mCaught != nullptr)
    {

        if (mCaught->isConnected())
        {
            if (mCaught->getValue())
            {
                graphics->SetPen(graphics->CreatePen(wxGraphicsPenInfo (ConnectionColorOne, 3)));
            }
            else
            {
                graphics->SetPen(graphics->CreatePen(wxGraphicsPenInfo (ConnectionColorZero, 3)));
            }
        }

        wxPoint2DDouble p1(connectorX, connectorY);
        wxPoint2DDouble p4(mCaught->GetX(), mCaught->GetY());

        double distance = std::hypot(p4.m_x - p1.m_x, p4.m_y - p1.m_y);
        double offset = std::min(BezierMaxOffset, distance);

        wxPoint2DDouble p2(p1.m_x + offset, p1.m_y);
        wxPoint2DDouble p3(p4.m_x - offset, p4.m_y);

        wxGraphicsPath path = graphics->CreatePath();
        path.MoveToPoint(p1.m_x, p1.m_y);
        path.AddCurveToPoint(p2.m_x, p2.m_y, p3.m_x, p3.m_y, p4.m_x, p4.m_y);

        graphics->StrokePath(path);
    }
}

/**
 * Did we click on the rod end?
 * @param x X location clicked on
 * @param y Y location clicked on
 * @return Did we click on it?
 */
bool PinConnector::HitTest(int x, int y)
{
    double rodX = mOwner->GetX();
    double rodY = mOwner->GetY();

    return (rodX -x) * (rodX - x) + (rodY - y) * (rodY - y) < pinRadius * pinRadius;
}

void PinConnector::Release()
{
    if(mDragging)
    {
        // The mouse has been released. See if there
        // is a fish we can catch?
        mOwner->GetSpartyBoots()->TryToCatch(this, mLineEnd);
    }

    mDragging = false;
}

/**
 * Set the caught fish
 * @param caught Caught fish
 */
void PinConnector::SetCaught(InputPin* caught)
{
    if(mCaught != nullptr)
    {
        // Release any previous catch
        mCaught->SetLine(nullptr);
    }

    mCaught = caught;

    if(mCaught != nullptr)
    {
        mCaught->SetLine(this);
        //Creating new connection as this one gets tethered
        this->getOwner()->AddConnector(std::make_shared<PinConnector>(this->GetSpartyBoots(), this->getOwner()));
    }

}

void PinConnector::MoveToFront()
{
    mOwner->GetSpartyBoots()->MoveToFront(mOwner);
}