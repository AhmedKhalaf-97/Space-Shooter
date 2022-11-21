#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RectangleShape rect;

    rect.setPosition(450, 450);
    rect.setSize(Vector2f(10,10));

    RenderWindow window(VideoMode(1920, 1080), "Space Shooter", Style::Default);

    while (window.isOpen())
    {
        window.clear();
        window.draw(rect);
        window.display();
    }
}
