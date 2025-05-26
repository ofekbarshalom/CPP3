//ofekbarshalom@gmail.com

#ifndef SPY_HPP
#define SPY_HPP

#include "Player.hpp"

using namespace std;

namespace coup {

    // Spy role: Can peek at another player's coin count.
    // Can block a player's next arrest action.
    class Spy : public Player {
        public:
            Spy(Game& game, const string& name);
            
            string getRole() const override;

            // View how many coins another player has
            void peek(Player& target);

            // Prevent the target from performing arrest next turn
            void blockArrest(Player& target);
    };

}

#endif // SPY_HPP
