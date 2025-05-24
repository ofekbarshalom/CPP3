//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GUI.hpp"
#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    bool launchOpeningScreen() {
        RenderWindow window(VideoMode(800, 600), "Coup");

        Font font;
        if (!font.loadFromFile("GUI/assets/Carlito-Regular.ttf")) {
            cerr << "Failed to load Carlito-Regular.ttf\n";
            return false;
        }

        Sprite background;
        try {
            background = loadAndScaleBackground("GUI/assets/background.jpg", window);
        } catch (const exception& e) {
            cerr << e.what() << '\n';
            return false;
        }

        RectangleShape overlay(Vector2f(window.getSize()));
        overlay.setFillColor(Color(0, 0, 0, 150));

        Text title = createTitle("Welcome to Coup!", font, window);

        RectangleShape startButton;
        Text buttonText;
        createButton("Start Game", font, startButton, buttonText, {200, 60}, {window.getSize().x / 2.f - 100, 300});

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed){
                    window.close();
                    return false;
                }

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (startButton.getGlobalBounds().contains(mousePos)) {
                        cout << "Game Starting...\n";
                        window.close();
                        return true; // User clicked "Start Game"
                    }
                }
            }

            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (startButton.getGlobalBounds().contains(mousePos)) {
                startButton.setFillColor(Color(80, 80, 80));
            } else {
                startButton.setFillColor(Color(50,50,50));
            }

            window.clear();
            window.draw(background);
            window.draw(overlay);
            window.draw(title);
            window.draw(startButton);
            window.draw(buttonText);
            window.display();
        }

        return false;
    }
}