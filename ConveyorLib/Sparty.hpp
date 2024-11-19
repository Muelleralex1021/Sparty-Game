/**
 * @file Sparty.hpp
 * @author trevo
 *
 *
 */

#ifndef SPARTY_HPP
#define SPARTY_HPP
#include "Item.hpp"
#include "LogicItem.hpp"
#include "InputPin.h"

/**
*Sparty Class
*/
class Sparty : public LogicItem {
private:
    /// x coord
    int mX;
    /// y coord
    int mY;
    /// height
    int mHeight;
    /// pin x
    int mPinX;
    /// pin y
    int mPinY;
    /// kick duration
    double mKickDuration;
    /// kick speed
    int mKickSpeed;
    /// width
    double mWidth;
    /// boot angle
    double mBootAngle = 0.0;
    /// Kick returning
    bool mReturning = false;
    ///kicking member variable
    bool mIsKicking = false;

    ///Is there a sensor so drawing can compensate
    bool mIsSensor = false;

    /// vector containing input pins
    std::vector<std::shared_ptr<InputPin>> mInputPins;

    /// Image for the sparty background.
    wxImage mSpartyBackImage;

    /// The bitmap for sparty background.
    wxBitmap mSpartyBackBitmap;

    /// The Image for the Sparty boot.
    wxImage mSpartyBootImage;

    /// The bitmap for Sparty boot.
    wxBitmap mSpartyBootBitmap;

    /// The Image for the Sparty front.
    wxImage mSpartyFrontImage;

    /// The bitmap for Sparty front.
    wxBitmap mSpartyFrontBitmap;

public:
    Sparty(SpartyBoots *spartyBoots, int x, int y, int height, int pinX, int pinY, double kickDuration, int kickSpeed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override
    {
        return false;
    };
    void Update(double elapsed) override;
    /**
     * Accept a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ItemVisitor &visitor) override
    {
        visitor.VisitSparty(this);
    }

    /**
     * retrieve kick speed
     * @return kick speed member variable
     */
    int GetKickSpeed() const
    {
        return mKickSpeed;
    };
   /**
    * @param graphics Shared pointer to the `wxGraphicsContext` used for rendering the pins.
    * @param start_x The x-coordinate of the pin's starting point.
    * @param start_y The y-coordinate of the pin's starting point.
    * @param end_x The x-coordinate of the pin's ending point.
    * @param end_y The y-coordinate of the pin's ending point.
    */
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)override {};
    /**
     * retrieve pin for result
     * @return mInputPin
     */
    std::vector<std::shared_ptr<InputPin>> getPin(){ return mInputPins; };

    /**
     * retrieves if sparty is kicking
     * @return kicking member variable
     */
    bool IsKicking() {return mIsKicking;};

    /**
     * sets if sparty is kicking or not
     * @param kicking to set mKicking to
     */
    void SetKicking(bool kicking) {mIsKicking = kicking;};
    /**
     * setter for the sensor
     * @param isSensor
     */
    void SetSensor(bool isSensor){ mIsSensor = isSensor;};

};

#endif // SPARTY_HPP
