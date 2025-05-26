//ofekbarshalom@gmail.com

#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>

namespace coup {

    // Constructor: initializes turn index to 0
    Game::Game() : turn_index(0) {}

    // Destructor: frees all dynamically allocated players
    Game::~Game() {
        for (Player* p : players_list) {
            delete p;   // Free memory for each player
        }
    }

    // Returns the name of the player whose turn it is
    string Game::turn() const {
        if (players_list.empty()) {
            throw runtime_error("No players in the game.");
        }
        return players_list.at(turn_index)->getName();
    }

    // Advances turn to the next alive player
    void Game::advanceTurn() {
        if (players_list.empty()) {
            throw runtime_error("No players to advance turn.");
        }

        size_t n = players_list.size();

        // Try each player after the current one
        for (size_t i = 1; i <= n; ++i) {
            size_t next_index = (turn_index + i) % n;
            if (players_list[next_index]->isAlive()) {
                turn_index = next_index;
                return;
            }
        }

        // All players are dead
        throw runtime_error("No alive players remaining.");
    }

    // Adds a player to the game (up to 6 allowed)
    void Game::addPlayer(Player* player) {
        if (players_list.size() >= 6) {
            throw runtime_error("Maximum number of players (6) reached.");
        }
        players_list.push_back(player);
    }

    // Marks a player as dead (doesn't remove from list)
    void Game::removePlayer(Player* player) {
        player->setAlive(false);
    }

    // Returns names of all currently alive players
    vector<string> Game::players() const {
        vector<string> active;
        for (Player* p : players_list) {
            if (p->isAlive()) {
                active.push_back(p->getName());
            }
        }
        return active;
    }

    // Returns reference to all players (alive or dead)
    const vector<Player*>& Game::getPlayers() const {
        return players_list;
    }

    // Returns the winner's name if exactly one player is alive
    string Game::winner() const {
        vector<string> alive_names = players();
        if (alive_names.size() != 1) {
            throw runtime_error("Game is still active — no winner yet.");
        }
        return alive_names[0];
    }

}
