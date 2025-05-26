//ofekbarshalom@gmail.com

#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    // Displays a popup showing how many coins a player has (used by Spy)
    void showSpyPeekPopup(const Font& font, const string& name, int coins) {
        RenderWindow popup(VideoMode(400, 200), "Spy Peek");

        // Message text: "<Player> has <X> coins."
        string msgText = name + " has " + to_string(coins) + " coins.";
        Text msg(msgText, font, 20);
        msg.setFillColor(Color::White);
        msg.setPosition(50, 60);

        // "OK" button
        RectangleShape okBtn(Vector2f(200, 40));
        okBtn.setPosition(100, 120);
        okBtn.setFillColor(Color(60, 60, 60));

        // OK button label
        Text okTxt("OK", font, 20);
        okTxt.setFillColor(Color::White);
        okTxt.setPosition(okBtn.getPosition().x + 80, okBtn.getPosition().y + 8);

        // Main event loop
        while (popup.isOpen()) {
            Event event;
            while (popup.pollEvent(event)) {

                // If user closes window
                if (event.type == Event::Closed)
                    popup.close();


                // If user clicks the OK button
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f click(event.mouseButton.x, event.mouseButton.y);
                    if (okBtn.getGlobalBounds().contains(click)) {
                        popup.close();
                    }
                }
            }

            // Draw everything
            popup.clear(Color(30, 30, 30));
            popup.draw(msg);
            popup.draw(okBtn);
            popup.draw(okTxt);
            popup.display();
        }
    }

}
