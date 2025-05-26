//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screens.hpp"
#include "GUI.hpp"

using namespace sf;
using namespace std;

namespace coup {

    // Displays the winner screen at the end of the game
    void launchWinnerScreen(const string& winnerName) {
        RenderWindow window(VideoMode(800, 600), "Coup - Winner");

        // Load font
        Font font;
        if (!font.loadFromFile("GUI/assets/Carlito-Regular.ttf")) {
            cerr << "Failed to load font\n";
            return;
        }

        // Load background image
        Sprite background;
        try {
            background = loadAndScaleBackground("GUI/assets/background.jpg", window);
        } catch (const exception& e) {
            cerr << e.what() << '\n';
            return;
        }

        // Overlay to darken background
        RectangleShape overlay(Vector2f(window.getSize()));
        overlay.setFillColor(Color(0, 0, 0, 150));

        // Display winner name in large yellow text
        Text title("Winner: " + winnerName, font, 40);
        title.setFillColor(Color::Yellow);
        FloatRect bounds = title.getLocalBounds();
        title.setOrigin(bounds.width / 2, bounds.height / 2);
        title.setPosition(window.getSize().x / 2.f, 200);

        // "Exit" button
        RectangleShape exitButton;
        Text exitText;
        createButton("Exit", font, exitButton, exitText, {200, 60}, {window.getSize().x / 2.f - 100, 400});

        // Main event loop
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close(); // User closed the window
                }

                // User clicked the Exit button
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (exitButton.getGlobalBounds().contains(mousePos)) {
                        window.close();  // Exit game
                    }
                }
            }

            // Hover effect for the button
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (exitButton.getGlobalBounds().contains(mousePos)) {
                exitButton.setFillColor(Color(80, 80, 80));
            } else {
                exitButton.setFillColor(Color(50, 50, 50));
            }

            // Draw everything
            window.clear();
            window.draw(background);
            window.draw(overlay);
            window.draw(title);
            window.draw(exitButton);
            window.draw(exitText);
            window.display();
        }
    }

}
