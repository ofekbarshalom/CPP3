//ofekbarshalom@gmail.com

#include "Spy.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

namespace coup {

    Spy::Spy(Game& game, const string& name) : Player(game, name) {}

    string Spy::getRole() const {
        return "Spy";
    }

    // Spy ability: print how many coins the target has
    void Spy::peek(Player& target) {
        if (!target.isAlive()) {
            throw runtime_error("Target is dead.");
        }
        
        setLastAction("peek", &target);
        cout << target.getName() << " has " << target.getCoins() << " coins." << endl;
    }

    // Spy ability: prevent the target from using 'arrest' in their next turn
    void Spy::blockArrest(Player& target) {
        if (!target.isAlive()) {
            throw runtime_error("Target is dead.");
        }
        
        target.setArrestBlocked(true);
        setLastAction("block_arrest", &target);
    }
}
