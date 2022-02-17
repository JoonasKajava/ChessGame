#include <iostream>
#include <SFML/Graphics.hpp>
#include "UserInterface.h"
#include <chrono>


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::seconds;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1220, 900), "Nimi :D", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    Station station(true);
    UserInterface ui(&station);

    while (window.isOpen())
    {
        if (!station._isWhiteTurn) {
            auto t1 = high_resolution_clock::now();

            MinMaxReturn botMovement = station.miniMax(2, &station);
            station.movePiece(botMovement.bestMove);

            auto t2 = high_resolution_clock::now();

            auto secs = duration_cast<seconds>(t2 - t1);


            std::cout << "Bot move took: " << secs.count() << "s\n";

            continue;
        }

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
                ui.checkPromotionClick(&window);
                break;
            default:
                break;
            }
        }

        window.clear(sf::Color::White);
        ui.drawStatus(&window);
        ui.drawBoard(&window);
        window.display();
    }

    return 0;
}