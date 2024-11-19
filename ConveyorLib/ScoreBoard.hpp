/**
 * @file ScoreBoard.hpp
 * @author bdean
 *
 *
 */

#ifndef PROJECT1_CONVEYORLIB_SCOREBOARD_H
#define PROJECT1_CONVEYORLIB_SCOREBOARD_H

#include "Item.hpp"
/**
 * Scoreboard Class
 */
class ScoreBoard : public Item {
private:
    /// x coord
    int mX;
    /// y coord
    int mY;
    /// current level
    wxString mLevel;
    /// instructions
    wxString mInstructions;
    /// good
    int mGood;
    /// bad
    int mBad;
    /// Score
    int mScore = 0;

public:
    ScoreBoard(SpartyBoots *spartyBoots, int x, int y, wxString level, int good, int bad, wxString instructions);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(int x, int y) override;
    /**
     * Accept a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ItemVisitor &visitor) override
    {
        visitor.VisitScoreboard(this);
    }
    /**
     * determines the good(+) scores
     * @return
     */
    int GetGood()
    {
        return mGood;
    };
    /**
     * determines the bad(-) scores
     * @return
     */
    int GetBad()
    {
        return mBad;
    };
    /**
     * Updates the score on the scoreboard
     * @param good
     */
    void ChangeScore(bool good)
    {
        if (good)
        {
            mScore += mGood;
        }
        else
        {
            mScore += mBad;
        }
    }
};

#endif // PROJECT1_CONVEYORLIB_SCOREBOARD_H
