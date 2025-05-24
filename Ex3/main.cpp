#include "GUI/Screens.hpp"
#include "src/Game.hpp"

using namespace coup;  

int main() {
    if(launchOpeningScreen()) {
        Game game_1{};
        launchPlayerSetupScreen(game_1);
    }
    
    return 0;
}
