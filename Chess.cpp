#include <SFML/Graphics.hpp>
#include "UserInterface.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1220, 900), "Chessbot", sf::Style::Titlebar | sf::Style::Close);
    Station station;
    UserInterface ui(&station);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button != sf::Mouse::Left) continue;
                ui.checkPieceClick(&window);
                break;
            default:
                break;
            }
        }

        window.clear(sf::Color::White);
        ui.drawBoard(&window);
        ui.drawStatus(&window);
        window.display();
    }

    return 0;
}