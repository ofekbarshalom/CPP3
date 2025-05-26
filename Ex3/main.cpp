//ofekbarshalom@gmail.com

#include "GUI/Screens.hpp"
#include "src/Game.hpp"

using namespace coup;  

int main() {
    // Launch opening screen. If user clicks "Start Game", continue.
    if(launchOpeningScreen()) {
        Game game_1{};  // Create a new game instance
        launchPlayerSetupScreen(game_1);  // Proceed to player setup screen
    }
    
    return 0;
}
