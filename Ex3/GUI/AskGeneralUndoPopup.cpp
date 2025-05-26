//ofekbarshalom@gmail.com

#include <SFML/Graphics.hpp>
#include <string>

#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    // Popup asking a General if they want to undo a coup for 5 coins
    bool askGeneralUndoPopup(const Font& font, const string& generalName) {
            RenderWindow popup(VideoMode(400, 200), "General's Choice");

            // Title text
            Text title("General " + generalName + " - Undo Coup for 5 coins?", font, 20);
            title.setFillColor(Color::White);
            title.setPosition(30, 30);

            // Buttons
            RectangleShape undoBtn(Vector2f(200, 40));  // "Undo" button
            undoBtn.setPosition(100, 90);
            undoBtn.setFillColor(Color(60, 60, 60));

            RectangleShape allowBtn(Vector2f(200, 40)); // "Allow" button
            allowBtn.setPosition(100, 140);
            allowBtn.setFillColor(Color(60, 60, 60));

            // Button labels
            Text undoTxt("Undo", font, 20);
            undoTxt.setFillColor(Color::White);
            undoTxt.setPosition(undoBtn.getPosition().x + 70, undoBtn.getPosition().y + 8);

            Text allowTxt("Allow", font, 20);
            allowTxt.setFillColor(Color::White);
            allowTxt.setPosition(allowBtn.getPosition().x + 65, allowBtn.getPosition().y + 8);

            // Main event loop
            while (popup.isOpen()) {
                Event event;

                // Handle window events (close, click and more)
                while (popup.pollEvent(event)) {

                    // User closed the popup manually
                    if (event.type == Event::Closed)
                        popup.close();  
                    
                    // User clicked with left mouse button
                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f click(event.mouseButton.x, event.mouseButton.y);

                        // If click was inside "Undo" button
                        if (undoBtn.getGlobalBounds().contains(click)) {
                            popup.close();
                            return true;    // General chose to undo the coup
                        }

                        // If click was inside "Allow" button
                        if (allowBtn.getGlobalBounds().contains(click)) {
                            popup.close();
                            return false;   // General chose not to undo
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