/**
 * @file LastProductVisitor.hpp
 * @author Alex Mueller
 *
 *
 */

#ifndef LASTPRODUCTVISITOR_HPP
#define LASTPRODUCTVISITOR_HPP

#include "Beam.hpp"
#include "Conveyor.hpp"
#include "ItemVisitor.hpp"
#include "Product.h"
#include "ScoreBoard.hpp"
#include "Sensor.h"
#include "Sparty.hpp"

/**
 * visitor for the last product in a level
 */
class LastProductVisitor : public ItemVisitor {
public:
    /**
     * Constructor for the Last Porduct Visitor
     * @param currentTime
     */
    explicit LastProductVisitor(double currentTime): mCurrentTime(currentTime) {}
    /**
     * getter for IsInBeam
     * @return mIsInBeam
     */
    bool IsProductInBeam() { return mIsInBeam; }
    /**
     * getter for beam
     * @return mBeam
     */
    Beam* GetBeam() { return mBeam; }
    /**
     * getter for sensor
     * @return mSensor
     */
    Sensor* GetSensor() { return mSensor; }
    /**
     * getter for product in beam
     * @return mProductInBeam
     */
    Product* GetProductInBeam() {return mProductInBeam; }
    /**
     * getter for sparty
     * @return mSparty
     */
    Sparty* GetSparty() { return mSparty; }
    /**
     * getter for gates
     * @return mGates
     */
    std::vector<LogicGate*> GetGates() { return mGates; }

    /**
     * Add for scoreboard
     * @param scoreboard
     */
    void VisitScoreboard(ScoreBoard *scoreboard) override
    {
        // The scoreboard should be at the front of the list.
        mScoreboard = scoreboard;
    }
    /**
     * Add for beam
     * @param beam
     */
    void VisitBeam(Beam *beam) override
    {
        // The beam should be at the front of the list.
        mBeamY = beam->GetY();
        mBeam = beam;
    }
    /**
     * Add for sensor
     * @param sensor
     */
    void VisitSensor(Sensor *sensor) override
    {
        mSensor = sensor;
    }
    /**
     * Add for conveyor
     * @param conveyor
     */
    void VisitConveyor(Conveyor *conveyor) override
    {
        mConveyorCenter = conveyor->GetX() - 25;
    }
    /**
     * Add for sparty
     * @param sparty
     */
    void VisitSparty(Sparty *sparty) override
    {
        mSparty = sparty;
    }

    void VisitLogicGate(LogicGate *logicGate) override
    {
        mGates.push_back(logicGate);
    }
    /**
     * Getter to check the result after visiting all products
     * @return
     */
    bool HasLastProductPassed() const
    {
        return mLastProductPassed;
    }
    /**
     * Add for product
     * @param product
     */
    void VisitProduct(Product *product) override
    {
        // Only check if this is marked as the last product
        if (product->GetY() > (mBeamY + 10) || product->GetX() < mConveyorCenter)
        {
            if (!(product->GetScoreAccountedFor()))
            {
                if ((product->ToKick() == product->WasKick()))
                {
                    mScoreboard->ChangeScore(true);
                }
                else
                {
                    mScoreboard->ChangeScore(false);
                }
                product->SetScoreDrawn();
            }
        }
        if (product->IsLast())
        {
            // If product has passed the beam
            if (product->GetY() > (mBeamY) || product->GetX() < mConveyorCenter)
            {
                mLastProductPassed = true;
            }
        }
        if (!(product->WasKick()) && (mBeamY - product->GetY() >= 0) && (mBeamY - product->GetY() <= 50))
        {
            // if (mSensor != nullptr)
            // {
            //     mSensor->ActivatePins(product->GetContent());
            // }
            mIsInBeam = true;
            mProductInBeam = product;
            // mBeam->SetItemTouchingBeam(true);
            // if (mSparty->IsKicking())
            // {
            //     product->SetKick();
            //     mSparty->SetKicking(false);
            // }
        }
        // if (!mProductInBeam)
        // {
        //     if (mSensor != nullptr)
        //     {
        //         mSensor->ResetPins();
        //     }
        //     mBeam->SetItemTouchingBeam(false);
        // }

    }

private:
    /// The current time
    double mCurrentTime = 0;

    /// The Y position of the beam
    double mBeamY = 0;

    /// The center X of the conveyor
    double mConveyorCenter = 0;

    /// Whether the last product passed the beam
    bool mLastProductPassed = false;

    /// The scoreboard being used in this instance
    ScoreBoard *mScoreboard = nullptr;
    /// sensor being used in instance
    Sensor *mSensor = nullptr;
    ///beam being used in instance
    Beam *mBeam = nullptr;
    ///product in beam
    bool mIsInBeam = false;
    ///sparty being used in instance
    Sparty *mSparty = nullptr;
    ///The product in the beam
    Product* mProductInBeam = nullptr;
    ///The gates in the game
    std::vector<LogicGate*> mGates;
};

#endif // LASTPRODUCTVISITOR_HPP
