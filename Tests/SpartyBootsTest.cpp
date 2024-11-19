/**
 * @file SpartyBootsTest.cpp
 * @author Alex Mueller
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

using namespace std;

class SpartyBootsTest : public ::testing::Test {
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


TEST_F(SpartyBootsTest, Construct)
{
    SpartyBoots spartyBoots(NULL);
}

TEST_F(SpartyBootsTest, Load)
{
    SpartyBoots spartyBoots(NULL);
    LoadLevel level;

    const wxString level0Test = wxGetCwd() + L"/Levels/level0.xml";

    ///Load level0 into LoadLevel object
    level.Load(level0Test);

    ASSERT_EQ(2, level.GetLevelSensor().size());
    ASSERT_EQ(5, level.GetLevelConveyer().size());
    ASSERT_EQ(6, level.GetLevelProducts().size());
    ASSERT_EQ(3, level.GetLevelBeam().size());
    ASSERT_EQ(6, level.GetLevelSparty().size());
    ASSERT_EQ(5, level.GetLevelScoreboard().size());

    SpartyBoots spartyBoots1(NULL);
    LoadLevel level1;

    const wxString level1Test = wxGetCwd() + L"/Levels/level1.xml";

    ///Load level1 into LoadLevel object
    level1.Load(level1Test);

    ASSERT_EQ(2, level.GetLevelSensor().size());
    ASSERT_EQ(5, level.GetLevelConveyer().size());
    ASSERT_EQ(6, level.GetLevelProducts().size());
    ASSERT_EQ(3, level.GetLevelBeam().size());
    ASSERT_EQ(6, level.GetLevelSparty().size());
    ASSERT_EQ(5, level.GetLevelScoreboard().size());

}
