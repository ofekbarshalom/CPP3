//ofekbarshalom@gmail.com

#ifndef SCREENS_HPP
#define SCREENS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Game.hpp"
#include "Player.hpp"

using namespace sf;
using namespace std;

namespace coup {

    bool launchOpeningScreen(); // Start screen; returns true if "Start Game" clicked
    void launchPlayerSetupScreen(Game& game); // Choose player count
    void launchNameEntryScreen(Game& game, int playerCount); // Enter player names
    void launchRevealRolesScreen(Game& game); // Show assigned roles
    void launchMainGameScreen(Game& game); // Main game logic and actions

    Player* chooseTargetPopup(const Font& font, const vector<Player*>& targets); // Choose a target for an action
    bool askGeneralUndoPopup(const Font& font, const string& generalName); // Ask General to block coup
    bool askJudgeUndoPopup(const Font& font, const string& judgeName); // Ask Judge to block bribe

    void showErrorPopup(const Font& font, const string& message); // Display error
    void showSpyPeekPopup(const Font& font, const string& name, int coins); // Show peek result
    void launchWinnerScreen(const string& winnerName); // Show winner
}

#endif // SCREENS_HPP
