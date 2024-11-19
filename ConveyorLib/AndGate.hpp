/**
 * @file AndGate.hpp
 * @author Alex Mueller
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_ANDGATE_H
#define PROJECT1_CONVEYORLIB_ANDGATE_H

#include <memory>
#include <vector>
#include "InputPin.h"
#include "LogicGate.h"
#include "OutputPin.h"
/**
 *And Gate class
 *
 */
class AndGate : public LogicGate {
private:
public:
    AndGate(SpartyBoots *spartyBoots);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y) override;
    bool HitTest(int x, int y) override;
    /**
    *Compute the logic. Depending on the object/gate
    ** */
    void GateCompute() override;
};

#endif // PROJECT1_CONVEYORLIB_ANDGATE_H
