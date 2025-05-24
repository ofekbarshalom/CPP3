//ofekbarshalom@gmail.com

#include "GUI.hpp"
#include <stdexcept>

using namespace sf;
using namespace std;

namespace coup {

    Text createTitle(const string& text, Font& font, RenderWindow& window, unsigned int size) {
        Text title(text, font, size);
        FloatRect bounds = title.getLocalBounds();
        title.setOrigin(bounds.width / 2, bounds.height / 2);
        title.setPosition(window.getSize().x / 2.f, 100);
        title.setFillColor(Color::White);
        return title;
    }

    void createButton(const string& label, Font& font, RectangleShape& button, Text& buttonText,
                      Vector2f size, Vector2f position) {
        button.setSize(size);
        button.setPosition(position);
        button.setFillColor(Color(50, 50, 50));

        buttonText.setFont(font);
        buttonText.setString(label);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(Color::White);

        FloatRect bounds = buttonText.getLocalBounds();
        buttonText.setOrigin(bounds.width / 2, bounds.height / 2 + bounds.top);
        buttonText.setPosition(
            position.x + size.x / 2,
            position.y + size.y / 2
        );
    }

    Sprite loadAndScaleBackground(const string& path, RenderWindow& window) {
        static Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile(path)) {
            throw runtime_error("Failed to load background image: " + path);
        }

        Sprite background(backgroundTexture);
        background.setScale(
            window.getSize().x / background.getLocalBounds().width,
            window.getSize().y / background.getLocalBounds().height
        );
        return background;
    }

}
