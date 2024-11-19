/**
 * @file Product.h
 * @author Alex Mueller
 *
 *
 */

#ifndef PRODUCT_H
#define PRODUCT_H
#include <map>
#include "Item.hpp"
/**
 * Products class
 */
class Product : public Item {
public:
    /// The possible product properties.
    /// The None properties allows us to indicate that
    /// the product has no content.
    enum class Properties
    {
        None,
        Red,
        Green,
        Blue,
        White,
        Square,
        Circle,
        Diamond,
        Izzo,
        Smith,
        Football,
        Basketball,
        Wolverine
    };

    /// The property types
    enum class Types
    {
        Color,
        Shape,
        Content
    };

    /// Mapping from the XML strings for properties to
    /// the Properties enum and the type of the property.
    static const std::map<std::wstring, Properties> NamesToProperties;

    /// Mapping from a property to it's type
    static const std::map<Properties, Types> PropertiesToTypes;

    /// Mapping from content properties to their associated image
    static const std::map<Properties, std::wstring> PropertiesToContentImages;
    Product(SpartyBoots *spartyBoots, wxString placement, wxString shape, wxString color, wxString content, wxString kick);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override;
    void UpdateClipRegion(const wxRect &rect);
    /**
     * Getter for placement
     * @return mPlacement
     */
    wxString GetPlacement()
    {
        return mPlacement;
    }
    /**
     * set as last product
     */
    void SetLast()
    {
        mLastProduct = true;
    };

    /**
     * check if last product
     * @return if product last
     */
    bool IsLast()
    {
        return mLastProduct;
    };

    void LoadContentImage();
    /**
     * sets product speed
     * @param speed
     */
    void SetSpeed(int speed)
    {
        mSpeed = speed;
    };

    /**
     * get product speed
     * @return speed of product
     */
    int GetSpeed()
    {
        return mSpeed;
    };

    /**
     * accept visitor
     * @param visitor item visitor
     */
    void Accept(ItemVisitor &visitor) override
    {
        visitor.VisitProduct(this);
    }

    /**
     * check if object needs to be kicked
     * @return mkick
     */
    bool ToKick()
    {
        return mKick;
    };

    /**
     * checks if object was kicked
     * @return mwaskicked
     */
    bool WasKick()
    {
        return mWasKicked;
    };

    /**
     * returns if score is drawn
     * @return score drawn
     */
    bool GetScoreAccountedFor()
    {
        return mScoreDrawn;
    };

    /**
     * sets mScoreDrawn
     */
    void SetScoreDrawn()
    {
        mScoreDrawn = true;
    };

    /**
     * acheive product content
     * @return vector of product content
     */
    std::vector<wxString> GetContent()
    {
        return {mContent, mShape, mColor};
    }

    /**
     * Sets mWasKicked
     */
    void SetKick() {mWasKicked = true;};

private:
    /// The clip region for drawing on the conveyor belt.
    wxRect mClipRegion;
    /// set as last product
    bool mLastProduct = false;
    /// placement
    wxString mPlacement;
    /// shape
    wxString mShape;
    /// color
    wxString mColor;
    /// content
    wxString mContent;
    /// kick
    bool mKick = false;
    /// was kicked
    bool mWasKicked = false;
    /// product speed
    int mSpeed;
    /// image content
    std::wstring mContentImage;
    /// Members to store properties
    Properties mShapeProperty = Properties::None;
    Properties mColorProperty = Properties::None;
    Properties mContentProperty = Properties::None;
    /// bitmap
    wxBitmap mContentBitmap;
    /// score has been acounted for
    bool mScoreDrawn = false;
};

#endif // PRODUCT_H
