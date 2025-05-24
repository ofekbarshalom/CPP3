//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <string>

#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    bool askGeneralUndoPopup(const Font& font, const string& generalName) {
            RenderWindow popup(VideoMode(400, 200), "General's Choice");

            Text title("General " + generalName + " - Undo Coup for 5 coins?", font, 20);
            title.setFillColor(Color::White);
            title.setPosition(30, 30);

            RectangleShape undoBtn(Vector2f(200, 40));
            undoBtn.setPosition(100, 90);
            undoBtn.setFillColor(Color(60, 60, 60));

            RectangleShape allowBtn(Vector2f(200, 40));
            allowBtn.setPosition(100, 140);
            allowBtn.setFillColor(Color(60, 60, 60));

            Text undoTxt("Undo", font, 20);
            undoTxt.setFillColor(Color::White);
            undoTxt.setPosition(undoBtn.getPosition().x + 70, undoBtn.getPosition().y + 8);

            Text allowTxt("Allow", font, 20);
            allowTxt.setFillColor(Color::White);
            allowTxt.setPosition(allowBtn.getPosition().x + 65, allowBtn.getPosition().y + 8);

            while (popup.isOpen()) {
                Event event;
                while (popup.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        popup.close();

                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f click(event.mouseButton.x, event.mouseButton.y);
                        if (undoBtn.getGlobalBounds().contains(click)) {
                            popup.close();
                            return true;
                        }
                        if (allowBtn.getGlobalBounds().contains(click)) {
                            popup.close();
                            return false;
                        }
                    }
                }

                popup.clear(Color(30, 30, 30));
                popup.draw(title);
                popup.draw(undoBtn); popup.draw(allowBtn);
                popup.draw(undoTxt); popup.draw(allowTxt);
                popup.display();
            }

            return false;
        }

}