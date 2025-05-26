//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GUI.hpp"
#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    // Displays a screen where the user selects how many players will play (2–6)
    void launchPlayerSetupScreen(Game& game) {
        RenderWindow window(VideoMode(800, 600), "Player Setup");

        // Load font
        Font font;
        if (!font.loadFromFile("GUI/assets/Carlito-Regular.ttf")) {
            cerr << "Failed to load Carlito-Regular.ttf\n";
            return;
        }

        // Load background image
        Sprite background;
        try {
            background = loadAndScaleBackground("GUI/assets/background.jpg", window);
        } catch (const exception& e) {
            cerr << e.what() << '\n';
            return;;
        }

        // Dark overlay for better text contrast
        RectangleShape overlay(Vector2f(window.getSize()));
        overlay.setFillColor(Color(0, 0, 0, 150));

        Text title = createTitle("How many players?", font, window);    // Title prompt

        // Create 5 buttons for 2–6 players
        vector<RectangleShape> buttons;
        vector<Text> labels;
        for (int i = 2; i <= 6; ++i) {
            RectangleShape button;
            Text label;
            Vector2f size(60, 60);
            Vector2f position(180 + (i - 2) * 90, 300); // Spread buttons horizontally
            createButton(to_string(i), font, button, label, size, position);
            buttons.push_back(button);
            labels.push_back(label);
        }

        // Event loop
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {

                // Window closed manually
                if (event.type == Event::Closed)
                    window.close();

                // Mouse click on a player count button
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    for (int i = 0; i < (int)buttons.size(); ++i) {
                        if (buttons[i].getGlobalBounds().contains(mousePos)) {
                            int playerCount = i + 2;
                            cout << "Selected " << playerCount << " players\n";
                            window.close();
                            launchNameEntryScreen(game, playerCount);   // Go to name entry screen
                            return;
                        }
                    }
                }

                // Button hover effect
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
