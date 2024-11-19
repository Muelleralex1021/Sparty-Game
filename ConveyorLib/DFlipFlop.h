/**
 * @file DFlipFlop.h
 * @author Alex Mueller
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_DFLIPFLOP_H
#define PROJECT1_CONVEYORLIB_DFLIPFLOP_H

#include <memory>
#include <vector>
#include "InputPin.h"
#include "LogicGate.h"
#include "OutputPin.h"


/**
 * Class representing a D Flip Flop
 */
class DFlipFlop : public LogicGate
{
private:
public:
    DFlipFlop(SpartyBoots *spartyBoots);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override;
    void GateCompute() override;
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y) override;
};

#endif //PROJECT1_CONVEYORLIB_DFLIPFLOP_H
