#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

#include "PlayerController.h"

using namespace sf;
using namespace std;

int main()
{
    Vector2f screenResolution;
    screenResolution.x = VideoMode::getDesktopMode().width;
    screenResolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y),
        "Space Shooter", Style::Fullscreen);

    View mainView(sf::FloatRect(0, 0, screenResolution.x, screenResolution.y));
    View hudView(sf::FloatRect(0, 0, screenResolution.x, screenResolution.y));

    PlayerController player(Vector2f(screenResolution.x/2, screenResolution.y/2));

    Text hud;
    Font font;
    font.loadFromFile("fonts/Audiowide-Regular.ttf");
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    Clock clock;

    while (window.isOpen())
    {
        Event event;
        Time dt = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        stringstream ss;
        ss << "Score:" << 100 << " Lives:" << 3;
        hud.setString(ss.str());

        player.Move();
        player.UpdatePosition(dt, screenResolution);

        window.clear();
        
        window.setView(mainView);
        window.draw(player.GetShape());

        window.setView(hudView);
        window.draw(hud);

        window.display();
    }
}
