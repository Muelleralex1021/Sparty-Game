/**
 * @file LogicItem.hpp
 * @author bdean
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_LOGICITEM_H
#define PROJECT1_CONVEYORLIB_LOGICITEM_H

#include "Item.hpp"
/**
 * Item that utilizes logic + pins
 */

class LogicItem : public Item {
private:
public:

    virtual void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y) = 0;
    /**
     *Compute the logic. Depending on the object/gate
     */
    virtual void GateCompute();

protected:
    /**
     *Call the constructor from item
     *@param spartyBoots the mspartyboots object
     */
    LogicItem(SpartyBoots *spartyBoots): Item(spartyBoots) {}
};

#endif // PROJECT1_CONVEYORLIB_LOGICITEM_H
