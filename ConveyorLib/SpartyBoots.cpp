/**
 * @file SpartyBoots.cpp
 * @author Alex Mueller
 */
#include "pch.h"
#include "SpartyBoots.hpp"
#include <wx/string.h>
#include <wx/tokenzr.h>
#include "Beam.hpp"
#include "Conveyor.hpp"
#include "Item.hpp"
#include "LastProductVisitor.hpp"
#include "LoadLevel.h"
#include "Product.h"
#include "ProductUpdateVisitor.hpp"
#include "ScoreBoard.hpp"
#include "Sensor.h"
#include "Sparty.hpp"
#include <algorithm>
#include "LogicGate.h"
#include "OutputPin.h"
#include "InputPin.h"

using namespace std;

/// Initialze vector of level files
std::vector<std::string> levelNames = {"level0.xml", "level1.xml", "level2.xml", "level3.xml",
                                       "level4.xml", "level5.xml", "level6.xml", "level7.xml", "level8.xml"};

/// Initial item X location
const int InitialX = 200;

/// Initial item Y location
const int InitialY = 200;

/// Images directory
const std::wstring DirectoryContainingImages = L"images/";

/// Level notices duration in seconds
const double LevelNoticeDuration = 2.0;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(24, 69, 59);

/// Color to draw a rectangle enclosing the level notice text
wxColour LevelNoticeBackground(255, 255, 255, 200);

/// Padding to add to the left and right side of the level
/// notice background rectangle in virtual pixels
const double LevelNoticePadding = 20;


/**
 * SpartyBoots Constructor
 */
SpartyBoots::SpartyBoots(wxWindow *parent)
{
    /*mBackground = make_unique<wxBitmap>(
         L"images/background1.png", wxBITMAP_TYPE_ANY);
         */
    mParent = parent;
    auto mWidth = 1000;
    auto mHeight = 800;
    mCurrentLevel = 1;

    LevelLoad(mCurrentLevel);
}

/**
 * Add an item to the SpartyBoots
 * @param item New item to add
 */
void SpartyBoots::Add(std::shared_ptr<Item> item)
{
    item->SetLocation(InitialX, InitialY);
    mItems.push_back(item);
}

void SpartyBoots::InsertItem(std::shared_ptr<Item> item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
    }
    mItems.push_back(item);
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the SpartyBoots.
 * @param x X location in pixels
 * @param y Y
 *
 * location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<IDraggable> SpartyBoots::HitTest(int x, int y)
{
    double virtualX = (x - mXOffset) / mScale;
    double virtualY = (y - mYOffset) / mScale;

    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        auto draggable = (*i)->HitDraggable(virtualX, virtualY);
        if(draggable != nullptr)
        {
            return draggable;
        }

        if ((*i)->HitTest(virtualX, virtualY))
        {
            return *i;
        }
    }

    return nullptr;
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the
 *
 * window
 */
void SpartyBoots::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(mPixelWidth);
    auto scaleY = double(height) / double(mPixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - mPixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > mPixelHeight * mScale)
    {
        mYOffset = (double)((height - mPixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Draw in virtual pixels on the graphics context
    //
    // INSERT YOUR DRAWING CODE HERE
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    // need this comment to commit for some reason feel free to delete
    // Draw notice if needed
    if (mShowingBegin)
    {
        wxString message = wxString::Format(L"Level %d", mCurrentLevel);
        wxFont font(NoticeSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, LevelNoticeColor);

        double width, height;
        graphics->GetTextExtent(message, &width, &height);

        double x = (mPixelWidth - width) / 2 - LevelNoticePadding;
        double y = (mPixelHeight - height) / 2;
        graphics->SetBrush(wxBrush(LevelNoticeBackground));
        graphics->SetPen(*wxTRANSPARENT_PEN);
        graphics->DrawRectangle(x, y, width + 2 * LevelNoticePadding, height);

        graphics->DrawText(message, (mPixelWidth - width) / 2, (mPixelHeight - height) / 2);
    }

    if (mShowingComplete)
    {
        wxString message = wxString::Format(L"Level Complete!");
        wxFont font(NoticeSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, LevelNoticeColor);

        double width, height;
        graphics->GetTextExtent(message, &width, &height);

        double x = (mPixelWidth - width) / 2 - LevelNoticePadding;
        double y = (mPixelHeight - height) / 2;
        graphics->SetBrush(wxBrush(LevelNoticeBackground));
        graphics->SetPen(*wxTRANSPARENT_PEN);
        graphics->DrawRectangle(x, y, width + 2 * LevelNoticePadding, height);

        graphics->DrawText(message, (mPixelWidth - width) / 2, (mPixelHeight - height) / 2);
    }

    graphics->PopState();
}

/**
 * Handle a mouse click
 * @param x X location clicked on
 * @param y Y location clicked on
 */
void SpartyBoots::OnLeftDown(int x, int y)
{
    /// The code here has been moved to HitTest
}

/**
 * on level select event
 * @param level to switch to
 */
void SpartyBoots::OnLevelSelect(int level)
{
    mShowingBegin = true;
    mShowingComplete = false;
    mNoticeTimer = 0;
    mCurrentLevel = level;
    mItems.clear();
    LevelLoad(mCurrentLevel);
    // mParent->Refresh();
}

/**
 *function to gather level information from file
 *@param level to load
 */
void SpartyBoots::LevelLoad(int level)
{
    wxString levelFileName = wxGetCwd() + L"/Levels/" + levelNames[level];
    LoadLevel levelLoader;
    levelLoader.Load(levelFileName);

    // level size extraction
    auto levelSize = levelLoader.GetLevelSize();
    wxStringTokenizer tokenizer(levelSize[0], ",");
    wxString widthStr = tokenizer.GetNextToken();
    wxString heightStr = tokenizer.GetNextToken();
    long w, h;
    widthStr.ToLong(&w);
    heightStr.ToLong(&h);
    mPixelWidth = static_cast<int>(w);
    mPixelHeight = static_cast<int>(h);

    // level sensor extraction
    auto levelSensor = levelLoader.GetLevelSensor();
    if (!levelSensor.empty())
    {
        wxString sensorX = levelSensor[0];
        wxString sensorY = levelSensor[1];
        long x, y;
        sensorX.ToLong(&x);
        sensorY.ToLong(&y);
        int sensorXInt = static_cast<int>(x);
        int sensorYInt = static_cast<int>(y);
        auto levelSensorChildren = levelLoader.GetLevelSensorChildren();
        auto sensor = std::make_shared<Sensor>(this, sensorXInt, sensorYInt, levelSensorChildren);
        mItems.push_back(sensor);
    }

    // level Conveyer extraction
    int conveyerSpeedInt;
    auto levelConveyer = levelLoader.GetLevelConveyer();
    Conveyor *conveyorPtr = nullptr;
    if (!levelConveyer.empty())
    {
        wxString conveyerX = levelConveyer[0];
        wxString conveyerY = levelConveyer[1];
        wxString conveyerSpeed = levelConveyer[2];
        wxString conveyerHeight = levelConveyer[3];
        wxString conveyerPanel = levelConveyer[4];
        long cx, cy, speed, height, panelX, panelY;
        conveyerX.ToLong(&cx);
        conveyerY.ToLong(&cy);
        conveyerSpeed.ToLong(&speed);
        conveyerHeight.ToLong(&height);
        wxStringTokenizer tokenizer2(conveyerPanel, ",");
        wxString conveyerPanelX = tokenizer2.GetNextToken();
        wxString conveyerPanelY = tokenizer2.GetNextToken();
        conveyerPanelX.ToLong(&panelX);
        conveyerPanelY.ToLong(&panelY);
        int conveyerXInt = static_cast<int>(cx);
        int conveyerYInt = static_cast<int>(cy);
        conveyerSpeedInt = static_cast<int>(speed);
        int conveyerHeightInt = static_cast<int>(height);
        int conveyerPanelXInt = static_cast<int>(panelX);
        int conveyerPanelYInt = static_cast<int>(panelY);

        auto conveyor = std::make_shared<Conveyor>(this, conveyerXInt, conveyerYInt, conveyerHeightInt, conveyerSpeedInt, conveyerPanelXInt,
                                                   conveyerPanelYInt);
        conveyorPtr = conveyor.get();
        mItems.push_back(conveyor);
    }
    // level extraction for beam
    auto levelBeam = levelLoader.GetLevelBeam();
    wxString beamX = levelBeam[0];
    wxString beamY = levelBeam[1];
    wxString beamSender = levelBeam[2];
    long bx, by, sender;
    beamX.ToLong(&bx);
    beamY.ToLong(&by);
    beamSender.ToLong(&sender);
    int beamXInt = static_cast<int>(bx);
    int beamYInt = static_cast<int>(by);
    int beamSenderInt = static_cast<int>(sender);

    auto beam = std::make_shared<Beam>(this, beamXInt, beamYInt, beamSenderInt);
    mItems.push_back(beam);


    // level extration sparty
    auto levelSparty = levelLoader.GetLevelSparty();
    wxString spartyX = levelSparty[0];
    wxString spartyY = levelSparty[1];
    wxString spartyHeight = levelSparty[2];
    wxString spartyPin = levelSparty[3];
    wxString spartyKickDuration = levelSparty[4];
    wxString spartyKickSpeed = levelSparty[5];
    long sx, sy, height, speed;
    double duration;
    spartyX.ToLong(&sx);
    spartyY.ToLong(&sy);
    spartyHeight.ToLong(&height);
    spartyKickDuration.ToDouble(&duration);
    spartyKickSpeed.ToLong(&speed);
    int spartyXInt = static_cast<int>(sx);
    int spartyYInt = static_cast<int>(sy);
    int spartyHeightInt = static_cast<int>(height);
    double spartyKickDurationDouble = static_cast<double>(duration);
    int spartyKickSpeedInt = static_cast<int>(speed);

    wxStringTokenizer tokenizer3(spartyPin, ",");
    wxString spartyPinX = tokenizer3.GetNextToken();
    wxString spartyPinY = tokenizer3.GetNextToken();
    long pinx, piny;
    spartyPinX.ToLong(&pinx);
    spartyPinY.ToLong(&piny);
    int spartyPinXInt = static_cast<int>(pinx);
    int spartyPinYInt = static_cast<int>(piny);

    auto sparty = std::make_shared<Sparty>(this, spartyXInt, spartyYInt, spartyHeightInt, spartyPinXInt, spartyPinYInt,
                                           spartyKickDurationDouble, spartyKickSpeedInt);
    mItems.push_back(sparty);

    // extract scoreboard setup
    auto levelScoreboard = levelLoader.GetLevelScoreboard();
    wxString levelScoreboardX = levelScoreboard[0];
    wxString levelScoreboardY = levelScoreboard[1];
    wxString levelScoreboardGood = levelScoreboard[2];
    wxString levelScoreboardBad = levelScoreboard[3];
    wxString levelScoreboardInstructions = levelScoreboard[4];
    long scoreboardX, scoreboardY, scoreboardGood, scoreboardBad;
    levelScoreboardX.ToLong(&scoreboardX);
    levelScoreboardY.ToLong(&scoreboardY);
    levelScoreboardGood.ToLong(&scoreboardGood);
    levelScoreboardBad.ToLong(&scoreboardBad);
    int levelScoreboardXInt = static_cast<int>(scoreboardX);
    int levelScoreboardYInt = static_cast<int>(scoreboardY);
    int levelScoreboardGoodInt = static_cast<int>(scoreboardGood);
    int levelScoreboardBadInt = static_cast<int>(scoreboardBad);

    auto scoreboard = std::make_shared<ScoreBoard>(this, levelScoreboardXInt, levelScoreboardYInt, wxString::Format("%d", level),
                                                   levelScoreboardGoodInt, levelScoreboardBadInt, levelScoreboardInstructions);
    mItems.insert(mItems.begin(), scoreboard);

    // level products extraction
    auto levelProducts = levelLoader.GetLevelProducts();
    double heightDisplacement = 0;
    int widthDisplacement = 25;
    int lastProductIndex = (levelProducts.size() - 1);
    for (int i = 0; i < (int)levelProducts.size(); i++)
    {
        auto product = levelProducts[i];
        wxString placement = product[0];
        wxString shape = product[1];
        wxString color = product[2];
        wxString content = product[3];
        wxString kick = product[4];

        auto productAdd = std::make_shared<Product>(this, placement, shape, color, content, kick);
        conveyorPtr->SetProductClip(productAdd);
        auto productPlacement = productAdd->GetPlacement();
        if (productPlacement.StartsWith("+"))
        {
            double offset;
            productPlacement.Mid(1).ToDouble(&offset);
            heightDisplacement += offset;
            productAdd->SetLocation((conveyorPtr->GetX() - (widthDisplacement)), conveyorPtr->GetY() - heightDisplacement);
        }
        else
        {
            double position;
            productPlacement.ToDouble(&position);
            heightDisplacement = position;
            // productAdd->SetLocation(mConveyor->GetX(), mConveyor->GetY() - position);
            productAdd->SetLocation((conveyorPtr->GetX() - widthDisplacement), conveyorPtr->GetY() - position);
            // heightDisplacement = (mConveyor->GetY() - position);
        }
        if (i == lastProductIndex)
        {
            productAdd->SetLast();
        }
        productAdd->SetSpeed(conveyerSpeedInt);
        mItems.push_back(productAdd);
    }
}

void SpartyBoots::Update(double elapsed)
{
    if (mShowingBegin)
    {
        mNoticeTimer += elapsed;
        if (mNoticeTimer >= LevelNoticeDuration)
        {
            mShowingBegin = false;
        }
    }
    /// updates product location and kicked products
    ProductUpdateVisitor visitor(elapsed);

    // Visit all items
    for (auto &item : mItems)
    {
        item->Accept(visitor);
    }

    /// checks if last product passed beam
    LastProductVisitor lastProductVisitor(elapsed);
    for (auto &item : mItems)
    {
        item->Accept(lastProductVisitor);

    }
    ///If there's a sensor, draw the input pin at different location
    if (lastProductVisitor.GetSensor() != nullptr)
    {
        lastProductVisitor.GetSparty()->SetSensor(true);
    }
    else
    {
        lastProductVisitor.GetSparty()->SetSensor(false);
    }

    //This checks if there's an item in the beam. Don't change states with visitors as the visitor
    //doesn't know about the rest of the items it will be visiting while its visiting. Check at the end.
    if (lastProductVisitor.IsProductInBeam())
    {
        //Get the beam and set it to activated
        lastProductVisitor.GetBeam()->SetItemTouchingBeam(true);
        //Get the sensor, activate the pins with the content being whatever the product thats in the beam's content is
        if (lastProductVisitor.GetSensor() != nullptr)
        {
            lastProductVisitor.GetSensor()->ActivatePins(lastProductVisitor.GetProductInBeam()->GetContent());
        }
        TopologicalComputing(lastProductVisitor.GetSensor(), lastProductVisitor.GetBeam(), lastProductVisitor.GetSparty(), lastProductVisitor.GetGates());


        if (lastProductVisitor.GetSparty()->getPin()[0]->getValue())
        {
            lastProductVisitor.GetSparty()->SetKicking(true);
            lastProductVisitor.GetProductInBeam()->SetKick();
        }
    }
    else
    {
        lastProductVisitor.GetBeam()->SetItemTouchingBeam(false);
        //1st level doesn't have a sensor
        if (lastProductVisitor.GetSensor() != nullptr)
        {
            lastProductVisitor.GetSensor()->ResetPins();
        }
        TopologicalComputing(lastProductVisitor.GetSensor(), lastProductVisitor.GetBeam(), lastProductVisitor.GetSparty(), lastProductVisitor.GetGates());

    }

    if (lastProductVisitor.HasLastProductPassed())
    {
        mLevelEndTimer += elapsed;
        if (mLevelEndTimer >= 3.0)
        {
            mShowingComplete = true;
            mCompleteTimer += elapsed;
            if (mCompleteTimer >= LevelNoticeDuration)
            {
                mCompleteTimer = 0;
                mShowingComplete = false;
                if (mCurrentLevel == (levelNames.size() - 1))
                {
                    mCurrentLevel = 1;
                }
                else
                {
                    mCurrentLevel++;
                }
                mItems.clear();
                LevelLoad(mCurrentLevel);
                mLevelEndTimer = 0;
            }
        }

    }

    for (const auto &item : mItems)
    {
        item->Update(elapsed);
    }

}


void SpartyBoots::TryToCatch(PinConnector* pinConnector, wxPoint lineEnd)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if((*i)->Catch(pinConnector, lineEnd))
        {
            return;
        }
    }
}

void SpartyBoots::MoveToFront(Item* item)
{
    // Find the shared_ptr corresponding to rawPtr
    auto loc = std::find_if(mItems.begin(), mItems.end(),
                           [item](std::shared_ptr<Item> ptr) {
                               return ptr.get() == item;
                           });
    auto itemPtr = *loc;
    if (loc != end(mItems))
    {
        mItems.erase(loc);
    }

    mItems.push_back(itemPtr);
}

void SpartyBoots::TopologicalComputing(Sensor* sensor, Beam* beam, Sparty* sparty, std::vector<LogicGate*> gates)
{
    std::vector<std::shared_ptr<OutputPin>> outPins;        // Get the sensor and beam pins into a vector we can manipulate
    std::vector<InputPin*> inPins;  // Changed to InputPin* type
    //Get beam output pin in
    outPins.push_back(beam->getPins()[0]);

    if (sensor != nullptr)
    {
        // Populate outPins with sensor pins
        for (auto sensorPins : sensor->getPins())
        {
            outPins.push_back(sensorPins);
        }
    }
    while (!outPins.empty())   // Do this until there's no more output pins to consider
    {
        // Iterate over the output pins, update the values, delete the output pins that were updated and put in inPins new inputPins
        for (auto outputPin : outPins)
        {
            if (!(outputPin->getConnector()).empty())
            {
                // Call UpdateValues on the output pin
                outputPin->UpdateValues();

                // Add connected input pins to inPins
                for (auto pinConnection : outputPin->getConnector()) {
                    inPins.push_back(pinConnection->getCaught()); // Ensure getCaught() returns InputPin*
                }
            }
        }

        outPins.clear();   // Remove the outPins anyways, since if outPin doesn't result in change of input, it's cut off

        // Iterate over the gates, and see if any of them are activated completely, then compute their output, and adding it to outputPins
        if (!gates.empty())
        {
            auto it = gates.begin();
            while (it != gates.end()) {
                // Get the input pins for the current gate
                auto gateInputPins = (*it)->GetInputPins();

                // Check if all input pins of the gate are in the inPins vector
                bool allInPins = std::all_of(gateInputPins.begin(), gateInputPins.end(), [&inPins](const std::shared_ptr<InputPin>& pin) {
                    return std::find(inPins.begin(), inPins.end(), pin.get()) != inPins.end(); // Use pin.get() to compare raw pointer
                });

                if (allInPins) {
                    // Compute the gate results
                    (*it)->GateCompute();
                    for (auto outputPins : (*it)->GetOutputPins())
                    {
                        outPins.push_back(outputPins);
                    }
                    // Remove the gate from the list
                    it = gates.erase(it); // erase() returns the next iterator
                } else {
                    ++it; // Move to the next gate
                }
            }
        }
    }


}