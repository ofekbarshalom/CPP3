//ofekbarshalom@gmail.com

#include "GUI.hpp"
#include <stdexcept>

using namespace sf;
using namespace std;

namespace coup {

    // Creates a centered title Text object at the top of the window
    Text createTitle(const string& text, Font& font, RenderWindow& window, unsigned int size) {
        Text title(text, font, size);
        FloatRect bounds = title.getLocalBounds();

        // Center the text
        title.setOrigin(bounds.width / 2, bounds.height / 2);
        title.setPosition(window.getSize().x / 2.f, 100);
        title.setFillColor(Color::White);

        return title;
    }

    // Creates a button and its label text, with size and position
    void createButton(const string& label, Font& font, RectangleShape& button, Text& buttonText, Vector2f size, Vector2f position) {
        // Set up button shape
        button.setSize(size);
        button.setPosition(position);
        button.setFillColor(Color(50, 50, 50));
        
        // Set up button text
        buttonText.setFont(font);
        buttonText.setString(label);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(Color::White);

        // Center text within button
        FloatRect bounds = buttonText.getLocalBounds();
        buttonText.setOrigin(bounds.width / 2, bounds.height / 2 + bounds.top);
        buttonText.setPosition(
            position.x + size.x / 2,
            position.y + size.y / 2
        );
    }

    // Loads and scales a background image to fill the window
    Sprite loadAndScaleBackground(const string& path, RenderWindow& window) {
        static Texture backgroundTexture;

        // Load image from file
        if (!backgroundTexture.loadFromFile(path)) {
            throw runtime_error("Failed to load background image: " + path);
        }

        // Create sprite and scale it to fit window size
        Sprite background(backgroundTexture);
        background.setScale(
            window.getSize().x / background.getLocalBounds().width,
            window.getSize().y / background.getLocalBounds().height
        );
        
        return background;
    }

}
