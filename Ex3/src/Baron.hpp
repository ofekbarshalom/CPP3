//ofekbarshalom@gmail.com

#ifndef BARON_HPP
#define BARON_HPP

#include "Player.hpp"

namespace coup {

class Baron : public Player {
    public:
        Baron(Game& game, const string& name);

        string getRole() const override;
        void invest();  // Pay 3 coins, receive 6 coins
};

}

#endif // BARON_HPP
