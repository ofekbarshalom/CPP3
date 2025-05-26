//ofekbarshalom@gmail.com

#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include "Player.hpp"

namespace coup {

// Merchant role: Gains bonus coins if starting the turn with 3 or more
// When arrested, they pay 2 coins to the bank instead of giving 1 coin to the attacker.
class Merchant : public Player {
    public:
        Merchant(Game& game, const string& name);

        string getRole() const override;
        void startTurnBonus();  // Called at the beginning of their turn
};

}

#endif // MERCHANT_HPP
