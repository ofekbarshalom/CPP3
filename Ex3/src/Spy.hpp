//ofekbarshalom@gmail.com

#ifndef SPY_HPP
#define SPY_HPP

#include "Player.hpp"

using namespace std;

namespace coup {

    class Spy : public Player {
        public:
            Spy(Game& game, const string& name);
            
            string getRole() const override;
            void peek(Player& target);
            void blockArrest(Player& target);
    };

}

#endif // SPY_HPP
