/**
 * @file OutputPin.cpp
 * @author tiend
 */


#include "pch.h"
#include "OutputPin.h"
#include "SpartyBoots.hpp"

OutputPin::OutputPin(SpartyBoots *spartyBoots): LogicItem(spartyBoots)
{
    mConnector.push_back(std::make_shared<PinConnector>(spartyBoots, this));
}

/**
 * Draw AndGate with virtual pixel
 * @param graphics
 */
void OutputPin::Draw(std::shared_ptr<wxGraphicsContext> graphics) {}

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
void OutputPin::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{
    // Create a path to draw the AND gate shape
    auto path = graphics->CreatePath();

    int pinRadius = PinSize / 2;

    graphics->SetPen(*wxBLACK_PEN);
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

    //check if all the connectors are connected. If yes, create a new pinConnector so you can link multiple inputs to 1 output
    // int count = 0;
    // for (auto connector : mConnector) {
    //     if (connector->getCaught() == nullptr)
    //     {
    //         count++;
    //     }
    // }
    // if (count == 0)
    // {
    //     mConnector.insert(mConnector.begin(), std::make_shared<PinConnector>(GetSpartyBoots(), this));
    // }


    //Draw the connectors
    for (auto connector : mConnector) {
        connector->Draw(graphics);
    }
}


/**
 * Test to see if we hit this OR gate with a mouse click.
 * @param x X position to test
 * @param y Y position to test
 * @return true

 * * if hit
 */
bool OutputPin::HitTest(int x, int y)
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

void OutputPin::Accept(ItemVisitor &visitor) {}
/**
 * updates values of pins
 */
void OutputPin::UpdateValues(){
    for (auto connection : mConnector)
    {
        //updating value every input pin of the connection from outputPin
        if (connection->getCaught() != nullptr)
        {
            connection->getCaught()->setValue(mValue);
            connection->getCaught()->setConnect(mConnected);
        }
    }

}

/**
 *
 * @param x
 * @param y
 * @return
 */
std::shared_ptr<IDraggable> OutputPin::HitDraggable(int x, int y)
{
    for (auto pinConnector : mConnector)
    {
        if(pinConnector->HitTest(x, y))
        {
            return pinConnector;
        }
    }

    return nullptr;
}