#include <SFML/Graphics.hpp>
#include <iostream>

#include "GUI.hpp"
#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    void launchPlayerSetupScreen(Game& game) {
        RenderWindow window(VideoMode(800, 600), "Player Setup");

        Font font;
        if (!font.loadFromFile("GUI/assets/Carlito-Regular.ttf")) {
            cerr << "Failed to load Carlito-Regular.ttf\n";
            return;
        }

        Sprite background;
        try {
            background = loadAndScaleBackground("GUI/assets/background.jpg", window);
        } catch (const exception& e) {
            cerr << e.what() << '\n';
            return;;
        }

        RectangleShape overlay(Vector2f(window.getSize()));
        overlay.setFillColor(Color(0, 0, 0, 150));

        Text title = createTitle("How many players?", font, window);

        // Create 5 buttons for 2–6 players using GUI::createButton
        vector<RectangleShape> buttons;
        vector<Text> labels;
        for (int i = 2; i <= 6; ++i) {
            RectangleShape button;
            Text label;
            Vector2f size(60, 60);
            Vector2f position(180 + (i - 2) * 90, 300);
            createButton(to_string(i), font, button, label, size, position);
            buttons.push_back(button);
            labels.push_back(label);
        }

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    for (int i = 0; i < (int)buttons.size(); ++i) {
                        if (buttons[i].getGlobalBounds().contains(mousePos)) {
                            int playerCount = i + 2;
                            cout << "Selected " << playerCount << " players\n";
                            window.close();
                            launchNameEntryScreen(game, playerCount);
                            return;
                        }
                    }
                }

                // Hover effect
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(mousePos)) {
                        buttons[i].setFillColor(Color(80, 80, 80));  // hover
                    } else {
                        buttons[i].setFillColor(Color(50, 50, 50));  // default
                    }
                }
            }

            // Draw everything
            window.clear();
            window.draw(background);
            window.draw(overlay);
            window.draw(title);
            for (size_t i = 0; i < buttons.size(); ++i) {
                window.draw(buttons[i]);
                window.draw(labels[i]);
            }
            window.display();
        }
    }

}
