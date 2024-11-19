/**
 * @file IDraggable.h
 * @author Alex Mueller
 *
 *
 */
 
#ifndef IDRAGGABLE_H
#define IDRAGGABLE_H



/**
 * Interface for something in the aquarium that is draggable
 */
class IDraggable
{
public:
    /**
     * Set the location of the draggable thing
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) = 0;

    /**
     * This draggable thing should be moved to the front
     * of the list of items.
     */
    virtual void MoveToFront() = 0;
    /**
     * Release after moving
     */
    virtual void Release() = 0;
};


#endif //IDRAGGABLE_H

