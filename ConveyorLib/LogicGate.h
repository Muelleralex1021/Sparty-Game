/**
 * @file LogicGate.h
 * @author tiend
 *
 *
 */

#ifndef LOGICGATE_H
#define LOGICGATE_H

#include "LogicItem.hpp"
#include "InputPin.h"
#include "OutputPin.h"

/**
 * Specifically gates that utilizes logic and pins. Derived from logicitem
 */
class LogicGate : public LogicItem {
protected:
    /// vector containing input pins
    std::vector<std::shared_ptr<InputPin>> mInputPins;
    /// vector containing output pins
    std::vector<std::shared_ptr<OutputPin>> mOutputPins;

public:
    /**
     * Accept a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ItemVisitor &visitor) override
    {
        visitor.VisitLogicGate(this);
    }
    /**
     * getter for input pins
     * @return mInputPins
     */
    std::vector<std::shared_ptr<InputPin>> GetInputPins() { return mInputPins; }
    /**
     * getter for output pins
     * @return mOutputPins
     */
    std::vector<std::shared_ptr<OutputPin>> GetOutputPins() { return mOutputPins; }
protected:
    /**
 *Call the constructor from logic item, subsequently item
 *@param spartyBoots the mspartyboots object
*/

    LogicGate(SpartyBoots *spartyBoots): LogicItem(spartyBoots) {}
};

#endif // LOGICGATE_H
