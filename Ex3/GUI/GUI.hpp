#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace coup {

    Text createTitle(const string& text, Font& font, RenderWindow& window, unsigned int size = 48);
    void createButton(const string& label, Font& font, RectangleShape& button, Text& buttonText, Vector2f size, Vector2f position);
    Sprite loadAndScaleBackground(const string& path, RenderWindow& window);
}

#endif // GUI_HPP
