//ofekbarshalom@gmail.com

#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>

namespace coup {

    Game::Game() : turn_index(0) {}

    Game::~Game() {
        for (Player* p : players_list) {
            delete p;
        }
    }

    string Game::turn() const {
        if (players_list.empty()) {
            throw runtime_error("No players in the game.");
        }
        return players_list.at(turn_index)->getName();
    }

    void Game::advanceTurn() {
        if (players_list.empty()) {
            throw runtime_error("No players to advance turn.");
        }

        size_t n = players_list.size();
        for (size_t i = 1; i <= n; ++i) {
            size_t next_index = (turn_index + i) % n;
            if (players_list[next_index]->isAlive()) {
                turn_index = next_index;
                return;
            }
        }

        throw runtime_error("No alive players remaining.");
    }

    void Game::addPlayer(Player* player) {
        if (players_list.size() >= 6) {
            throw runtime_error("Maximum number of players (6) reached.");
        }
        players_list.push_back(player);
    }

    void Game::removePlayer(Player* player) {
        player->setAlive(false);
    }

    vector<string> Game::players() const {
        vector<string> active;
        for (Player* p : players_list) {
            if (p->isAlive()) {
                active.push_back(p->getName());
            }
        }
        return active;
    }

    const vector<Player*>& Game::getPlayers() const {
        return players_list;
    }

    string Game::winner() const {
        vector<string> alive_names = players();
        if (alive_names.size() != 1) {
            throw runtime_error("Game is still active — no winner yet.");
        }
        return alive_names[0];
    }

}
