//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <vector>

#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    // Displays a popup window with an error message and a single "OK" button
    void showErrorPopup(const Font& font, const string& message) {
        RenderWindow popup(VideoMode(400, 200), "Action Error");

        // Error message text
        Text msg(message, font, 18);
        msg.setFillColor(Color::White);
        msg.setPosition(30, 50);

        // OK button
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

                // Window closed manually
                if (event.type == Event::Closed)
                    popup.close();

                // Click on OK button
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f click(event.mouseButton.x, event.mouseButton.y);
                    if (okBtn.getGlobalBounds().contains(click)) {
                        popup.close();
                    }
                }
            }

            // Render the popup
            popup.clear(Color(30, 30, 30));
            popup.draw(msg);
            popup.draw(okBtn);
            popup.draw(okTxt);
            popup.display();
        }
    }

}