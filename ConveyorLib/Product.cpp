/**
 * @file Product.cpp
 * @author trevo
 */

#include "pch.h"
#include "Product.h"
#include <wx/graphics.h>

/// Default product size in pixels
std::wstring ProductDefaultSize = L"80";

/// Size to draw content relative to the product size
double ContentScale = 0.8;

/// Color to use for "red"
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for "green"
const wxColour MSUGreen(24, 69, 59);

/// Color to use for "blue"
const wxColor UofMBlue(0, 39, 76);

/// Delay after last product has left beam or
/// been kicked before we end the level.
const double LastProductDelay = 3;

const std::map<std::wstring, Product::Properties> Product::NamesToProperties = {
    {L"red",        Product::Properties::Red       },
    {L"green",      Product::Properties::Green     },
    {L"blue",       Product::Properties::Blue      },
    {L"white",      Product::Properties::White     },
    {L"square",     Product::Properties::Square    },
    {L"circle",     Product::Properties::Circle    },
    {L"diamond",    Product::Properties::Diamond   },
    {L"izzo",       Product::Properties::Izzo      },
    {L"smith",      Product::Properties::Smith     },
    {L"basketball", Product::Properties::Basketball},
    {L"football",   Product::Properties::Football  },
    {L"umich",      Product::Properties::Wolverine },
    {L"none",       Product::Properties::None      },
};

const std::map<Product::Properties, Product::Types> Product::PropertiesToTypes = {
    {Product::Properties::Red,        Product::Types::Color  },
    {Product::Properties::Green,      Product::Types::Color  },
    {Product::Properties::Blue,       Product::Types::Color  },
    {Product::Properties::White,      Product::Types::Color  },
    {Product::Properties::Square,     Product::Types::Shape  },
    {Product::Properties::Circle,     Product::Types::Shape  },
    {Product::Properties::Diamond,    Product::Types::Shape  },
    {Product::Properties::Izzo,       Product::Types::Content},
    {Product::Properties::Smith,      Product::Types::Content},
    {Product::Properties::Football,   Product::Types::Content},
    {Product::Properties::Basketball, Product::Types::Content},
    {Product::Properties::Wolverine,  Product::Types::Content},
    {Product::Properties::None,       Product::Types::Content}
};

const std::map<Product::Properties, std::wstring> Product::PropertiesToContentImages = {
    {Product::Properties::Izzo,       L"images/izzo.png"      },
    {Product::Properties::Smith,      L"images/smith.png"     },
    {Product::Properties::Football,   L"images/football.png"  },
    {Product::Properties::Basketball, L"images/basketball.png"},
    {Product::Properties::Wolverine,  L"images/wolverine.png" },
};

/**
 * initialization function for product
 * @param spartyBoots SpartyBoots
 * @param placement wxString
 * @param shape wxString
 *
 * @param
 * color wxString
 * @param content wxString
 * @param kick wxString
 */

Product::Product(SpartyBoots *spartyBoots, wxString placement, wxString shape, wxString color, wxString content, wxString kick)
    : Item(spartyBoots), mClipRegion(0, 0, 0, 0)
{
    mPlacement = placement;
    mShape = shape;
    mColor = color;
    mContent = content;
    if (kick == L"yes")
    {
        mKick = true;
    }
    // Handle shape
    if (!shape.IsEmpty())
    {
        auto shapeIt = NamesToProperties.find(shape.ToStdWstring());
        if (shapeIt != NamesToProperties.end())
        {
            mShapeProperty = shapeIt->second;
        }
    }

    // Handle color
    if (!color.IsEmpty())
    {
        auto colorIt = NamesToProperties.find(color.ToStdWstring());
        if (colorIt != NamesToProperties.end())
        {
            mColorProperty = colorIt->second;
        }
    }

    // Handle content
    if (!content.IsEmpty())
    {
        auto contentIt = NamesToProperties.find(content.ToStdWstring());
        if (contentIt != NamesToProperties.end())
        {
            mContentProperty = contentIt->second;

            // Load content image if applicable
            auto imageIt = PropertiesToContentImages.find(mContentProperty);
            if (imageIt != PropertiesToContentImages.end())
            {
                mContentImage = imageIt->second;
            }
            LoadContentImage();
        }
    }
    else
    {
        mContentProperty = Properties::None;
    }

    // Validate property types
    if (mShapeProperty != Properties::None && PropertiesToTypes.at(mShapeProperty) != Types::Shape)
    {
        // Handle error or set default
        mShapeProperty = Properties::None;
    }

    if (mColorProperty != Properties::None && PropertiesToTypes.at(mColorProperty) != Types::Color)
    {
        // Handle error or set default
        mColorProperty = Properties::None;
    }

    if (mContentProperty != Properties::None && PropertiesToTypes.at(mContentProperty) != Types::Content)
    {
        // Handle error or set default
        mContentProperty = Properties::None;
    }
}

/**
 * Draws the product on screen.
 * @param graphics The graphics context
 */
void Product::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    if (mClipRegion.GetWidth() > 0)
        graphics->Clip(wxRegion(mClipRegion));

    // draw product...
    // Set color based on the product's color property
    wxColour color;
    switch (mColorProperty)
    {
    case Properties::Red:
        color = OhioStateRed;
        break;
    case Properties::Green:
        color = MSUGreen;
        break;
    case Properties::Blue:
        color = UofMBlue;
        break;
    case Properties::White:
        color = *wxWHITE;
        break;
    default:
        color = *wxLIGHT_GREY;
        break; // Default color
    }
    graphics->SetBrush(wxBrush(color));
    graphics->SetPen(wxPen(color));

    // Draw shape based on the property
    if (mShapeProperty == Properties::Square)
    {
        graphics->DrawRectangle(GetX(), GetY(), 50, 50);
    }
    else if (mShapeProperty == Properties::Circle)
    {
        graphics->DrawEllipse(GetX(), GetY(), 50, 50);
    }
    else if (mShapeProperty == Properties::Diamond)
    {
        // Translate to the center of the rectangle to rotate
        graphics->PushState();
        graphics->Translate(GetX() + 25, GetY() + 25); // Move to the center of the rectangle
        graphics->Rotate(wxDegToRad(45));              // Rotate 45 degrees
        graphics->DrawRectangle(-25, -25, 50, 50);
        graphics->PopState();
    }

    if (mContentBitmap.IsOk())
    {
        double scale = 0.8;                             // 80% scaling
        int size = 50;                                  // Assume the circle's size is 50x50
        int imageSize = static_cast<int>(size * scale); // Scale image size

        // Center the image inside the shape
        int offsetX = (size - imageSize) / 2;
        int offsetY = (size - imageSize) / 2;

        graphics->DrawBitmap(mContentBitmap, GetX() + offsetX, GetY() + offsetY, imageSize, imageSize);
    }

    graphics->PopState();
}

/**
 * Tests for click.
 * @param x The X of the click
 * @param y The Y of the click
 * @return Whether the product was hit
 */
bool Product::HitTest(int x, int y)
{
    int testX = x - GetX();
    int testY = y - GetY();
    if (((testX < 50 && testX >= 0) && (testY < 50 && testY >= 0)) && (mContentProperty == Properties::Wolverine))
    {
        mWasKicked = true;
        return true;
    }
    return false;
}

/**
 * Sets the clipping region for drawing on screen.
 * @param rect The area where the conveyor is displayed
 */
void Product::UpdateClipRegion(const wxRect &rect)
{
    mClipRegion = rect;
}

/**
 * function for loading bitmap image
 */
void Product::LoadContentImage()
{
    auto imageIt = PropertiesToContentImages.find(mContentProperty);
    if (imageIt != PropertiesToContentImages.end())
    {
        wxImage image(imageIt->second); // Load the image
        if (image.IsOk())
        {
            mContentBitmap = wxBitmap(image); // Convert to bitmap
        }
    }
}


