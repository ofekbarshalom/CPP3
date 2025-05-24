//ofekbarshalom@gmail.com

#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

#include "Player.hpp"

namespace coup {

class Governor : public Player {
    public:
        Governor(Game& game, const string& name);

        string getRole() const override;
        void tax() override;                  // Override tax to collect 3 coins
        void undo(Player& target) override;   // Governor can undo tax
};

}

#endif // GOVERNOR_HPP
