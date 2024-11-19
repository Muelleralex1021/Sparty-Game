/**
 * @file ScoreBoard.cpp
 * @author bdean
 */
#include "pch.h"
#include "ScoreBoard.hpp"

/// Size of the scoreboard in virtual pixels
const wxSize ScoreboardSize(380, 100);

/// The spacing from the scores to the instructions presentation
/// in virtual pixels
const int SpacingScoresToInstructions = 40;

/// The spacing between the instruction lines in virtual pixels.
const int SpacingInstructionLines = 17;

/**
 * initialization of scoreboard
 * @param spartyBoots
 * @param x
 * @param y
 * @param level
 * @param good
 * @param bad
 * @param
 *
 * instructions
 */
ScoreBoard::ScoreBoard(SpartyBoots *spartyBoots, int x, int y, wxString level, int good, int bad, wxString instructions): Item(spartyBoots)
{
    mX = x;
    mY = y;
    mLevel = level;
    mGood = good;
    mBad = bad;
    mInstructions = instructions;
    if (abs(mGood) > 1000)
    {
        mGood = 10;
        mBad = -5;
    }
}
/**
 * drawing of scoreboard
 * @param graphics
 */
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Use the initialized location from the constructor (scoreboardX and scoreboardY)
    // auto x = 700;  // Get X coordinate
    // auto y = 40;  // Get Y coordinate

    // Width and height of the scoreboard
    auto w = ScoreboardSize.GetWidth();  // Adjusted width to ensure text fits
    auto h = ScoreboardSize.GetHeight(); // Adjusted height for all text to fit comfortably

    // Set up the pen and brush for the scoreboard (customize as needed)
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);

    // Draw the rectangle for the scoreboard
    graphics->DrawRectangle(mX - w / 2, mY - h / 2, w, h);

    // Set up the font for "Level" and "Game" (size 25)
    auto font = graphics->CreateFont(25, L"Arial", wxFONTFLAG_BOLD, wxColour(24, 69, 59));
    graphics->SetFont(font);

    // Draw the "Level" and "Game" information on separate lines
    wxString score = wxString::Format("%d", mScore);
    wxString levelText = L"Level: " + mLevel; // Default level text
    wxString gameText = L"Game: " + score;    // Default game text

    // Position the larger text for "Level" and "Game"
    graphics->DrawText(levelText, mX - w / 2 + 10, mY - h / 2 + 10);                        // Top-left, for "Level"
    graphics->DrawText(gameText, mX + w / 2 - gameText.length() * 15 - 5, mY - h / 2 + 10); // Top-right, for "Game"

    // Set up a smaller font for the instructions (size 15)
    font = graphics->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
    graphics->SetFont(font);

    // Instruction text below "Level" and "Game"
    wxString instructions = mInstructions; // Instruction text

    // Position the instructions text
    graphics->DrawText(instructions, mX - w / 2 + 10, mY - h / 2 + SpacingScoresToInstructions); // Centered, multi-line instructions
}

/**
 * determines if scoreboard has been hit
 * @param x
 * @param y
 * @return bool of if scoreboard hit
 */
bool ScoreBoard::HitTest(int x, int y)
{
    // do we even need a hit test on this class since it needs no click interaction?
    return false;
}
