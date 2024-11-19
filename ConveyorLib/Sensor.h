/**
 * @file Sensor.h
 * @author Alex Mueller
 *
 *
 */

#ifndef SENSOR_H
#define SENSOR_H
#include "LogicItem.hpp"
#include "OutputPin.h"

/**
 * Sensor Class
 */
class Sensor : public LogicItem {

public:
    Sensor(SpartyBoots *spartyBoots, int x, int y, std::vector<wxString>);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override
    {
        return false;
    };
    /**
     * Accept a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ItemVisitor& visitor) override { visitor.VisitSensor(this); }

    void ActivatePins(std::vector<wxString> productContent);
   /**
    * function for drawing pins
    * @param graphics Shared pointer to the `wxGraphicsContext` used for drawing.
    * @param start_x The x-coordinate of the starting point of the pin.
    * @param start_y The y-coordinate of the starting point of the pin.
    * @param end_x The x-coordinate of the ending point of the pin.
    * @param end_y The y-coordinate of the ending point of the pin.
    */
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)override {};

    void ResetPins();
    /**
     * getter for output pins
     * @return mOutputPins
     */
    std::vector<std::shared_ptr<OutputPin>> getPins() {return mOutputPins;}

private:
    /// X location of sensor
    int mX;
    /// Y location of sensor
    int mY;

    /// vector containing output pins
    std::vector<std::shared_ptr<OutputPin>> mOutputPins;

    /// Children of sensor
    std::vector<wxString> mChildren;

    /// Image for the sparty background.
    wxImage mSensorCableImage;

    /// The bitmap for sparty background.
    wxBitmap mSensorCableBitmap;

    /// The Image for the Sparty boot.
    wxImage mSensorCameraImage;

    /// The bitmap for Sparty boot.
    wxBitmap mSensorCameraBitmap;

    /// The Image for the Sparty boot.
    wxImage mBasketballImage;

    /// The bitmap for Sparty boot.
    wxBitmap mBasketballBitmap;

    /// The Image for the Sparty boot.
    wxImage mFootballImage;

    /// The bitmap for Sparty boot.
    wxBitmap mFootballBitmap;

    /// The Image for the Sparty boot.
    wxImage mIzzoImage;

    /// The bitmap for Sparty boot.
    wxBitmap mIzzoBitmap;

    /// The Image for the Sparty boot.
    wxImage mSmithImage;

    /// The bitmap for Sparty boot.
    wxBitmap mSmithBitmap;

    /// The Image for the Sparty boot.
    wxImage mWolverineImage;

    /// The bitmap for Sparty boot.
    wxBitmap mWolverineBitmap;
};

#endif // SENSOR_H
