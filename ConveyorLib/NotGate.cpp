/**
 * @file NotGate.cpp
 * @author Alex Mueller
 */

#include "pch.h"
#include "NotGate.hpp"
#include "SpartyBoots.hpp"

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

/// Size of the Not gate in pixels
const wxSize NotGateSize(50, 50);

/**
 * constructor for the NotGate class
 * @param spartyBoots
 */
NotGate::NotGate(SpartyBoots *spartyBoots): LogicGate(spartyBoots)
{
    auto x = GetX();
    auto y = GetY();
    auto w = NotGateSize.GetWidth();  // Width of the AND gate
    auto h = NotGateSize.GetHeight(); // Height of the AND gate

    /// Creating a vector of pins and initializing them at the same time
    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));
    mOutputPins.push_back(std::make_shared<OutputPin>(spartyBoots));

    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y);
    mOutputPins[0]->SetLocation(x + w / 2 + DefaultLineLength, y);

    /// Adding the pins to spartyboots so that it recognizes it when hittesting
    spartyBoots->Add(mInputPins[0]);
    spartyBoots->Add(mOutputPins[0]);
}

/**
 * Draws the Not Gate
 * @param graphics
 */
void NotGate::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Create a path to draw the NOT gate shape
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = NotGateSize.GetWidth();  // Width of the NOT gate
    auto h = NotGateSize.GetHeight(); // Height of the NOT gate

    // Define the three corner points of the NOT gate (triangle)
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
    wxPoint2DDouble p2(x + w / 2, y);         // Center right
    wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left

    // Create the path for the NOT gate triangle
    path.MoveToPoint(p1);
    path.AddLineToPoint(p2); // Line to the center right
    path.AddLineToPoint(p3); // Line to the top left
    path.AddLineToPoint(p1); // Close back to the bottom left

    // Set pen and brush for drawing the NOT gate triangle
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);

    // Draw the triangle path
    graphics->DrawPath(path);

    // Draw the small circle at the output of the NOT gate
    double circleRadius = 5;                         // Radius of the circle
    double circleCenterX = x + w / 2 + circleRadius; // Center of the circle
    double circleCenterY = y;

    // GateCompute();


    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y);
    mOutputPins[0]->SetLocation(x + w / 2 + DefaultLineLength, y);

    mInputPins[0]->DrawPins(graphics, x - w / 2, y, x - w / 2 - DefaultLineLength, y);
    mOutputPins[0]->DrawPins(graphics, x + w / 2, y, x + w / 2 + DefaultLineLength, y);

    // Draw the circle
    graphics->SetBrush(*wxWHITE_BRUSH); // Set brush to fill the circle
    graphics->SetPen(*wxBLACK_PEN);
    graphics->DrawEllipse(circleCenterX - circleRadius, circleCenterY - circleRadius, 2 * circleRadius, 2 * circleRadius);

}

/**
 * Draw the pins of AndGate by calling from LogicItem
 * @param graphics
 * @param start_x
 * @param start_y
 * @param end_x
 * @param end_y
 */
void NotGate::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{
}

/**
 * Checks if clicked area contains the not gate
 * @param x
 * @param y
 * @return bool
 */
bool NotGate::HitTest(int x, int y)
{
    double wid = NotGateSize.GetWidth();
    double hit = NotGateSize.GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return true;
}

/**
 * computes gate logic
 */
void NotGate::GateCompute()
{
    if (mInputPins[0]->isConnected())
    {
        mOutputPins[0]->setValue(!(mInputPins[0]->getValue()));
        mOutputPins[0]->setConnect(true);
    }
}
