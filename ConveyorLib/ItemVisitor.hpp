/**
 * @file ItemVisitor.hpp
 * @author trevo
 *
 *
 */

#ifndef ITEMVISITOR_HPP
#define ITEMVISITOR_HPP

// #include "Beam.hpp"
// #include "Conveyor.hpp"
// #include "Sensor.h"
// #include "LogicGate.h"

class ScoreBoard;
class Sparty;
class Beam;
class Product;
class Item;
class LogicGate;
class Sensor;
class Conveyor;

/**
 * Visitor for Items
 */
class ItemVisitor {
public:
    virtual ~ItemVisitor() = default;
    /**
     * Add other item types as needed
     * @param item
     */
    virtual void VisitItem(Item *item) {}
    /**
     * Add for visit logic gates
     * @param logicGate
     */
    virtual void VisitLogicGate(LogicGate *logicGate) {}
    /**
     * Add for visit sensor
     * @param sensor
     */
    virtual void VisitSensor(Sensor *sensor) {};
    /**
     * Add for conveyer
     * @param conveyor
     */
    virtual void VisitConveyor(Conveyor *conveyor) {};
    /**
     * add for beam
     * @param beam
     */
    virtual void VisitBeam(Beam *beam) {};
    /**
     * add for sparty
     * @param sparty
     */
    virtual void VisitSparty(Sparty *sparty) {};
    /**
     * add for scoreboard
     * @param scoreboard
     */
    virtual void VisitScoreboard(ScoreBoard *scoreboard) {};
    /**
     * Add for product
     * @param product
     */
    virtual void VisitProduct(Product *product) = 0;
};

#endif // ITEMVISITOR_HPP
