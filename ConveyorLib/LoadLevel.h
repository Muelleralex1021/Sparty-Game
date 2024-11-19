/**
 * @file LoadLevel.h
 * @author Alex Mueller
 *
 * Class to load levels from XML data file
 *
 */

#ifndef LOADLEVEL_H
#define LOADLEVEL_H

/**
 * load level class with vectors to store information
 */
class LoadLevel {
private:
    /// vector that stores level size
    std::vector<wxString> mLevelSize;
    /// vector that stores level sensor info
    std::vector<wxString> mLevelSensor;
    /// vector that stores level sensor children
    std::vector<wxString> mLevelSensorChildren;
    /// vector that stores level conveyer info
    std::vector<wxString> mLevelConveyer;
    /// vector that stores level products info
    std::vector<std::vector<wxString>> mLevelProducts;
    /// vector that stores level beam info
    std::vector<wxString> mLevelBeam;
    /// vector that stores level Sparty info
    std::vector<wxString> mLevelSparty;
    /// vector that stores level Scoreboard info
    std::vector<wxString> mLevelScoreboard;
    /// vector that stores level list info
    std::vector<std::vector<wxString>> mLevelList;

public:
    void Load(const wxString &filename);

    /**
     *getter for level size info
     */
    std::vector<wxString> GetLevelSize()
    {
        return mLevelSize;
    }
    /**
     *getter for level sensor info
     */
    std::vector<wxString> GetLevelSensor()
    {
        return mLevelSensor;
    }
    /**
     *getter for level sensor children
     */
    std::vector<wxString> GetLevelSensorChildren()
    {
        return mLevelSensorChildren;
    }
    /**
     *getter for level conveyer info
     */
    std::vector<wxString> GetLevelConveyer()
    {
        return mLevelConveyer;
    }
    /**
     *getter for level products info
     */
    std::vector<std::vector<wxString>> GetLevelProducts()
    {
        return mLevelProducts;
    }
    /**
     *getter for level beam info
     */
    std::vector<wxString> GetLevelBeam()
    {
        return mLevelBeam;
    }
    /**
     *getter for level Sparty info
     */
    std::vector<wxString> GetLevelSparty()
    {
        return mLevelSparty;
    }
    /**
     *getter for level scoreboard info
     */
    std::vector<wxString> GetLevelScoreboard()
    {
        return mLevelScoreboard;
    }
};

#endif // LOADLEVEL_H
