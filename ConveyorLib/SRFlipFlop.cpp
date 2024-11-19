/**
 * @file SRFlipFlop.cpp
 * @author bdean
 */

#include "pch.h"
#include "SRFlipFlop.h"
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
const wxSize SRFlipFlopSize(50, 75);

/// Gap between the edge of the flip flop and the labels
const int SRFlipFlopLabelMargin = 3;

/**
 * Constructor
 * @param spartyBoots The SpartyBoots instance that this SR flip-flop belongs to
 */
SRFlipFlop::SRFlipFlop(SpartyBoots *spartyBoots) : LogicGate(spartyBoots)
{
    auto x = GetX();
    auto y = GetY();
    auto w = SRFlipFlopSize.GetWidth();  // Width of the AND gate
    auto h = SRFlipFlopSize.GetHeight(); // Height of the AND gate

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

/**
 * Draw the SR flip-flop gate shape and labels.
 * @param graphics The device context to draw on
 */
void SRFlipFlop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto path = graphics->CreatePath();

    auto x = GetX();
    auto y = GetY();
    auto w = SRFlipFlopSize.GetWidth();
    auto h = SRFlipFlopSize.GetHeight();

    // Draw the rectangular body of the flip-flop
    path.AddRectangle(x - w / 2, y - h / 2, w, h);

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // Draw labels "S", "R", "Q", and "Q'" inside the flip-flop
    wxFont font(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial");
    graphics->SetFont(font, *wxBLACK);

    /// setting the pins location to be exactly where I drew them.
    mInputPins[0]->SetLocation(x - w / 2 - DefaultLineLength, y - h/4);
    mInputPins[1]->SetLocation(x - w / 2 - DefaultLineLength, y + h/4);
    mOutputPins[0]->SetLocation(x + w / 2 + DefaultLineLength, y - h/4);
    mOutputPins[1]->SetLocation(x + w / 2 + DefaultLineLength, y + h/4);

    mInputPins[0]->DrawPins(graphics, x - w / 2, y - h/4, x - w / 2 - DefaultLineLength, y - h/4);
    mOutputPins[0]->DrawPins(graphics, x + w / 2, y - h/4, x + w / 2 + DefaultLineLength, y - h/4);
    mInputPins[1]->DrawPins(graphics, x - w / 2, y + h/4, x - w / 2 - DefaultLineLength, y + h/4);
    mOutputPins[1]->DrawPins(graphics, x + w / 2, y + h/4, x + w / 2 + DefaultLineLength, y + h/4);


    graphics->DrawText("S", x - w / 2 + SRFlipFlopLabelMargin, y + h / 4 - 8);
    graphics->DrawText("R", x - w / 2 + SRFlipFlopLabelMargin, y - h / 4 - 8);
    graphics->DrawText("Q", x + w / 2 - SRFlipFlopLabelMargin - 15, y + h / 4 - 8);
    graphics->DrawText("Q'", x + w / 2 - SRFlipFlopLabelMargin - 15, y - h / 4 - 8);
}

/**
 * Test to see if we hit this SR flip-flop with a mouse click.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit
 */
bool SRFlipFlop::HitTest(int x, int y)
{
    double wid = SRFlipFlopSize.GetWidth();
    double hit = SRFlipFlopSize.GetHeight();

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
 * Empty implementation of GateCompute for SRFlipFlop.
 */
void SRFlipFlop::GateCompute()
{
    if (mInputPins[0]->isConnected() && mInputPins[1]->isConnected())
    {
        bool sValue = mInputPins[0]->getValue(); // Get value of S input
        bool rValue = mInputPins[1]->getValue(); // Get value of R input

        if (sValue && !rValue) // Set condition: S = 1, R = 0
        {
            mOutputPins[0]->setValue(true);    // Q = 1
            mOutputPins[0]->setConnect(true);
            mOutputPins[1]->setValue(false);   // Q' = 0
            mOutputPins[1]->setConnect(true);
        }
        else if (!sValue && rValue) // Reset condition: S = 0, R = 1
        {
            mOutputPins[0]->setValue(false);   // Q = 0
            mOutputPins[0]->setConnect(true);
            mOutputPins[1]->setValue(true);    // Q' = 1
            mOutputPins[1]->setConnect(true);
        }
    }
}

void SRFlipFlop::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{

}
