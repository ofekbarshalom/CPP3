//ofekbarshalom@gmail.com

#include "General.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

    General::General(Game& game, const string& name) : Player(game, name) {}


    string General::getRole() const {
        return "General";
    }
    
    void General::undo(Player& target) {
    if (coins < 5) {
        throw runtime_error("Not enough coins to defend against a coup.");
    }

    removeCoins(5);
    setLastAction("defend_coup", &target);
    }

}
