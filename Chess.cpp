#include <iostream>
#include <SFML/Graphics.hpp>
#include "UserInterface.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1220, 900), "Nimi :D", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    Station station(true);
    UserInterface ui(&station);

    

    while (window.isOpen())
    {
        if (
            !station._isWhiteTurn && 
            !station.gameOver) {

            std::vector<Move> moves;
            station.giveAllLegalMoves(moves);
            std::cout << "Bot had " << moves.size() << " legal moves\n";

            sf::Clock clock;

            MinMaxReturn botMovement = station.miniMax(3, &station);
            station.movePiece(botMovement.bestMove);

            sf::Time elapsed = clock.getElapsedTime();

            std::cout << "Bot move took: " << elapsed.asSeconds() << "s\n\n";

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
                
                if (event.mouseButton.button != sf::Mouse::Left || station.gameOver) continue;
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