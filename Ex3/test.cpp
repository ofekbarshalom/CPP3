#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"

using namespace coup;
using namespace std;

// Test cases for the Game class
TEST_CASE("Game class tests") {
    // Create a game instance and players
    Game game;

    Player* governor = new Governor(game, "Governor");
    Player* spy = new Spy(game, "Spy");
    Player* baron = new Baron(game, "Baron");
    Player* general = new General(game, "General");
    Player* judge = new Judge(game, "Judge");
    Player* merchant = new Merchant(game, "Merchant");

    // Initialize tests
    SUBCASE("Initial player list and order") {
        CHECK(game.players().size() == 6);
        CHECK(game.turn() == "Governor");
    }

     SUBCASE("Initial coin count") {
        CHECK(governor->getCoins() == 0);
        CHECK(spy->getCoins() == 0);
    }

    SUBCASE("Initial roles") {
        CHECK(judge->getRole() == "Judge");
        CHECK(merchant->getRole() == "Merchant");
    }


    // turn() tests
    SUBCASE("Calling turn() with no players throws") {
        Game emptyGame;
        CHECK_THROWS_AS(emptyGame.turn(), runtime_error);
    }


    // advanceTurn() tests
    SUBCASE("Calling advanceTurn() with no players throws") {
        Game emptyGame;
        CHECK_THROWS_AS(emptyGame.advanceTurn(), runtime_error);
    }

    SUBCASE("Advance turn only to alive players") {
        game.advanceTurn();
        CHECK(game.turn() == "Spy");

        // Kill next in turn (Baron) and advance
        game.removePlayer(baron);
        game.advanceTurn();  // Should skip Baron
        CHECK(game.turn() == "General");
    }

    SUBCASE("advanceTurn throws if all players are dead") {
        game.removePlayer(governor);
        game.removePlayer(spy);
        game.removePlayer(baron);
        game.removePlayer(general);
        game.removePlayer(judge);
        game.removePlayer(merchant);
        CHECK_THROWS_AS(game.advanceTurn(), runtime_error);
    }


    // addPlayer() tests
    SUBCASE("Adding more than 6 players throws") {
        CHECK_THROWS_AS(new Governor(game, "7"), runtime_error);
    }


    // removePlayer() tests
    SUBCASE("Removing a player marks them dead") {
        CHECK(spy->isAlive());
        game.removePlayer(spy);
        CHECK_FALSE(spy->isAlive());
        auto players = game.players();
        CHECK(find(players.begin(), players.end(), "Spy") == players.end());
    }


    // players() test
    SUBCASE("players() returns only alive player names") {
        game.removePlayer(spy);
        
        vector<string> activeNames = game.players();
        CHECK(activeNames.size() == 5);
        CHECK(find(activeNames.begin(), activeNames.end(), "Spy") == activeNames.end());
        CHECK(find(activeNames.begin(), activeNames.end(), "Governor") != activeNames.end());
    }


    // getPlayers() test
    SUBCASE("getPlayers() returns all player objects, dead or alive") {
        const vector<Player*>& allPlayers = game.getPlayers();
        CHECK(allPlayers.size() == 6); // Even if some are dead

        // Confirm the actual object pointers are there
        bool foundSpy = false;
        bool foundGovernor = false;
        for (Player* p : allPlayers) {
            if (p == spy) foundSpy = true;
            if (p == governor) foundGovernor = true;
        }
        CHECK(foundSpy);
        CHECK(foundGovernor);
    }


    // winner() tests
    SUBCASE("Winner detection") {
        // Eliminate all but one
        game.removePlayer(spy);
        game.removePlayer(baron);
        game.removePlayer(general);
        game.removePlayer(judge);
        game.removePlayer(merchant);

        CHECK_NOTHROW(game.winner());
        CHECK(game.winner() == "Governor");
    }

    SUBCASE("Winner exception when game not over") {
        CHECK_THROWS_AS(game.winner(), runtime_error);
    }

}



// Test cases for the Player class
TEST_CASE("Player class tests") {
    Game game;

    // Create two players for testing
    class DummyPlayer : public coup::Player {
    public:
        DummyPlayer(Game& g, const string& name) : Player(g, name) {}
        string getRole() const override { return "Dummy"; }
    };


    Player* p1 = new DummyPlayer(game, "Alice");
    Player* p2 = new DummyPlayer(game, "Bob");

    SUBCASE("Player initialization") {
        CHECK(p1->getName() == "Alice");
        CHECK(p1->getCoins() == 0);
        CHECK(p1->isAlive());
        CHECK(p1->getRole() != "");
    }

    SUBCASE("Dead player cannot perform actions") {
        p1->setAlive(false);
        CHECK_THROWS(p1->gather());
        CHECK_THROWS(p1->tax());
        CHECK_THROWS(p1->bribe());
        CHECK_THROWS(p1->coup(*p2));
        CHECK_THROWS(p1->arrest(*p2));
        CHECK_THROWS(p1->sanction(*p2));
    }

    SUBCASE("Cannot target dead player") {
        game.removePlayer(p2);
        p1->addCoins(10);
        CHECK_THROWS(p1->arrest(*p2));
        CHECK_THROWS(p1->sanction(*p2));
        CHECK_THROWS(p1->coup(*p2));
    }

    SUBCASE("requireMyTurnAndAlive() test") {
        // Should not throw if it's Alice's turn and she's alive
        CHECK_NOTHROW(p1->requireMyTurnAndAlive());

        // Advance turn to Bob
        game.advanceTurn();
        CHECK_THROWS_WITH(p1->requireMyTurnAndAlive(), "It's not Alice's turn.");

        // Kill Alice and check
        p1->setAlive(false);
        CHECK_THROWS_WITH(p1->requireMyTurnAndAlive(), "Alice is dead.");
    }


    // gather() tests
    SUBCASE("gather adds one coin and advances turn") {
        CHECK(p1->getCoins() == 0);
        p1->gather();
        CHECK(p1->getCoins() == 1);
        CHECK(game.turn() == "Bob");
    }

    // Sanction blocks gather
    SUBCASE("gather fails if sanctioned") {
        game.advanceTurn();
        p2->addCoins(5);
        p2->sanction(*p1);
        CHECK_THROWS_WITH(p1->gather(), "You are sanctioned and cannot gather.");
    }


    // tax() tests
    SUBCASE("tax gives 2 coins") {
        p1->tax();
        CHECK(p1->getCoins() == 2);
    }

    // Sanction blocks tax
    SUBCASE("tax fails when sanctioned") {
        game.advanceTurn();
        p2->addCoins(5);
        p2->sanction(*p1);
        CHECK_THROWS_WITH(p1->tax(), "You are sanctioned and cannot tax.");
    }


    // bribe() tests
    SUBCASE("bribe works correctly") {
        p1->addCoins(5);
        p1->bribe();
        CHECK(p1->getCoins() == 1);
        CHECK(p1->getLastAction() == "bribe");
        p1->tax();
        CHECK(game.turn() == "Alice"); // Should still be Alice's turn
    }


    // arrest() tests
    SUBCASE("arrest works correctly") {
        p1->addCoins(5);
        p2->addCoins(1);
        p1->arrest(*p2);
        CHECK(p1->getCoins() == 6);
        CHECK(p2->getCoins() == 0);
        CHECK(p1->getLastAction() == "arrest");
        CHECK(p1->getLastTarget() == p2);
    }

    // Arrest cannot target the same player twice in a row
    SUBCASE("arrest target limitation") {
        p2->addCoins(4);
        p1->arrest(*p2);
        game.advanceTurn();
        CHECK_THROWS_WITH(p1->arrest(*p2), "Cannot arrest the same player twice in a row.");
    }

    // Arrest fails if target is dead
    SUBCASE("arrest fails if target dead") {
        game.removePlayer(p2);
        CHECK_THROWS_WITH(p1->arrest(*p2), "Target is already eliminated.");
    }


    // sanction() tests
    SUBCASE("sanction works correctly") {
        p1->addCoins(5);
        p1->sanction(*p2);
        CHECK(p1->getCoins() == 2);
        CHECK_THROWS_WITH(p2->gather(), "You are sanctioned and cannot gather.");
    }


    // coup() tests
    SUBCASE("coup works correctly") {
        p1->addCoins(10);
        p1->coup(*p2);
        CHECK(p1->getCoins() == 3);
        CHECK(!p2->isAlive());
    }

    SUBCASE("Cannot perform non-coup actions when holding 10+ coins") {
        p1->addCoins(10);
        CHECK_THROWS(p1->gather());
        CHECK_THROWS(p1->tax());
        CHECK_THROWS(p1->bribe());
        CHECK_THROWS(p1->sanction(*p2));
        CHECK_THROWS(p1->arrest(*p2));
    }


    // undo() test
    SUBCASE("Base undo() throws") {
        CHECK_THROWS_WITH(p1->undo(*p2), "This role does not support undo.");
    }


    // getGame() test
    SUBCASE("getGame returns correct reference") {
        Game& ref = p1->getGame();
        CHECK(&ref == &game);
    }


    // addCoins() and removeCoins() tests
    SUBCASE("addCoins and removeCoins") {
        p1->addCoins(7);
        CHECK(p1->getCoins() == 7);
        p1->removeCoins(3);
        CHECK(p1->getCoins() == 4);
    }

    SUBCASE("removeCoins throws if not enough coins") {
        p1->addCoins(2);
        CHECK_THROWS_WITH(p1->removeCoins(5), "Not enough coins for this action.");
    }


    // action setup tests
    SUBCASE("setLastAction and getLastAction/Target") {
        p1->setLastAction("custom_action", p2);
        CHECK(p1->getLastAction() == "custom_action");
        CHECK(p1->getLastTarget() == p2);
    }
}


// Test cases for the Governor class
TEST_CASE("Governor behavior") {
    Game game;
    Player* gov = new Governor(game, "Gov");
    Player* other = new Merchant(game, "Other");  // Any neutral role

    // getRole() test
    SUBCASE("Governor role is correct") {
        CHECK(gov->getRole() == "Governor");
    }

    // Tax bonus test
    SUBCASE("Governor tax gives 3 coins") {
        gov->tax();
        CHECK(gov->getCoins() == 3);
    }

    // undo tax tests
    SUBCASE("Governor undo removes 2 coins from taxer") {
        game.advanceTurn();  
        other->tax();         
        gov->undo(*other);    
        CHECK(other->getCoins() == 0);
    }

    SUBCASE("Governor undo fails if target has no tax action") {
        CHECK_THROWS_WITH(gov->undo(*other), "Governor can only undo a tax action.");
    }

    SUBCASE("Governor undo fails if target is dead") {
        game.removePlayer(other);
        CHECK_THROWS_WITH(gov->undo(*other), "Cannot undo a dead player.");
    }

    SUBCASE("Governor undo fails if target has < 2 coins") {
        game.advanceTurn(); 
        other->tax();     
        other->removeCoins(1);
        CHECK_THROWS_WITH(gov->undo(*other), "Target does not have enough coins to undo tax.");
    }
}



// Test cases for the Spy class
TEST_CASE("Spy behavior") {
    Game game;
    Spy* spy = new Spy(game, "Spy");
    General* target = new General(game, "Target");  // Use General to test arrestBlocked behavior

    // getRole() test
    SUBCASE("Spy role is correct") {
        CHECK(spy->getRole() == "Spy");
    }

    // blockArrest() tests
    SUBCASE("Spy can block arrest") {
        spy->blockArrest(*target);
        CHECK(game.turn() == "Spy");  // Should still be Spy's turn
        game.advanceTurn();
        CHECK_THROWS_WITH(target->arrest(*spy), "Arrest blocked by Spy.");
    }

    SUBCASE("Spy cannot block arrest of dead target") {
        game.removePlayer(target);
        CHECK_THROWS_WITH(spy->blockArrest(*target), "Target is dead.");
    }

    // peek() tests
    SUBCASE("Spy can peek at alive target") {
        spy->peek(*target);
        CHECK(game.turn() == "Spy");  // Should still be Spy's turn
        CHECK(spy->getLastAction() == "peek");
        CHECK(spy->getLastTarget() == target);
    }

    SUBCASE("Spy cannot peek dead target") {
        game.removePlayer(target);
        CHECK_THROWS_WITH(spy->peek(*target), "Target is dead.");
    }
}



// Test cases for the Baron class
TEST_CASE("Baron behavior") {
    Game game;
    Baron* baron = new Baron(game, "Baron");
    Player* other = new Spy(game, "Other");

    // getRole() test
    SUBCASE("Baron role is correct") {
        CHECK(baron->getRole() == "Baron");
    }

    // invest() tests
    SUBCASE("Baron can invest and gain profit") {
        baron->addCoins(3);
        baron->invest();
        CHECK(baron->getCoins() == 6);
        CHECK(baron->getLastAction() == "invest");
    }

    SUBCASE("Baron cannot invest with less than 3 coins") {
        baron->addCoins(2);
        CHECK_THROWS(baron->invest());
    }

    // sanction() compensation tests
    SUBCASE("Baron gains 1 coin when sanctioned") {
        other->addCoins(5);
        game.advanceTurn();  // Baron -> Other
        other->sanction(*baron);  // triggers +1 coin for Baron
        CHECK(baron->getCoins() == 1);
    }
}


// Test cases for the General class
TEST_CASE("General behavior") {
    Game game;
    General* general = new General(game, "General");
    Player* other = new Spy(game, "Other");

    // getRole() test
    SUBCASE("General role is correct") {
        CHECK(general->getRole() == "General");
    }

    // undo coup tests
    SUBCASE("General can undo a coup with 5 coins") {
        general->addCoins(5);
        general->undo(*other);
        CHECK(general->getCoins() == 0);
        CHECK(general->getLastAction() == "defend_coup");
        CHECK(general->getLastTarget() == other);
    }

    SUBCASE("General cannot undo with less than 5 coins") {
        CHECK_THROWS_WITH(general->undo(*other), "Not enough coins to defend against a coup.");
    }
}


// Test cases for the Judge class
TEST_CASE("Judge behavior") {
    Game game;
    Player* judge = new Judge(game, "Judge");
    Player* other = new Spy(game, "Other");  // neutral role

    // getRole() test
    SUBCASE("Judge role is correct") {
        CHECK(judge->getRole() == "Judge");
    }

    // undo() tests
    SUBCASE("Judge can undo a bribe") {
        other->addCoins(5);
        game.advanceTurn();  // Judge -> Other
        other->bribe();      // perform a bribe
        judge->undo(*other);  // judge cancels it

        CHECK(other->getCoins() == 1);
        CHECK(judge->getLastAction() == "undo_bribe");
        CHECK(judge->getLastTarget() == other);
        CHECK(other->getLastAction() == "bribe_blocked");
    }

    SUBCASE("Judge cannot undo if last action wasn't bribe") {
        game.advanceTurn();  // Judge -> Other
        other->tax();
        CHECK_THROWS_WITH(judge->undo(*other), "Judge can only undo a bribe action.");
    }

    SUBCASE("Judge cannot undo dead player") {
        game.removePlayer(other);
        CHECK_THROWS_WITH(judge->undo(*other), "Cannot undo action of a dead player.");
    }

    // Sanction compensation test
    SUBCASE("Sanctioning Judge costs attacker 4 coins instead of 3") {
        other->addCoins(5);  // enough to afford
        game.advanceTurn();  // Judge -> Other
        other->sanction(*judge);  // costs 4 because Judge is the target
        CHECK(other->getCoins() == 1);
    }
}


// Test cases for the Merchant class
TEST_CASE("Merchant behavior") {
    Game game;
    Merchant* merchant = new Merchant(game, "Merchant");
    Player* other = new Spy(game, "Other");

    // getRole() test
    SUBCASE("Merchant role is correct") {
        CHECK(merchant->getRole() == "Merchant");
    }

    // startTurnBonus() tests
    SUBCASE("Merchant gets bonus at start of turn with 3+ coins") {
        merchant->addCoins(3);
        merchant->startTurnBonus();
        CHECK(merchant->getCoins() == 4);
    }

    SUBCASE("Merchant gets no bonus if under 3 coins") {
        merchant->addCoins(2);
        merchant->startTurnBonus();
        CHECK(merchant->getCoins() == 2);
    }

    SUBCASE("Merchant gets no bonus if dead") {
        game.removePlayer(merchant);
        CHECK_THROWS_WITH(merchant->startTurnBonus(), "Dead players cannot receive start-of-turn bonuses.");
    }

    // arrest() behavior when Merchant is target
    SUBCASE("Merchant loses 2 coins when arrested") {
        other->addCoins(3);
        merchant->addCoins(4);
        game.advanceTurn();
        other->arrest(*merchant);

        CHECK(merchant->getCoins() == 2);  // lost 2
        CHECK(other->getCoins() == 3);     // did not gain a coin
    }
}
