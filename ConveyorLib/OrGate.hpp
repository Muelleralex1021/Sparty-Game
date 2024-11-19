/**
 * @file OrGate.hpp
 * @author Alex Mueller
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_ORGATE_HPP
#define PROJECT1_CONVEYORLIB_ORGATE_HPP

#include <memory>
#include <vector>
#include "InputPin.h"
#include "LogicGate.h"
#include "OutputPin.h"

/**
 * Class that implements an OR gate.
 */
class OrGate : public LogicGate {
private:
public:
    OrGate(SpartyBoots *spartyBoots);
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override;
    /**
    *Compute the logic. Depending on the object/gate
    ** */
    void GateCompute() override;
};

// need this comment to commit for some reason feel free to delete
#endif // PROJECT1_CONVEYORLIB_ORGATE_HPP
