/**
 * @file SpartyBoots.hpp
 * @author Alex Mueller
 *
 *
 */

#ifndef SPARTYBOOTS_H
#define SPARTYBOOTS_H

#include <memory>
#include <vector>
#include "Conveyor.hpp"
#include "ItemVisitor.hpp"
#include "PinConnector.h"
/**
 * Initialize Item class
 *
 */
class Item;
/**
 * Our SpartyBoots that we will draw in
 *
 */
class SpartyBoots {
private:
    /// All of the items to populate our SpartyBoots
    std::vector<std::shared_ptr<Item>> mItems;
    std::unique_ptr<wxBitmap> mBackground; ///< Background image to use
    double mScale;                         ///< scale of virtual pixel
    double mXOffset;                       ///< Xoffset to calculate virtual pixel
    double mYOffset;                       ///< Yoffset to calculate virtual pixel
    int mCurrentLevel;                     ///< keep track of current level
    int mPixelWidth;
    int mPixelHeight;
    /// window parent for refreshing level change
    /// parent window object
    wxWindow *mParent;
    /// timer for showing notice
    double mNoticeTimer = 0;
    /// boolean of whather notice should be shown
    bool mShowingBegin = true;
    ///boolean of wheather notice should be shown
    bool mShowingComplete = false;
    ///complete notice timer
    double mCompleteTimer = 0;
    ///has level ended
    bool mLevelEnd = false;
    ///level ended timer
    double mLevelEndTimer = 0;



public:
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int, int);
    SpartyBoots(wxWindow *parent);
    /**
     * return Scale to calculate virtual pixel
     * @returns mScale
    */
    double getScale()
    {
        return mScale;
    }
    /**
    * return XOffset to calculate virtual pixel
    * @returns mXOffset
    */
    double getXOffset()
    {
        return mXOffset;
    }
    /**
    * return YOffset to calculate virtual pixel
    * @returns mYOffset
    */
    double getYOffset()
    {
        return mYOffset;
    }
    void Add(std::shared_ptr<Item> item);
    std::shared_ptr<IDraggable> HitTest(int x, int y);
    void OnLeftDown(int x, int y);
    void OnLevelSelect(int level);
    void LevelLoad(int level);

    /**
 * Insert the item to the list of item
 * @param item
 */
    void InsertItem(std::shared_ptr<Item> item);
    void Update(double elapsed);
    /// function for getting items
    std::vector<std::shared_ptr<Item>> GetItems()
    {
        return mItems;
    };
    /// Attempts to catch an input pin and connect them
    void TryToCatch(PinConnector* pinConnector, wxPoint lineEnd);
    /// Moves an item to the front of the drawing order
    void MoveToFront(Item* item);
    /// function for topologically calculating the gates. Needs to know the sensor and beam output pins to start, the sparty pins to stop,
    /// and the logic gates to check.
    void TopologicalComputing(Sensor* sensor, Beam* beam, Sparty* sparty, std::vector<LogicGate*> gates);

};

#endif // SPARTYBOOTS_H
