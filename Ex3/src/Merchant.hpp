#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include "Player.hpp"

namespace coup {

class Merchant : public Player {
    public:
        Merchant(Game& game, const string& name);

        string getRole() const override;
        void startTurnBonus();  // Called at the beginning of their turn
};

}

#endif // MERCHANT_HPP
