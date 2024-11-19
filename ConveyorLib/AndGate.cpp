/**
 * @file AndGate.cpp
 * @author bdean
 */

#include "pch.h"
#include "AndGate.hpp"
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

/// Size of the AND gate in pixels
/// @return wxSize
/// for drawing and hit testing
const wxSize AndGateSize(75, 50);

/// How far the Bezier control points are for the AND gate to the right of the ends of the curve as a percentage of the gate width
const double AndGateControlPointOffset = 0.75;

/**
 * Constructor for the AndGate class
 * @param spartyBoots
 */
AndGate::AndGate(SpartyBoots *spartyBoots): LogicGate(spartyBoots)
{
    auto x = GetX();
    auto y = GetY();
    auto w = AndGateSize.GetWidth();  // Width of the AND gate
    auto h = AndGateSize.GetHeight(); // Height of the AND gate

    /// Creating a vector of pins and initializing them at the same time
    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));
    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));

    mOutputPins.push_back(std::make_shared<OutputPin>(spartyBoots));

    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y + h / 4);
    mInputPins[1]->SetLocation(x - w / 2 - DefaultLineLength, y - h / 4);

    mOutputPins[0]->SetLocation(x + w / 2 + 3 * DefaultLineLength, y);

    /// Adding the pins to spartyboots so that it recognizes it when hittesting
    spartyBoots->Add(mInputPins[0]);
    spartyBoots->Add(mInputPins[1]);
    spartyBoots->Add(mOutputPins[0]);
}

/**
 * Draw AndGate with virtual pixel
 * @param graphics
 */
void AndGate::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Create a path to draw the AND gate shape
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();

    auto w = AndGateSize.GetWidth();  // Width of the AND gate
    auto h = AndGateSize.GetHeight(); // Height of the AND gate

    // Define the corner points of the AND gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
    wxPoint2DDouble p2(x + w / 2, y + h / 2); // Bottom right
    wxPoint2DDouble p3(x + w / 2, y - h / 2); // Top right
    wxPoint2DDouble p4(x - w / 2, y - h / 2); // Top left

    // Control point used for the rounded right side of the AND gate
    auto controlPoint = wxPoint2DDouble(w * AndGateControlPointOffset, 0);

    // Create the path for the AND gate
    path.MoveToPoint(p1);                                           // Start at the bottom left
    path.AddLineToPoint(p4);                                        // Draw the left vertical line
    path.AddLineToPoint(p3);                                        // Draw the top horizontal line
    path.AddCurveToPoint(p3 + controlPoint, p2 + controlPoint, p2); // Rounded right side
    path.AddLineToPoint(p1);                                        // Draw the bottom horizontal line

    // Close the path
    path.CloseSubpath();

    // Set pen and brush for drawing
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);

    // Draw the path
    graphics->DrawPath(path);

    // // Compute logic of the inputs and change output accordingly
    // GateCompute();

     // if (mOutputPins[0]->getValue() == true)
     // {
     //
     // }

    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y + h / 4);
    mInputPins[1]->SetLocation(x - w / 2 - DefaultLineLength, y - h / 4);

    mOutputPins[0]->SetLocation(x + w / 2 + 3 * DefaultLineLength, y);

    mInputPins[0]->DrawPins(graphics, x - w / 2, y + h / 4, x - w / 2 - DefaultLineLength, y + h / 4);
    mInputPins[1]->DrawPins(graphics, x - w / 2, y - h / 4, x - w / 2 - DefaultLineLength, y - h / 4);
    mOutputPins[0]->DrawPins(graphics, x + w / 2 + 2.1 * DefaultLineLength, y, x + w / 2 + 3 * DefaultLineLength, y);
}

/**
 * Draw the pins of AndGate by calling from LogicItem
 * @param graphics
 * @param start_x
 * @param start_y
 * @param end_x
 * @param end_y
 */
void AndGate::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{
}

/**
 * Test to see if we hit this OR gate with a mouse click.
 * @param x X position to test
 * @param y Y position to test
 * @return true
 * * if hit
 */
bool AndGate::HitTest(int x, int y)
{
    double wid = AndGateSize.GetWidth();
    double hit = AndGateSize.GetHeight();

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
 * This function checks if both input pins are connected. If they are,
 * it sets the value of the output pin to the logical AND of the values
 * of the two input pins.
 */
void AndGate::GateCompute()
{
    if (mInputPins[0]->isConnected() && mInputPins[1]->isConnected())
    {
        mOutputPins[0]->setValue(mInputPins[0]->getValue() && mInputPins[1]->getValue());
        mOutputPins[0]->setConnect(true);
    }
}
