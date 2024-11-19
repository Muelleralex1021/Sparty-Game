/**
 * @file LoadLevel.cpp
 * @author Alex Mueller
 */

#include "pch.h"
#include "LoadLevel.h"
#include "Item.hpp"

using namespace std;

/**
 * Load the level from a XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename
 *
 * The filename of the file to load the level from.
 */
void LoadLevel::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    auto size = root->GetAttribute(L"size");
    this->mLevelList.push_back(vector<wxString> {L"level", size});
    this->mLevelSize.push_back(size);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //

    auto child = root->GetChildren();
    for (; child != nullptr; child = child->GetNext())
    {
        auto gameItem = child->GetChildren();
        for (; gameItem != nullptr; gameItem = gameItem->GetNext())
        {
            auto name = gameItem->GetName();
            if (name == L"sensor")
            {
                auto x = gameItem->GetAttribute(L"x");
                auto y = gameItem->GetAttribute(L"y");
                this->mLevelList.push_back(vector<wxString> {L"sensor", x, y});
                this->mLevelSensor.push_back(x);
                this->mLevelSensor.push_back(y);
                // Get child elements of sensor
                auto sensorChild = gameItem->GetChildren();
                for (; sensorChild != nullptr; sensorChild = sensorChild->GetNext())
                {
                    auto childName = sensorChild->GetName();
                    this->mLevelSensorChildren.push_back(childName);
                }
                // XmlSensor(child);
            }
            else if (name == L"conveyor")
            {
                auto x = gameItem->GetAttribute(L"x");
                auto y = gameItem->GetAttribute(L"y");
                auto speed = gameItem->GetAttribute(L"speed");
                auto height = gameItem->GetAttribute(L"height");
                auto panel = gameItem->GetAttribute(L"panel");
                this->mLevelList.push_back(vector<wxString> {L"conveyor", x, y, speed, height, panel});
                this->mLevelConveyer.push_back(x);
                this->mLevelConveyer.push_back(y);
                this->mLevelConveyer.push_back(speed);
                this->mLevelConveyer.push_back(height);
                this->mLevelConveyer.push_back(panel);

                auto conveyorChild = gameItem->GetChildren();
                for (; conveyorChild != nullptr; conveyorChild = conveyorChild->GetNext())
                {
                    auto name = conveyorChild->GetName();
                    if (name == L"product")
                    {
                        auto placement = conveyorChild->GetAttribute(L"placement");
                        auto shape = conveyorChild->GetAttribute(L"shape");
                        auto color = conveyorChild->GetAttribute(L"color");
                        auto content = conveyorChild->GetAttribute(L"content");
                        auto kick = conveyorChild->GetAttribute(L"kick");
                        this->mLevelList.push_back(vector<wxString> {L"product", placement, shape, color, content, kick});
                        this->mLevelProducts.push_back(vector<wxString> {placement, shape, color, content, kick});
                        // XmlProduct(child);
                    }
                }
                // XmlConveyor(child);
            }
            else if (name == L"beam")
            {
                auto x = gameItem->GetAttribute(L"x");
                auto y = gameItem->GetAttribute(L"y");
                auto sender = gameItem->GetAttribute(L"sender");
                this->mLevelList.push_back(vector<wxString> {L"beam", x, y, sender});
                this->mLevelBeam.push_back(x);
                this->mLevelBeam.push_back(y);
                this->mLevelBeam.push_back(sender);
                // XmlBeam(child);
            }
            else if (name == L"sparty")
            {
                auto x = gameItem->GetAttribute(L"x");
                auto y = gameItem->GetAttribute(L"y");
                auto height = gameItem->GetAttribute(L"height");
                auto pin = gameItem->GetAttribute(L"pin");
                auto kickduration = gameItem->GetAttribute(L"kick-duration");
                auto kickspeed = gameItem->GetAttribute(L"kick-speed");
                this->mLevelList.push_back(vector<wxString> {L"sparty", x, y, height, pin, kickduration, kickspeed});
                this->mLevelSparty.push_back(x);
                this->mLevelSparty.push_back(y);
                this->mLevelSparty.push_back(height);
                this->mLevelSparty.push_back(pin);
                this->mLevelSparty.push_back(kickduration);
                this->mLevelSparty.push_back(kickspeed);
                // XmlSparty(child);
            }
            else if (name == L"scoreboard")
            {
                auto x = gameItem->GetAttribute(L"x");
                auto y = gameItem->GetAttribute(L"y");
                auto good = gameItem->GetAttribute(L"good", L"10");
                auto bad = gameItem->GetAttribute(L"bad", L"0");
                this->mLevelList.push_back(vector<wxString> {L"scoreboard", x, y, good, bad});
                this->mLevelScoreboard.push_back(x);
                this->mLevelScoreboard.push_back(y);
                this->mLevelScoreboard.push_back(good);
                this->mLevelScoreboard.push_back(bad);
                // XmlScoreboard(child);
                //  Get the text content
                wxString instructions;
                auto textNode = gameItem->GetChildren();
                while (textNode != nullptr)
                {
                    if (textNode->GetType() == wxXML_TEXT_NODE)
                    {
                        instructions += textNode->GetContent();
                    }
                    else if (textNode->GetName() == L"br")
                    {
                        instructions += L"\n"; // Add newline for <br/> tags
                    }
                    textNode = textNode->GetNext();
                }
                this->mLevelScoreboard.push_back(instructions);
            }
        }
    }
}
