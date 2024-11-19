/**
 * @file SRFlipFlop.h
 * @author bdean
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_SRFLIPFLOP_H
#define PROJECT1_CONVEYORLIB_SRFLIPFLOP_H

#include <memory>
#include <vector>
#include "InputPin.h"
#include "LogicGate.h"
#include "OutputPin.h"

/**
 * Class for SRFlipFlops
 * derived from LogicGate
 */
class SRFlipFlop : public LogicGate
{
private:
public:

    SRFlipFlop(SpartyBoots *spartyBoots);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y)override;
    void DrawPins(std::shared_ptr<wxGraphicsContext> graphics,
                  int start_x,
                  int start_y,
                  int end_x,
                  int end_y) override;
    void GateCompute()override;
};

#endif //PROJECT1_CONVEYORLIB_SRFLIPFLOP_H
