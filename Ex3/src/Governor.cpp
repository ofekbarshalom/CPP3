//ofekbarshalom@gmail.com

#include "Governor.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

    Governor::Governor(Game& game, const string& name): Player(game, name) {}

    string Governor::getRole() const {
        return "Governor";
    }

    void Governor::tax() {
        requireMyTurnAndAlive();
        
        if (sanctioned) {
            throw runtime_error("You are sanctioned and cannot tax.");
        }

        if (coins >= 10) {
            throw runtime_error("You must coup when holding 10 or more coins.");
        }

        addCoins(3); // Special tax bonus
        string previousAction = last_action;
        setLastAction("tax");
        sanctioned = false;

        if(previousAction != "bribe") {
            game->advanceTurn();
        }
    }

    void Governor::undo(Player& target) {
        if (!target.isAlive()) {
            throw runtime_error("Cannot undo a dead player.");
        }

        if (target.getLastAction() != "tax") {
            throw runtime_error("Governor can only undo a tax action.");
        }

        if (target.getCoins() < 2) {
            throw runtime_error("Target does not have enough coins to undo tax.");
        }

        target.removeCoins(2);
    }

}
