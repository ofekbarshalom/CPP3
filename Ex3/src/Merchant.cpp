//ofekbarshalom@gmail.com

#include "Merchant.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

    Merchant::Merchant(Game& game, const string& name) : Player(game, name) {}

    string Merchant::getRole() const {
        return "Merchant";
    }
    
    // Special ability: if starting the turn with 3+ coins, gain 1 extra coin
    void Merchant::startTurnBonus() {
        if (!isAlive()) {
            throw runtime_error("Dead players cannot receive start-of-turn bonuses.");
        }

        if (coins >= 3) {
            coins += 1;  // Merchant bonus
        }
    }

}
