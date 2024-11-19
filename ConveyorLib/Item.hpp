/**
 * @file Item.hpp
 * @author tiend
 *
 *
 */

#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include "ItemVisitor.hpp"
#include "IDraggable.h"

class PinConnector;
class SpartyBoots; // Forward declaration

/**
 * Items of the application
 */
class Item : public IDraggable {
private:

    SpartyBoots *mSpartyBoots; ///< Pointer to SpartyBoots
    double mX = 0; ///< X location for the center of the item
    double mY = 0; ///< Y location for the center of the item

public:

    virtual ~Item();
    /**
    * get x coordinates
    * @return mX
    */

    double GetX() const
    {
        return mX;
    }
    /**
    * get y coordinates
    * @return my
    */

    double GetY() const
    {
        return mY;
    }

    /**
    * Set location x y
    * @param x
    * @param y
    *
    */
    virtual void SetLocation(double x, double y)
    {
        mX = x;
        mY = y;
    }

    Item() = delete;

    Item(const Item &) = delete;

    void operator=(const Item &) = delete;
    /**
   * draw function
   * @param dc
    */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> dc) = 0;
    /**
    * Check if mouse click hit
    * @param x, y
    * @return 0
    */
    virtual bool HitTest(int x, int y) = 0;
    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * accept visitor
     * @param visitor Item visitor
     */
    virtual void Accept(ItemVisitor &visitor) = 0;

    /**
     * This function checks if there is a draggable object at the given (x, y)
     * coordinates. It returns a shared pointer to the draggable object if one
     * is found; otherwise, it returns `nullptr`.
     * @param x
     * @param y
     * @return nullptr
     */
    virtual std::shared_ptr<IDraggable> HitDraggable(int x, int y) {return nullptr;}

    /**
     * Release after moving
     */
    void Release() override {}
    /**
     * Get the pointer to the SpartyBoots object
     * @return Pointer to spartyBoots object
     */
    SpartyBoots* GetSpartyBoots() { return mSpartyBoots;  }

    /**
     * Try to catch a fish at the new x,y location of the rod end
     * @param pinConnector pin we are trying to catch from
     * @param lineEnd The line end point
     * @return true if caught
     */
    virtual bool Catch(PinConnector* pinConnector , wxPoint lineEnd) {return false;}

    virtual void MoveToFront() override;

protected:

    Item(SpartyBoots *SpartyBoots);
};

#endif // ITEM_H
