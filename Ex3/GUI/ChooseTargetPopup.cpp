#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Screens.hpp"

using namespace sf;
using namespace std;

namespace coup {

    Player* chooseTargetPopup(const Font& font, const vector<Player*>& targets) {
        RenderWindow popup(VideoMode(400, 300), "Choose Target");

        while (popup.isOpen()) {
            Event event;
            while (popup.pollEvent(event)) {
                if (event.type == Event::Closed)
                    popup.close();

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2f click(event.mouseButton.x, event.mouseButton.y);
                    for (size_t t = 0; t < targets.size(); ++t) {
                        FloatRect area(100, 60 + t * 50, 200, 40);
                        if (area.contains(click)) {
                            popup.close();
                            return targets[t];
                        }
                    }
                }
            }

            popup.clear(Color(30, 30, 30));
            Text title("Choose Target", font, 24);
            title.setPosition(120, 20);
            popup.draw(title);

            for (size_t t = 0; t < targets.size(); ++t) {
                RectangleShape box(Vector2f(200, 40));
                box.setPosition(100, 60 + t * 50);
                box.setFillColor(Color(60, 60, 60));

                Text txt(targets[t]->getName(), font, 20);
                txt.setPosition(110, 65 + t * 50);
                popup.draw(box);
                popup.draw(txt);
            }

            popup.display();
        }

        return nullptr;
    }
}