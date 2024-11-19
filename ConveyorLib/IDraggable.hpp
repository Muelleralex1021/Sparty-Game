/**
 * @file IDraggable.h
 * @author bdean
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_IDRAGGABLE_H
#define PROJECT1_CONVEYORLIB_IDRAGGABLE_H

class IDraggable
{
private:

public:
    /**
     * Set the location of the draggable thing
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) = 0;


    /**
     * Release after moving
     */
    virtual void Release() {};
};

#endif //PROJECT1_CONVEYORLIB_IDRAGGABLE_H
