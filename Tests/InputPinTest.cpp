/**
 * @file InputPinTest.cpp
 * @author tiend
 */


#include <pch.h>
#include <SpartyBoots.hpp>
#include "gtest/gtest.h"
#include <wx/filename.h>
#include <LoadLevel.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <InputPin.h>


using namespace std;

class InputPinTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/SpartyBoots";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }
};

/** Mock class for testing the class Item */
class LogicMock : public InputPin {
public:
    LogicMock(SpartyBoots *spartyBoots) : InputPin(spartyBoots) {}
    bool HitTest(int x, int y) {
        double radius = 10 / 2.0; // Radius of the circular pin


        // Calculate the distance from the center of the pin to the point (x, y)
        double testX = x - GetX();
        double testY = y - GetY();

        // Calculate the squared distance to avoid using sqrt for performance
        double distanceSquared = testX * testX + testY * testY;

        // Check if the point is within the radius of the pin
        if (distanceSquared <= radius * radius)
        {
            // We are inside the circular pin
            return true;
        }

        return false;
    }

    void Draw(std::shared_ptr<wxGraphicsContext> context) {
        // Provide a mock implementation
    }

    void Accept(ItemVisitor &visitor) {
        // Provide a mock implementation
    }

    void DrawPins(std::shared_ptr<wxGraphicsContext> context, int x, int y, int width, int height, bool state) {
        // Provide a mock implementation
    }

};

TEST_F(InputPinTest, Construct)
{
    auto spartyBoots = std::make_shared<SpartyBoots>(nullptr);
    LogicMock inputPin(spartyBoots.get());
}

TEST_F(InputPinTest, HitTest)
{
    auto spartyBoots = std::make_shared<SpartyBoots>(nullptr);
    LogicMock inputPin(spartyBoots.get());

    inputPin.SetLocation(100, 150);
    ASSERT_EQ(100, inputPin.GetX());
    ASSERT_EQ(150, inputPin.GetY());

    ASSERT_EQ(true, inputPin.HitTest(95,150));
    ASSERT_EQ(false, inputPin.HitTest(94,150));
}

TEST_F(InputPinTest, PartOfItems)
{
    auto spartyBoots = std::make_shared<SpartyBoots>(nullptr);
    LogicMock inputPin(spartyBoots.get());

    inputPin.SetLocation(100, 150);
}
