//ofekbarshalom@gmail.com

#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace coup {

    // Creates a centered title text for the given window
    Text createTitle(const string& text, Font& font, RenderWindow& window, unsigned int size = 48);

    // Creates a labeled button with text and positioning
    void createButton(const string& label, Font& font, RectangleShape& button, Text& buttonText, Vector2f size, Vector2f position);

    // Loads and scales a background image to fit the window
    Sprite loadAndScaleBackground(const string& path, RenderWindow& window);
}

#endif // GUI_HPP
