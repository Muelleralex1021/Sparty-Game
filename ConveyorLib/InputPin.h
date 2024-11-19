/**
 * @file InputPin.h
 * @author tiend
 *
 *
 */

#ifndef INPUTPIN_H
#define INPUTPIN_H

#include "LogicItem.hpp"
#include "PinConnector.h"


/**
 *Class of input pins
* Derived from LogicItem, which is derived from Item
* */
class InputPin : public LogicItem {
private:
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

    /// whether pin is connected or not
    bool mConnected = false;
    /// value of pin
    bool mValue = false;
    /// pointer to output pin it's connected to. Only 1 output pin since an input can only take 1 output
    std::shared_ptr<OutputPin> mConnectedOutputPin = nullptr;

    /// Pin line we are connected to
    PinConnector* mLine = nullptr;

public:
    InputPin(SpartyBoots *spartyBoots);
    /**
     * Set the line that has caught this inputpin
     * @param line
     * @param spartyBoots so you can initiate the new pinConnector within the function
     */
    void SetLine(PinConnector* line);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y) override;
    bool HitTest(int x, int y) override;
    void Accept(ItemVisitor &visitor) override;
    /**
    *set value of pin
    *@param outputValue
    ** */
    void setValue(bool outputValue)
    {
        mValue = outputValue;
    }
    /**
    *get value of pin
    *@return mValue
    ** */
    bool getValue()
    {
        return mValue;
    }
    /**
    *check if connected
    *@return mConnected
    ** */
    bool isConnected()
    {
        return mConnected;
    }
    /**
    *set Connection status
    *@param connection
    ** */
    void setConnect(bool connection)
    {
        mConnected = connection;
    }


    /**
    *set output pin connected to
    *@param outputPin
    ** */
    void SetConnectedOutputPin(std::shared_ptr<OutputPin> outputPin) {
        mConnectedOutputPin = outputPin;
        mConnected = (outputPin != nullptr);  // Update connection status based on pointer
    }
    /**
    * Get outputpin
    *@return output pin
    ** */
    std::shared_ptr<OutputPin> GetConnectedOutputPin() const {
        return mConnectedOutputPin;
    }
    /**
     * Try to catch a fish at the new x,y location of the rod end
     * @param pinConnector Rod we are trying to catch from
     * @param lineEnd The line end point
     * @return true if caught
     */
    bool Catch(PinConnector *pinConnector, wxPoint lineEnd) override;
};

#endif // INPUTPIN_H
