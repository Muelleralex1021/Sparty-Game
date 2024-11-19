/**
 * @file Beam.hpp
 * @author Alex Mueller
 *
 *
 */

#ifndef BEAM_HPP
#define BEAM_HPP
#include "LogicItem.hpp"
#include "SpartyBoots.hpp"
#include "OutputPin.h"

/**
*Beam Class
*/
class Beam : public LogicItem {
private:
    /// X coordinate
    int mX;
    /// Y coordinate
    int mY;
    /// Sender value
    int mSender;
    /// Bool if item is touching the beam
    bool mItemTouchingBeam = false;

    /// vector containing output pins
    std::vector<std::shared_ptr<OutputPin>> mOutputPins;

    /// Image for the beam sender and receiver when red
    wxImage mBeamRedImage;

    /// The bitmap beam sender and receiver when red.
    wxBitmap mBeamRedBitmap;

    /// Image for the beam sender and receiver when green
    wxImage mBeamGreenImage;

    /// The bitmap for beam sender and receiver when green.
    wxBitmap mBeamGreenBitmap;

    /// Image for the beam sender and receiver when green
    wxImage mBeamGreenImageMirrored;

    /// The bitmap for beam sender and receiver when green.
    wxBitmap mBeamGreenBitmapMirrored;

    /// Image for the beam sender and receiver when green
    wxImage mBeamRedImageMirrored;

    /// The bitmap for beam sender and receiver when green.
    wxBitmap mBeamRedBitmapMirrored;


public:
    Beam(SpartyBoots *spartyBoots, int x, int y, int sender);
    /**
     * getter for pins in list
     * @return mOutputPins
     */
    std::vector<std::shared_ptr<OutputPin>> getPins(){ return mOutputPins; }
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override
    {
        return false;
    };
    /**
     * Accept a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ItemVisitor &visitor) override
    {
        visitor.VisitBeam(this);
    }
    /**
     * Empty draw pins function
     */
    void DrawPins(std::shared_ptr<wxGraphicsContext>,int,int,int,int){};
    void SetItemTouchingBeam(bool b);;
};

#endif // BEAM_HPP
