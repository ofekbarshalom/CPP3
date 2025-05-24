#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <stdexcept>

using namespace std;

namespace coup {

    class Game; // Forward declaration

    class Player {
        protected:
            Game* game;
            string name;
            int coins;
            bool alive;
            bool sanctioned = false;
            bool arrestBlocked = false;

            string last_action;
            Player* last_target = nullptr;

        public:
            Player(Game& game, const string& name);
            virtual ~Player() = default;

            // Info accessors
            const string& getName() const;
            int getCoins() const;
            void setAlive(bool val);
            void setArrestBlocked(bool val);
            bool isAlive() const;
            virtual string getRole() const = 0;

            // Actions
            virtual void gather();            // +1 coin
            virtual void tax();
            virtual void bribe();
            virtual void arrest(Player& target);
            virtual void sanction(Player& target);
            virtual void coup(Player& target);
            virtual void undo(Player& target);

            // Helpers
            Game& getGame();
            void addCoins(int amount);
            void removeCoins(int amount);
            const string& getLastAction() const;
            Player* getLastTarget() const;
            void setLastAction(const string& action, Player* target = nullptr);
            void requireMyTurnAndAlive() const;
    };

} // namespace coup

#endif // PLAYER_HPP