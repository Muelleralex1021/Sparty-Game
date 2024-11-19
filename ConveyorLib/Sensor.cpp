/**
 * @file Sensor.cpp
 * @author trevo
 */

#include "pch.h"
#include "Sensor.h"
#include "SpartyBoots.hpp"

/// The image file for the sensor cable
const std::wstring SensorCableImage = L"sensor-cable.png";

/// The image file for the sensor camera
const std::wstring SensorCameraImage = L"sensor-camera.png";

/// The image file for the sensor cable
const std::wstring BasketballImage = L"basketball.png";

/// The image file for the sensor cable
const std::wstring FootballImage = L"football.png";

/// The image file for the sensor cable
const std::wstring IzzoImage = L"izzo.png";

/// The image file for the sensor cable
const std::wstring SmithImage = L"smith.png";

/// The image file for the sensor cable
const std::wstring WolverineImage = L"wolverine.png";

/// How far below Y location of the sensor system is the panel top?
const int PanelOffsetY = 87;

/// How much space for each property
const wxSize PropertySize(100, 40);

/// Size of a shape as a property in virtual pixels
const double PropertyShapeSize = 32;

/// Range where a Sensor is viewed by the sensor relative
/// to the Y coordinate of the sensor.
const int SensorRange[] = {-40, 15};

/// The background color to draw the sensor panel
const wxColour PanelBackgroundColor(128, 128, 128);

/// Default Camera Width size in pixels
const wxDouble CameraWidth = 225.0;

/// Default Cable Width size in pixels
const wxDouble CableWidth = 350.0;

/// Default Camera Height size in pixels
const wxDouble CameraHeight = 200.0;

/// Default Cable Height size in pixels
const wxDouble CableHeight = 300.0;

/// Default offset for the sensor panel
int PanelRectOffsetY = 30;

/// Color to use for "red"
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for "green"
const wxColour MSUGreen(24, 69, 59);

/// Color to use for "blue"
const wxColor UofMBlue(0, 39, 76);

/// Diameter to draw the pin in pixels
const int PinSize = 10;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown = wxColour(128, 128, 128);

/// Maximum offset of Bezier control points relative to line ends
static constexpr double BezierMaxOffset = 200;

/// Line with for drawing lines between pins
static const int LineWidth = 3;

/// Default length of line from the pin
static const int DefaultLineLength = 20;

/**
 * initialization function for sensor
 * @param spartyBoots
 * @param x
 * @param y
 * @param children
 */
Sensor::Sensor(SpartyBoots *spartyBoots, int x, int y, std::vector<wxString> children): LogicItem(spartyBoots),
    mSensorCableImage(L"images/" + SensorCableImage, wxBITMAP_TYPE_ANY), mSensorCableBitmap(mSensorCableImage),
    mSensorCameraImage(L"images/" + SensorCameraImage, wxBITMAP_TYPE_ANY), mSensorCameraBitmap(mSensorCameraImage),
    mWolverineImage(L"images/" + WolverineImage, wxBITMAP_TYPE_ANY), mWolverineBitmap(mWolverineImage),
    mSmithImage(L"images/" + SmithImage, wxBITMAP_TYPE_ANY), mSmithBitmap(mSmithImage),
    mIzzoImage(L"images/" + IzzoImage, wxBITMAP_TYPE_ANY), mIzzoBitmap(mIzzoImage),
    mFootballImage(L"images/" + FootballImage, wxBITMAP_TYPE_ANY), mFootballBitmap(mFootballImage),
    mBasketballImage(L"images/" + BasketballImage, wxBITMAP_TYPE_ANY), mBasketballBitmap(mBasketballImage)

{
    mX = x;
    mY = y;
    mChildren = children;
    SetLocation(x, y);


    int index = 0;  // for indexing and recognizing each output
    for(auto child : mChildren)
    {
        /// Creating a vector of pins and initializing them at the same time
        mOutputPins.push_back(std::make_shared<OutputPin>(spartyBoots));
        spartyBoots->Add(mOutputPins[index]);
        // Increment index for the next iteration
        ++index;
    }
}

/**
 *
 * Draw Sensor.
 * @param graphics
 */
void Sensor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{


    graphics->DrawBitmap(mSensorCableBitmap, mX - CableWidth/2 - 10, mY - CableHeight/2, CableWidth, CableHeight);
    graphics->DrawBitmap(mSensorCameraBitmap, mX - CableWidth/2 - 10, mY - CameraHeight/2, CableWidth, CameraHeight);

    int offsetY = PanelRectOffsetY;

    int index = 0; //for indexing the output gates
    for(auto child : mChildren)
    {
        wxPen panelPen(*wxBLACK, 2);
        graphics->SetPen(panelPen);
        if (child == L"red"){graphics->SetBrush(OhioStateRed);}
        else if (child == L"green"){graphics->SetBrush(MSUGreen);}
        else if (child == L"blue"){graphics->SetBrush(UofMBlue);}
        else if (child == L"white"){graphics->SetBrush(*wxWHITE);}
        else
        {
            graphics->SetBrush(PanelBackgroundColor);
        }
        graphics->DrawRectangle(mX - CableWidth/2 - 10 + CableWidth, mY + PanelOffsetY + offsetY, PropertySize.x, PropertySize.y);
        ///This little part is for setting location and drawing output pins
        mOutputPins[index]->SetLocation(mX - CableWidth/2 - 10 + CableWidth + PropertySize.x + DefaultLineLength, mY + PanelOffsetY + offsetY + PropertySize.y/2);
        mOutputPins[index]->DrawPins(graphics, mX - CableWidth/2 - 10 + CableWidth + PropertySize.x, mY + PanelOffsetY + offsetY + PropertySize.y/2, mX - CableWidth/2 - 10 + CableWidth + PropertySize.x + DefaultLineLength, mY + PanelOffsetY + offsetY + PropertySize.y/2);
        mOutputPins[index]->setConnect(true);
        if (child == L"basketball")
        {
            graphics->DrawBitmap(mBasketballBitmap, mX + CableWidth/2 + (PropertySize.x/4) - 10, mY + PanelOffsetY + offsetY, PropertySize.x/2, PropertySize.y);
        }
        if (child == L"football")
        {
            graphics->DrawBitmap(mFootballBitmap,mX + CableWidth/2 + (PropertySize.x/4) - 10, mY + PanelOffsetY + offsetY, PropertySize.x/2, PropertySize.y);
        }
        if (child == L"izzo")
        {
            graphics->DrawBitmap(mIzzoBitmap, mX + CableWidth/2 + (PropertySize.x/4) - 10, mY + PanelOffsetY + offsetY, PropertySize.x/2, PropertySize.y);
        }
        if (child == L"smith")
        {
            graphics->DrawBitmap(mSmithBitmap, mX + CableWidth/2 + (PropertySize.x/4) - 10, mY + PanelOffsetY + offsetY, PropertySize.x/2, PropertySize.y);
        }
        if (child == L"wolverine")
        {
            graphics->DrawBitmap(mWolverineBitmap, mX + CableWidth/2 + (PropertySize.x/4) - 10, mY + PanelOffsetY + offsetY, PropertySize.x/2, PropertySize.y);
        }
        if (child == L"square")
        {
            graphics->SetBrush(*wxWHITE);
            graphics->DrawRectangle( mX + CableWidth/2 + (PropertySize.x/4) - 10 + (PropertySize.x/8), mY + PanelOffsetY + offsetY + (PropertySize.x/16), PropertySize.x/4,PropertySize.x/4);
        }
        if (child == L"circle")
        {
            graphics->SetBrush(*wxWHITE);
            graphics->DrawEllipse(mX + CableWidth/2 + (PropertySize.x/4) - 10 + (PropertySize.x/8), mY + PanelOffsetY + offsetY + (PropertySize.x/16),  PropertySize.x/4,PropertySize.x/4);
        }
        if (child == L"diamond")
        {
            graphics->SetBrush(*wxWHITE);
            graphics->Translate(GetX() + 25, GetY() + 25);  // Move to the center of the rectangle
            graphics->Rotate(wxDegToRad(45));  // Rotate 45 degrees
            graphics->DrawRectangle(mX + CableWidth/2 + (PropertySize.x/4) - 10 + (PropertySize.x/8), mY + PanelOffsetY + offsetY + (PropertySize.x/16), PropertySize.x/4,PropertySize.x/4);
        }
        index++;
        offsetY += PropertySize.y;
    }
}

/**
 * activate pins based on product info
 * @param productContent product info
 */
void Sensor::ActivatePins(std::vector<wxString> productContent)
{
    for (auto& property : productContent)
    {
        auto it = std::find(mChildren.begin(), mChildren.end(), property);
        if (it != mChildren.end())
        {
            size_t index = std::distance(mChildren.begin(), it);
            // Do something with the index, such as activating the pin
            mOutputPins[index]->setValue(true);
        }
    }
}

/**
 * reset sensor pins
 */
void Sensor::ResetPins()
{
    for (auto pins : mOutputPins)
    {
        pins->setValue(false);
    }
}

