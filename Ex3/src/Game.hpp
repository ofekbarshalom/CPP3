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
            size_t turn_index;             // Index of the player whose turn it is

        public:
            Game();
            ~Game();

            // Returns the name of the player whose turn it is
            string turn() const;

            // Advances turn to the next alive player
            void advanceTurn();

            // Player management
            void addPlayer(Player* player);             // Adds a player to the game (up to 6 allowed)
            void removePlayer(Player* player);          // Marks a player as dead (doesn't remove from list)
            vector<string> players() const;             // Returns a list of player names in the game
            const vector<Player*>& getPlayers() const;  // Returns names of all alive players
            string winner() const;                      // Returns the name of the winner (the last player alive)      
    };

}

#endif // GAME_HPP