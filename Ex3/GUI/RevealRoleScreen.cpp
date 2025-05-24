#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "GUI.hpp"
#include "Screens.hpp"
#include "Game.hpp"
#include "Player.hpp"

using namespace sf;
using namespace std;

namespace coup {

    void launchRevealRolesScreen(Game& game) {
        RenderWindow window(VideoMode(800, 600), "Player Roles");

        Font font;
        if (!font.loadFromFile("GUI/assets/Carlito-Regular.ttf")) {
            cerr << "Failed to load font\n";
            return;
        }

        Sprite background;
        try {
            background = loadAndScaleBackground("GUI/assets/background.jpg", window);
        } catch (const exception& e) {
            cerr << e.what() << '\n';
            return;
        }

        RectangleShape overlay(Vector2f(window.getSize()));
        overlay.setFillColor(Color(0, 0, 0, 150));

        Text title = createTitle("Player Roles", font, window);

        // Button
        RectangleShape startButton;
        Text buttonText;
        createButton("Start Game", font, startButton, buttonText, {200, 60}, {window.getSize().x / 2.f - 100, 500});

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (startButton.getGlobalBounds().contains(mousePos)) {
                        window.close();
                        launchMainGameScreen(game);
                        return;
                    }
                }
            }

            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            startButton.setFillColor(
                startButton.getGlobalBounds().contains(mousePos) ? Color(80, 80, 80) : Color(50, 50, 50)
            );

            window.clear();
            window.draw(background);
            window.draw(overlay);
            window.draw(title);

            // List players + roles
            const auto& allPlayers = game.getPlayers();
            float y = 160.f;

            for (Player* p : allPlayers) {
                stringstream ss;
                ss << p->getName() << " - " << p->getRole();
                Text playerText(ss.str(), font, 24);
                playerText.setPosition(100, y);
                playerText.setFillColor(Color::White);
                window.draw(playerText);
                y += 40;
            }

            window.draw(startButton);
            window.draw(buttonText);
            window.display();
        }
    }

}
