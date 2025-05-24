//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <set>

#include "GUI.hpp"
#include "Game.hpp"
#include "Screens.hpp"

#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"

using namespace sf;
using namespace std;

namespace coup {

    void launchNameEntryScreen(Game& game, int playerCount) {
    RenderWindow window(VideoMode(800, 600), "Enter Player Names");

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

    Text title = createTitle("Enter Player Names", font, window);

    // Total height of form = inputs + gap + button
    float blockHeight = playerCount * 60 + 30 + 60;
    float startY = (600 - blockHeight) / 2.f;

    title.setPosition(window.getSize().x / 2.f, startY - 50);  // Move title above form

    vector<RectangleShape> boxes;
    vector<Text> inputs(playerCount);
    vector<string> names(playerCount);
    int activeBox = 0;

    for (int i = 0; i < playerCount; ++i) {
        RectangleShape box(Vector2f(300, 40));
        box.setPosition(250, startY + i * 60);
        box.setFillColor(i == activeBox ? Color(80, 80, 80) : Color(50, 50, 50));
        boxes.push_back(box);

        inputs[i].setFont(font);
        inputs[i].setCharacterSize(20);
        inputs[i].setFillColor(Color::White);
    }

    // Button placed 30px under last input box
    RectangleShape startButton;
    Text buttonText;
    float buttonY = startY + playerCount * 60 + 30;
    createButton("Continue", font, startButton, buttonText, {200, 60}, {300, buttonY});

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (activeBox < playerCount && event.text.unicode < 128) {
                    char ch = static_cast<char>(event.text.unicode);
                    if (ch == '\b') {
                        if (!names[activeBox].empty())
                            names[activeBox].pop_back();
                    } else if (isprint(ch) && names[activeBox].size() < 16) {
                        names[activeBox] += ch;
                    }
                    inputs[activeBox].setString(names[activeBox]);
                    FloatRect bounds = inputs[activeBox].getLocalBounds();
                    inputs[activeBox].setOrigin(bounds.left, bounds.top);
                    inputs[activeBox].setPosition(
                        boxes[activeBox].getPosition().x + 10,
                        boxes[activeBox].getPosition().y + 5
                    );
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
                activeBox = (activeBox + 1) % playerCount;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (startButton.getGlobalBounds().contains(mousePos)) {
                    window.close();

                    // Create random-role players
                    srand(time(nullptr));
                    vector<function<Player*(Game&, const string&)>> roleFactories = {
                        [](Game& g, const string& n) { return new Governor(g, n); },
                        [](Game& g, const string& n) { return new Spy(g, n); },
                        [](Game& g, const string& n) { return new Baron(g, n); },
                        [](Game& g, const string& n) { return new General(g, n); },
                        [](Game& g, const string& n) { return new Judge(g, n); },
                        [](Game& g, const string& n) { return new Merchant(g, n); }
                    };
                    
                    set<string> seen;
                    for (const string& name : names) {
                        if (seen.count(name)) {
                            showErrorPopup(font, "Duplicate name detected: " + name);
                            window.close();
                            launchNameEntryScreen(game, playerCount);
                            return;
                        }
                        seen.insert(name);
                    }

                    for (const string& name : names) {
                        int i = rand() % roleFactories.size();
                        roleFactories[i](game, name);
                        cout << "Created player: " << name << endl;
                    }

                    launchRevealRolesScreen(game);
                    return;
                }

                for (int i = 0; i < playerCount; ++i) {
                    if (boxes[i].getGlobalBounds().contains(mousePos)) {
                        activeBox = i;
                    }
                }
            }
        }

        // Hover effect for button
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (startButton.getGlobalBounds().contains(mousePos)) {
            startButton.setFillColor(Color(80, 80, 80));
        } else {
            startButton.setFillColor(Color(50, 50, 50));
        }

        for (int i = 0; i < playerCount; ++i) {
            boxes[i].setFillColor(i == activeBox ? Color(80, 80, 80) : Color(50, 50, 50));
        }

        window.clear();
        window.draw(background);
        window.draw(overlay);
        window.draw(title);
        for (int i = 0; i < playerCount; ++i) {
            window.draw(boxes[i]);
            window.draw(inputs[i]);
        }
        window.draw(startButton);
        window.draw(buttonText);
        window.display();
    }
}


}
