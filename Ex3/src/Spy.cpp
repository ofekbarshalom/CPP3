#include "Spy.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

namespace coup {

    Spy::Spy(Game& game, const string& name) : Player(game, name) {}

    string Spy::getRole() const {
        return "Spy";
    }

    void Spy::peek(Player& target) {
        if (!target.isAlive()) {
            throw runtime_error("Target is dead.");
        }
        
        setLastAction("peek", &target);
        cout << target.getName() << " has " << target.getCoins() << " coins." << endl;
    }

    void Spy::blockArrest(Player& target) {
        if (!target.isAlive()) {
            throw runtime_error("Target is dead.");
        }
        
        target.setArrestBlocked(true);
        setLastAction("block_arrest", &target);
    }
}
