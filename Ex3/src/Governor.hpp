//ofekbarshalom@gmail.com

#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

#include "Player.hpp"

namespace coup {

// Governor role: Gains bonus from tax and can undo other players' tax actions
class Governor : public Player {
    public:
        Governor(Game& game, const string& name);

        string getRole() const override;
        void tax() override;                  // Override tax to collect 3 coins
        void undo(Player& target) override;   // Governor can undo tax
};

}

#endif // GOVERNOR_HPP
