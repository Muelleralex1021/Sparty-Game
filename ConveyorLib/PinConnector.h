/**
 * @file PinConnector.h
 * @author Alex Mueller
 *
 *
 */
 
#ifndef PINCONNECTOR_H
#define PINCONNECTOR_H

#include "Item.hpp"

class InputPin;
class OutputPin;

/**
 * Class for pin connection
 * derived from item
 */
class PinConnector : public Item {
private:
    /// Location of the line end when dragging
    wxPoint mLineEnd;

    /// Are we dragging the line?
    bool mDragging = false;

    /// Have we caught anything?
    InputPin*  mCaught = nullptr;

    /// Pin that owns this connector
    OutputPin* mOwner = nullptr;
public:
    /**
     * Constructor for pin connector
     * @param spartyBoots
     * @param mOwner
     */
    PinConnector(SpartyBoots *spartyBoots, OutputPin* mOwner);
    /**
     * Getter for Owner
     * @return mOwner
     */
    OutputPin* getOwner(){ return mOwner; }
    /**
     * Getter for caught boolean
     * @return mCaught
     */
    InputPin* getCaught(){ return mCaught; }
    void SetLocation(double x, double y) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override;
    void Accept(ItemVisitor &visitor) {};
    void Release() override;
    void SetCaught(InputPin* caught);
    void MoveToFront() override;

};



#endif //PINCONNECTOR_H
