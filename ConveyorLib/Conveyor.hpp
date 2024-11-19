/**
 * Conveyor item class declaration
 * @file Conveyor.hpp
 * @author Alex Mueller
 */

#ifndef CONVEYORLIB_CONVEYOR_HPP
#define CONVEYORLIB_CONVEYOR_HPP

#include "Item.hpp"
#include "Product.h"
/**
 * Conveyor Class
 */
class Conveyor : public Item {
    /// The height of the conveyor.
    int mHeight;

    /// The speed of the conveyor.
    int mSpeed;

    /// The X position of the panel.
    int mPanelX;

    /// The Y position of the panel.
    int mPanelY;

    /// Whether the belt is running.
    bool mRunning = false;

    /// The image for the conveyor background.
    wxImage mBackgroundImage;

    /// The bitmap for the conveyor background.
    wxBitmap mBackgroundBitmap;

    /// The image for the conveyor belt.
    wxImage mBeltImage;

    /// The bitmap for the conveyor belt.
    wxBitmap mBeltBitmap;

    /// The image for the panel (start).
    wxImage mPanelStartImage;

    /// The bitmap for the panel (start).
    wxBitmap mPanelStartBitmap;

    /// The image for the panel (stop).
    wxImage mPanelStopImage;

    /// The bitmap for the panel (stop).
    wxBitmap mPanelStopBitmap;

    /// The position of the conveyor belt.
    int mBeltOffset = 0;

public:
    Conveyor(SpartyBoots *game, double x, double y, int height, int speed, int panelX, int panelY);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override;
    void Update(double elapsed) override;
    void SetProductClip(std::shared_ptr<Product> item);
    /**
     * getter for the boolean that indicates if conveyor is running
     * @return mRunning
     */
    bool IsRunning()
    {
        return mRunning;
    };
    /**
     * Accept a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ItemVisitor &visitor) override
    {
        visitor.VisitConveyor(this);
    }
};

#endif
