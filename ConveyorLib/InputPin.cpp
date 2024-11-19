/**
 * @file InputPin.cpp
 * @author Alex Mueller
 */

#include "pch.h"
#include "InputPin.h"
#include "OutputPin.h"

/**
 * Constructor
 * @param spartyBoots
 */
InputPin::InputPin(SpartyBoots *spartyBoots): LogicItem(spartyBoots) {}

/**
 * setter for mLine
 * @param line
 */
void InputPin::SetLine(PinConnector *line)
{
    if (line != nullptr)
    {
        mConnected = line->getOwner()->isConnected();
    }
    mLine = line;
}

/**
 * Draw AndGate with virtual pixel
 * @param graphics
 */
void InputPin::Draw(std::shared_ptr<wxGraphicsContext> graphics) {}

/**
 * Draw the pins of AndGate by calling from LogicItem
 * @param graphics
 * @param start_x the starting position of tail of pin
 *
 * @param start_y  starting position of tail of pin
 * @param end_x where pin end (and where the pin is)
 * @param end_y where pin end (and
 * where the pin is)
 */
void InputPin::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{
    // Create a path to draw the AND gate shape
    auto path = graphics->CreatePath();

    int pinRadius = PinSize / 2;

    graphics->SetPen(*wxBLACK_PEN);

    //This part is in case the pin is connected to a line. When that happens, we update the pins' value and connected
    // if (mLine != nullptr)
    // {
    //     if (mLine->getOwner()->isConnected())
    //     {
    //         mConnected = true;
    //     }
    //
    // }
    // else
    // {
    //     mConnected = false;
    // }

    if (mConnected)
    {
        if (getValue())
        {
            graphics->SetBrush(ConnectionColorOne); // Gray color for the pin circles
        }
        else
        {
            graphics->SetBrush(ConnectionColorZero); // Gray color for the pin circles
        }
    }
    else
    {
        graphics->SetBrush(ConnectionColorUnknown); // Gray color for the pin circles
    }

    // Left pins (inputs) should be vertically aligned
    wxPoint2DDouble startPin(start_x, start_y); // Top-left input pin
    wxPoint2DDouble endPin(end_x, end_y);       // Bottom-left input pin

    // Create the path for the AND gate
    path.MoveToPoint(startPin);  // Start at the bottom left
    path.AddLineToPoint(endPin); // Draw the left vertical line

    // Draw the path
    graphics->DrawPath(path);

    // Draw the pins as circles
    graphics->DrawEllipse(endPin.m_x - pinRadius, endPin.m_y - pinRadius, PinSize, PinSize); // First input pin
}

/**
 * Test to see if we hit this OR gate with a mouse click.
 * @param x X position to test
 * @param y Y position to test
 * @return true

 * * if hit
 */
bool InputPin::HitTest(int x, int y)
{
    double radius = PinSize / 2.0; // Radius of the circular pin

    // Calculate the distance from the center of the pin to the point (x, y)
    double centerX = GetX();
    double centerY = GetY();
    double testX = x - GetX();
    double testY = y - GetY();

    // Calculate the squared distance to avoid using sqrt for performance
    double distanceSquared = testX * testX + testY * testY;

    // Check if the point is within the radius of the pin
    if (distanceSquared <= radius * radius)
    {
        // We are inside the circular pin
        return true;
    }

    return false;
}

/**
 * accepts the item visitor
 * @param visitor
 */
void InputPin::Accept(ItemVisitor &visitor) {}

/**
 * connect to a pin at the new x,y location of the wire end
 * @param pinConnector we are trying to catch from
 * @param lineEnd The line end point
 * @return true if connected
 */
bool InputPin::Catch(PinConnector *pinConnector, wxPoint lineEnd)
{
    double pinRadius = PinSize/2;
    double centerX = GetX();
    double centerY = GetY();
    auto relativeX = lineEnd.x - centerX;
    auto relativeY = lineEnd.y - centerY;


    if( (relativeX * relativeX + relativeY * relativeY) <
            pinRadius  * pinRadius )
    {
        if(mLine != nullptr)
        {
            mLine->SetCaught(nullptr);
            //transition into not connected state when disconnected
            mConnected = false;
        }

        pinConnector->SetCaught(this);
    }

    return false;
}
