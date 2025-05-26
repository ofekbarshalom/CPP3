//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <string>

#include "Screens.hpp"

using namespace sf;
using namespace std;


namespace coup {

    // Popup asking a Judge if they want to undo a bribe
    bool askJudgeUndoPopup(const Font& font, const string& judgeName) {
        RenderWindow popup(VideoMode(400, 200), "Judge's Choice");

        // Title text
        Text title("Judge " + judgeName + " - Undo bribe?", font, 20);
        title.setFillColor(Color::White);
        title.setPosition(30, 30);

        // "Undo" button
        RectangleShape undoBtn(Vector2f(200, 40));
        undoBtn.setPosition(100, 90);
        undoBtn.setFillColor(Color(60, 60, 60));

        // "Allow" button
        RectangleShape allowBtn(Vector2f(200, 40));
        allowBtn.setPosition(100, 140);
        allowBtn.setFillColor(Color(60, 60, 60));

        // Text for "Undo"
        Text undoTxt("Undo", font, 20);
        undoTxt.setFillColor(Color::White);
        undoTxt.setPosition(undoBtn.getPosition().x + 70, undoBtn.getPosition().y + 8);

        // Text for "Allow"
        Text allowTxt("Allow", font, 20);
        allowTxt.setFillColor(Color::White);
        allowTxt.setPosition(allowBtn.getPosition().x + 65, allowBtn.getPosition().y + 8);

        // Main event loop
        while (popup.isOpen()) {
            Event event;
            while (popup.pollEvent(event)) {

                // Window closed manually
                if (event.type == Event::Closed)
                    popup.close();
                
                // Mouse click detected
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f click(event.mouseButton.x, event.mouseButton.y);

                    // Clicked "Undo"
                    if (undoBtn.getGlobalBounds().contains(click)) {
                        popup.close();
                        return true;    //Judge blocks the bribe
                    }

                    // Clicked "Allow"
                    if (allowBtn.getGlobalBounds().contains(click)) {
                        popup.close();
                        return false;   //Judge lets the bribe stand
                    }
                }
            }

            // Draw everything
            popup.clear(Color(30, 30, 30));
            popup.draw(title);
            popup.draw(undoBtn); popup.draw(allowBtn);
            popup.draw(undoTxt); popup.draw(allowTxt);
            popup.display();
        }

        return false;   // Default return if window is closed another way
    }

}