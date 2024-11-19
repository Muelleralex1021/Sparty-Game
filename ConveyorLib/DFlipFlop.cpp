/**
 * @file DFlipFlop.cpp
 * @author Alex Mueller
 */

#include "pch.h"
#include "DFlipFlop.h"
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

/// Size of the Flip Flop in pixels
const wxSize DFlipFlopSize(50, 75);

/// Gap between the edge of the flip flop and the labels
const int DFlipFlopLabelMargin = 3;

/// How large the clock input triagle is in pixels width and height
const int DFlipFlopClockSize = 10;

DFlipFlop::DFlipFlop(SpartyBoots *spartyBoots) : LogicGate(spartyBoots)
{
    auto x = GetX();
    auto y = GetY();
    auto w = DFlipFlopSize.GetWidth();  // Width of the AND gate
    auto h = DFlipFlopSize.GetHeight(); // Height of the AND gate

    /// Creating a vector of pins and initializing them at the same time
    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));
    mInputPins.push_back(std::make_shared<InputPin>(spartyBoots));
    mOutputPins.push_back(std::make_shared<OutputPin>(spartyBoots));
    mOutputPins.push_back(std::make_shared<OutputPin>(spartyBoots));

    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y - h/4);
    mInputPins[1]->SetLocation(x - w / 2 - DefaultLineLength, y + h/4);
    mOutputPins[0]->SetLocation(x + w / 2 + DefaultLineLength, y - h/4);
    mOutputPins[1]->SetLocation(x + w / 2 + DefaultLineLength, y + h/4);

    /// Adding the pins to spartyboots so that it recognizes it when hittesting
    spartyBoots->Add(mInputPins[0]);
    spartyBoots->Add(mOutputPins[0]);
    spartyBoots->Add(mInputPins[1]);
    spartyBoots->Add(mOutputPins[1]);
}
void DFlipFlop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto x = GetX();
    auto y = GetY();
    auto w = DFlipFlopSize.GetWidth();
    auto h = DFlipFlopSize.GetHeight();

    // Create a path for the D flip-flop body
    auto path = graphics->CreatePath();
    path.AddRectangle(x - w / 2, y - h / 2, w, h);

    // Draw the main body rectangle
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // Set up font for the labels
    wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial");
    graphics->SetFont(font, *wxBLACK);

    // Draw labels "D", "Q", and "Q'"
    graphics->DrawText("D", x - w / 2 + DFlipFlopLabelMargin, y - h / 4 - 8);
    graphics->DrawText("Q", x + w / 2 - DFlipFlopLabelMargin - 15, y - h / 4 - 8);
    graphics->DrawText("Q'", x + w / 2 - DFlipFlopLabelMargin - 15, y + h / 4 - 8);

    // Position the triangle so that its left side aligns with the rectangle's left edge
    wxPoint2DDouble p1(x - w / 2 + DFlipFlopClockSize, y + h / 4);               // Right point of the triangle
    wxPoint2DDouble p2(x - w / 2, y + h / 4 - DFlipFlopClockSize / 2);           // Top corner aligned with left edge of the rectangle
    wxPoint2DDouble p3(x - w / 2, y + h / 4 + DFlipFlopClockSize / 2);           // Bottom corner aligned with left edge of the rectangle

    // Create a path for the hollow triangle
    auto clockPath = graphics->CreatePath();
    clockPath.MoveToPoint(p1);
    clockPath.AddLineToPoint(p2);
    clockPath.AddLineToPoint(p3);
    clockPath.CloseSubpath();


    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y - h/4);
    mInputPins[1]->SetLocation(x - w / 2 - DefaultLineLength, y + h/4);
    mOutputPins[0]->SetLocation(x + w / 2 + DefaultLineLength, y - h/4);
    mOutputPins[1]->SetLocation(x + w / 2 + DefaultLineLength, y + h/4);

    mInputPins[0]->DrawPins(graphics, x - w / 2, y - h/4, x - w / 2 - DefaultLineLength, y - h/4);
    mOutputPins[0]->DrawPins(graphics, x + w / 2, y - h/4, x + w / 2 + DefaultLineLength, y - h/4);
    mInputPins[1]->DrawPins(graphics, x - w / 2, y + h/4, x - w / 2 - DefaultLineLength, y + h/4);
    mOutputPins[1]->DrawPins(graphics, x + w / 2, y + h/4, x + w / 2 + DefaultLineLength, y + h/4);


    // Draw the hollow triangle with only the outline
    graphics->SetBrush(*wxTRANSPARENT_BRUSH);  // Set brush to transparent for a hollow effect
    graphics->SetPen(*wxBLACK_PEN);            // Outline color
    graphics->DrawPath(clockPath);
}

bool DFlipFlop::HitTest(int x, int y)
{
    double wid = DFlipFlopSize.GetWidth();
    double hit = DFlipFlopSize.GetHeight();

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

void DFlipFlop::GateCompute()
{
    if (mInputPins[0]->isConnected() && mInputPins[1]->isConnected())
    {
        // Check if the CLK pin is currently high
        if (mInputPins[1]->getValue()) // When CLK is high
        {
            // Set Q to the value of D
            bool dValue = mInputPins[0]->getValue();
            mOutputPins[0]->setValue(dValue);       // Q = D
            mOutputPins[0]->setConnect(true);

            // Set Q' to the inverse of Q
            mOutputPins[1]->setValue(!dValue);      // Q' = NOT Q
            mOutputPins[1]->setConnect(true);
        }
    }
}

void DFlipFlop::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{

}