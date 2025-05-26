//ofekbarshalom@gmail.com

#ifndef BARON_HPP
#define BARON_HPP

#include "Player.hpp"

namespace coup {

// Baron role: Can invest money for profit and gains compensation when sanctioned
class Baron : public Player {
    public:
        Baron(Game& game, const string& name);

        string getRole() const override;
        void invest();  // Pay 3 coins, receive 6 coins
};

} // namespace coup

#endif // BARON_HPP
