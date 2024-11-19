/**
 * @file NotGate.hpp
 * @author Alex Mueller
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_NOTGATE_H
#define PROJECT1_CONVEYORLIB_NOTGATE_H

#include <memory>
#include <vector>
#include "InputPin.h"
#include "LogicGate.h"
#include "OutputPin.h"
/**
 *Class NotGates
* Derived from LogicGate, which is derived from LogicItem, which is derived from Item
* */
class NotGate : public LogicGate {
private:
public:
    /// Constructor
    NotGate(SpartyBoots *spartyBoots);
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y) override;
    /// Draw this NOT gate
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override;
    /**
    *Compute the logic. Depending on the object/gate
    ** */
    void GateCompute() override;
};

#endif // PROJECT1_CONVEYORLIB_NOTGATE_H
