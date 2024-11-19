/**
 * @file LogicItem.cpp
 * @author bdean
 */
#include "pch.h"
#include "LogicItem.hpp"

/**
 * Draw the pins of AndGate by calling from LogicItem
 * @param graphics
 * @param start_x
 * @param start_y
 * @param end_x
 * @param end_y
 */
void LogicItem::DrawPins(std::shared_ptr<wxGraphicsContext> graphics, int start_x, int start_y, int end_x, int end_y)
{}

/**
 * computes pin connections
 */
void LogicItem::GateCompute() {}
