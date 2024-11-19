/**
 * @file OrGate.cpp
 * @author Alex Mueller
 */

#include "pch.h"
#include "OrGate.hpp"
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

/// Size of OR gate
const wxSize OrGateSize(75, 50);
/**
 * Constructor
 * @param spartyBoots The SpartyBoots instance that this OR gate belongs to
 */
OrGate::OrGate(SpartyBoots *spartyBoots): LogicGate(spartyBoots)
{
    auto x = GetX();
    auto y = GetY();
    auto w = OrGateSize.GetWidth();  // Width of the AND gate
    auto h = OrGateSize.GetHeight(); // Height of the AND gate

    /// Creating a vector of pins and initializing them at the same time
    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));
    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));

    mOutputPins.push_back(std::make_shared<OutputPin>(spartyBoots));

    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y + h / 4);
    mInputPins[1]->SetLocation(x - w / 2 - DefaultLineLength, y - h / 4);

    mOutputPins[0]->SetLocation(x + w / 2 + DefaultLineLength, y);



    /// Adding the pins to spartyboots so that it recognizes it when hittesting
    spartyBoots->Add(mInputPins[0]);
    spartyBoots->Add(mInputPins[1]);
    spartyBoots->Add(mOutputPins[0]);
}

/**
 * Draw the OR gate
 * @param graphics
 */
void OrGate::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Create a path to draw the gate shape
    auto path = graphics->CreatePath();

    // The the location and size
    auto x = GetX();
    auto y = GetY();
    auto w = OrGateSize.GetWidth();
    auto h = OrGateSize.GetHeight();

    // The three corner points of an OR gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
    wxPoint2DDouble p2(x + w / 2, y);         // Center right
    wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left

    // Control points used to create the Bezier curves
    auto controlPointOffset1 = wxPoint2DDouble(w * 0.5, 0);
    auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
    auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

    // Create the path for the gate
    path.MoveToPoint(p1);
    path.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
    path.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
    path.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
    path.CloseSubpath();

    // Draw the path
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // // Compute value of input and change output accordingly
    // GateCompute();


    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y + h / 4);
    mInputPins[1]->SetLocation(x - w / 2 - DefaultLineLength, y - h / 4);

    mOutputPins[0]->SetLocation(x + w / 2 + DefaultLineLength, y);

    mInputPins[0]->DrawPins(graphics, x - w * 0.7 / 2, y + h / 4, x - w / 2 - DefaultLineLength, y + h / 4);
    mInputPins[1]->DrawPins(graphics, x - w * 0.7 / 2, y - h / 4, x - w / 2 - DefaultLineLength, y - h / 4);
    mOutputPins[0]->DrawPins(graphics, x + w / 2, y, x + w / 2 + DefaultLineLength, y);

}

/**
 * Draw the pins of AndGate by calling from LogicItem
 * @param graphics the graphics context to draw on
 * @param start_x the starting position of tail of pin
 * @param start_y  starting position of tail of pin
 * @param end_x where pin end (and where the pin is)
 * @param end_y where pin end (and where the pin is)
 */
void OrGate::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{
}

/**
 * Test to see if we hit this OR gate with a mouse click.
 * @param x X position to test
 * @param y Y position to test
 * @return true
 * if hit
 */
bool OrGate::HitTest(int x, int y)
{
    // Simple bounding box hit test for now (you can make it more complex if needed)
    double wid = OrGateSize.GetWidth();
    double hit = OrGateSize.GetHeight();

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
void OrGate::GateCompute()
{
    if (mInputPins[0]->isConnected() && mInputPins[1]->isConnected())
    {
        mOutputPins[0]->setValue(mInputPins[0]->getValue() || mInputPins[1]->getValue());
        mOutputPins[0]->setConnect(true);
    }
}

