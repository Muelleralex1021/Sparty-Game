/**
 * @file ProductUpdateVisitor.hpp
 * @author trevo
 *
 *
 */

#ifndef PRODUCTUPDATEVISITOR_HPP
#define PRODUCTUPDATEVISITOR_HPP
#include "Conveyor.hpp"
#include "ItemVisitor.hpp"
#include "Product.h"
#include "Sparty.hpp"

/**
 * visitor class for product updates
 */
class ProductUpdateVisitor : public ItemVisitor {
public:
    /**
     * Constructor for ProductUpdateVisitor
     * @param elapsed
     */
    explicit ProductUpdateVisitor(double elapsed): mElapsed(elapsed) {}
    /**
     * Add visiting conveyor
     * @param conveyor
     */
    void VisitConveyor(Conveyor *conveyor) override
    {
        mIsActive = conveyor->IsRunning();
    }
    /**
     * Add visiting for sparty
     * @param sparty
     */
    void VisitSparty(Sparty *sparty) override
    {
        mKickSpeed = sparty->GetKickSpeed();
    }

    /**
     * function for updating product item
     * @param product product to check
     */
    void VisitProduct(Product *product) override
    {
        if (!mIsActive)
            return;
        // Get current product speed
        int speed = product->GetSpeed();
        product->SetLocation(product->GetX(), (product->GetY() + (mElapsed * speed)));
        if (product->WasKick())
        {
            product->SetLocation((product->GetX() - (mElapsed * mKickSpeed)), (product->GetY()));
        }
    }


private:
    /// The amount of time elapsed this tick
    double mElapsed;

    /// The speed of the kick
    int mKickSpeed;

    /// Whether to run an update this tick
    bool mIsActive;


};

#endif // PRODUCTUPDATEVISITOR_HPP
