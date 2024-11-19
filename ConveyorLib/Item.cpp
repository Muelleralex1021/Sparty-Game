/**
 * @file Item.cpp
 * @author Alex Mueller
 */
#include "pch.h"
#include "Item.hpp"
#include "SpartyBoots.hpp"
/**
 * Destructor
 */
Item::~Item() {}

/**
 * Constructor
 * @param SpartyBoots The SpartyBoots this item is a member of
 */
Item::Item(SpartyBoots *SpartyBoots): mSpartyBoots(SpartyBoots) {}

/**
 * moves clicked item to front
 */
void Item::MoveToFront()
{
    mSpartyBoots->MoveToFront(this);
}