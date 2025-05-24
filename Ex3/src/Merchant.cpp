//ofekbarshalom@gmail.com

#include "Merchant.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

    Merchant::Merchant(Game& game, const string& name) : Player(game, name) {}

    string Merchant::getRole() const {
        return "Merchant";
    }
    
    void Merchant::startTurnBonus() {
        if (!isAlive()) {
            throw runtime_error("Dead players cannot receive start-of-turn bonuses.");
        }

        if (coins >= 3) {
            coins += 1;  // Merchant bonus: +1 coin at start of turn if holding 3+
        }
    }

}
