/**
 * @file OutputPin.h
 * @author tiend
 *
 *
 */

#ifndef OUTPUTPIN_H
#define OUTPUTPIN_H

#include "LogicItem.hpp"
#include "InputPin.h"

class InputPin;
class PinConnector;
/**
 *Class of output pins
* Derived from LogicItem, which is derived from Item
* */
class OutputPin : public LogicItem {
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
    /// List of shared pointers to InputPin objects
    std::vector<std::shared_ptr<InputPin>> mConnectedInputPins;

    ///List of shared pointers to connector
    std::vector<std::shared_ptr<PinConnector>> mConnector;

public:
    /**
     * Constructor for output pin
     * @param spartyBoots
     */
    OutputPin(SpartyBoots *spartyBoots);
    std::shared_ptr<IDraggable> HitDraggable(int x, int y) override;
    /**
     * Getter for Connector
     * @return mConnector
     */
    std::vector<std::shared_ptr<PinConnector>> getConnector() {return mConnector;}
    /**
     * Adds a connetor
     * @param connection
     */
    void AddConnector(std::shared_ptr<PinConnector> connection) {mConnector.insert(mConnector.begin(), connection);}
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y) override;
    bool HitTest(int x, int y) override;
    void Accept(ItemVisitor &visitor) override;
    /**
    *set value of pin
    *@param inputValue
    ** */
    void setValue(bool inputValue)
    {
        mValue = inputValue;
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
    *set input pin connected to
    *@param inputPin
    ** */
    void AddConnectedInputPin(std::shared_ptr<InputPin> inputPin) {
        mConnectedInputPins.push_back(inputPin);
        mConnected = !mConnectedInputPins.empty();  // Update connection status
    }
    /**
    * Get inputpins
    *@return inputpins vector
    ** */
    std::vector<std::shared_ptr<InputPin>> GetConnectedInputPin() const {
        return mConnectedInputPins;
    }

    /**
    * Connect outputpin to inputpin. Since you'll only be dragging outputpin to input pins, this function will only be in outputpin
    *@param inputPin
    ** */
    void ConnectPins(std::shared_ptr<InputPin> inputPin) {
        // Add the input pin to the connected input pins list
        mConnectedInputPins.push_back(inputPin);
        //Setting the input pin to the value of connected output
        inputPin->setValue(mValue);
        // Set the current OutputPin as the connected output pin for the InputPin
        inputPin->SetConnectedOutputPin(std::shared_ptr<OutputPin>(this)); // Assuming InputPin has a function to do this
        // Update connection status
        mConnected = !mConnectedInputPins.empty();
    }

    void UpdateValues();

};

#endif // OUTPUTPIN_H
