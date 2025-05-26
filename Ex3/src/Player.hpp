//ofekbarshalom@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <stdexcept>

using namespace std;

namespace coup {

    class Game; // Forward declaration

    class Player {              
        protected:
            Game* game;                 // Pointer to the game this player belongs to
            string name;                                      
            int coins;                  // Is the player still in the game
            bool alive;
            bool sanctioned = false;    // if player is currently under sanction
            bool arrestBlocked = false; // if player is currently under arrest block

            string last_action;         // Last action performed by the player
            Player* last_target = nullptr;  // Last target of the player's action

        public:
            Player(Game& game, const string& name);
            virtual ~Player() = default;

            // Info accessors
            const string& getName() const;
            int getCoins() const;
            void setAlive(bool val);
            void setArrestBlocked(bool val);    // Enable/disable arrest block
            bool isAlive() const;
            virtual string getRole() const = 0; // Each player must implement this to return their role

            // Base actions (can be overridden by roles)
            virtual void gather();                  // +1 coin
            virtual void tax();                     // +2 coins
            virtual void bribe();                   // Pay 4 coins to do extra action
            virtual void arrest(Player& target);    // Steal coin from another player
            virtual void sanction(Player& target);  // Block a player from performing gather or tax for one turn
            virtual void coup(Player& target);      // Pay 7 coins to eliminate another player
            virtual void undo(Player& target);      // Undo the last action against another player

            // Utility methods
            Game& getGame();                        // Access game reference
            void addCoins(int amount);
            void removeCoins(int amount);
            const string& getLastAction() const;
            Player* getLastTarget() const;
            void setLastAction(const string& action, Player* target = nullptr);

            // Validates that it's the player's turn and they're alive
            void requireMyTurnAndAlive() const;
    };

} // namespace coup

#endif // PLAYER_HPP