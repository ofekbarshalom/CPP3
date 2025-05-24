//ofekbarshalom@gmail.com

#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "Player.hpp"

using namespace std;

namespace coup {

    class Game {
        private:
            vector<Player*> players_list;  // All players in join order
            size_t turn_index;             // Whose turn is it (index into players_list)

        public:
            Game();
            ~Game();

            // Turn-related
            string turn() const;
            void advanceTurn();

            // Player management
            void addPlayer(Player* player);
            void removePlayer(Player* player);
            vector<string> players() const;
            const vector<Player*>& getPlayers() const;
            string winner() const;
    };

}

#endif // GAME_HPP