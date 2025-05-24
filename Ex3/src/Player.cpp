//ofekbarshalom@gmail.com

#include "Player.hpp"
#include "Game.hpp"
#include "Merchant.hpp"
#include "Baron.hpp"
#include "Judge.hpp"
#include "General.hpp"

namespace coup {

    Player::Player(Game& game, const string& name) : game(&game), name(name), coins(0), alive(true), last_action(""), last_target(nullptr) {
        game.addPlayer(this);
    }

    const string& Player::getName() const {
        return name;
    }

    int Player::getCoins() const {
        return coins;
    }

    bool Player::isAlive() const {
        return alive;
    }

    void Player::setArrestBlocked(bool val) {
        arrestBlocked = val;
    }

    void Player::setAlive(bool val) {
        alive = val;
    }

    // Helper function to check if it's the player's turn and if they are alive
    void Player::requireMyTurnAndAlive() const {
        if (!alive) {
            throw runtime_error(name + " is dead.");
        }
        if (game->turn() != name) {
            throw runtime_error("It's not " + name + "'s turn.");
        }
    }

    void Player::gather() {
        requireMyTurnAndAlive();

        if (coins >= 10) {
            throw runtime_error("You must coup when holding 10 or more coins.");
        }

        if(sanctioned) {
            throw runtime_error("You are sanctioned and cannot gather.");
        }

        coins += 1;
        string previousAction = last_action;
        setLastAction("gather");
        arrestBlocked = false; // Clear arrest block after action

        if(previousAction != "bribe") {
            game->advanceTurn();
        }
    }

    void Player::tax() {
        requireMyTurnAndAlive();
        if (coins >= 10) {
            throw runtime_error("You must coup when holding 10 or more coins.");
        }
        if(sanctioned) {
            throw runtime_error("You are sanctioned and cannot tax.");
        }
        coins += 2;
        string previousAction = last_action;
        setLastAction("tax");
        arrestBlocked = false; // Clear arrest block after action

        if(previousAction != "bribe") {
            game->advanceTurn();
        }
    }

    void Player::bribe() {
        requireMyTurnAndAlive();
        if (coins >= 10) {
            throw runtime_error("You must coup when holding 10 or more coins.");
        }
        removeCoins(4);
        setLastAction("bribe");
        sanctioned = false; // Clear sanction after action
        arrestBlocked = false; // Clear arrest block after action
    }

    void Player::arrest(Player& target) {
        requireMyTurnAndAlive();
        if (arrestBlocked) {
            throw runtime_error("Arrest blocked by Spy.");
        }
        if (coins >= 10) {
            throw runtime_error("You must coup when holding 10 or more coins.");
        }
        if (!target.isAlive()) {
            throw runtime_error("Target is already eliminated.");
        }
        if (last_action == "arrest" && last_target == &target) {
            throw runtime_error("Cannot arrest the same player twice in a row.");
        }
        if (target.getCoins() == 0) {
            throw runtime_error("Target has no coins to take.");
        }
        
        if (dynamic_cast<Merchant*>(&target)) {
            target.removeCoins(2);  // Take 2 from the Merchant
        } else {
            target.removeCoins(1);
            coins += 1;
        }
        
        if (dynamic_cast<General*>(&target)) {
            target.addCoins(1);  // Refund the General
        }
        
        string previousAction = last_action;
        setLastAction("arrest", &target);
        sanctioned = false; // Clear sanction after action

        if(previousAction != "bribe") {
            game->advanceTurn();
        }
    }

    void Player::sanction(Player& target) {
        requireMyTurnAndAlive();
        if (coins >= 10) {
            throw runtime_error("You must coup when holding 10 or more coins.");
        }
        if (!target.isAlive()) {
            throw runtime_error("Target is already eliminated.");
        }

        // Baron gets 1 coin compensation when sanctioned
        if (dynamic_cast<Baron*>(&target)) {
            target.addCoins(1);
        }

        // Player attacked a Judge so they lose 1 more coin
        if (dynamic_cast<Judge*>(&target)) {
            removeCoins(1);
        }

        removeCoins(3);
        string previousAction = last_action;
        setLastAction("sanction", &target);
        target.sanctioned = true;

        
        sanctioned = false; // Clear sanction after action
        arrestBlocked = false; // Clear arrest block after action
        
        if(previousAction != "bribe") {
            game->advanceTurn();
        }
    }

    void Player::coup(Player& target) {
        requireMyTurnAndAlive();

        if (!target.isAlive()) {
            throw runtime_error("Target is already eliminated.");
        }

        removeCoins(7);
        target.alive = false;
        string previousAction = last_action;
        setLastAction("coup", &target);
        game->removePlayer(&target);
        sanctioned = false; // Clear sanction after action
        arrestBlocked = false; // Clear arrest block after action
        
        if(previousAction != "bribe") {
            game->advanceTurn();
        }
    }

    void Player::undo(Player& /*target*/) {
        throw runtime_error("This role does not support undo.");
    }

    Game& Player::getGame() {
        return *game;
    }

    void Player::addCoins(int amount) {
        coins += amount;
    }

    void Player::removeCoins(int amount) {
        if (coins < amount) {
            throw runtime_error("Not enough coins for this action.");
        }
        coins -= amount;
    }

    const string& Player::getLastAction() const {
        return last_action;
    }

    Player* Player::getLastTarget() const {
        return last_target;
    }

    void Player::setLastAction(const string& action, Player* target) {
        last_action = action;
        last_target = target;
    }
    
};