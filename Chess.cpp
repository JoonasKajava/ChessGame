#include <iostream>
#include <SFML/Graphics.hpp>
#include "UserInterface.h"

extern int minimaxCounter;

bool botWorking = false;


void handleBot(Station* station) {
    std::vector<Move> moves;
    station->giveAllLegalMoves(moves);
    std::cout << "Bot had " << moves.size() << " legal moves\n";

    sf::Clock clock;
    minimaxCounter = 0;
    MinMaxReturn botMovement = station->miniMax(MinMaxReturn(-INFINITY), MinMaxReturn(INFINITY), 4, station);
    std::cout << "Best move (" << (std::string)botMovement.bestMove << ") had evaluation of " << botMovement.evaluationValue << std::endl;
    station->movePiece(botMovement.bestMove);

    sf::Time elapsed = clock.getElapsedTime();

    std::cout << "Bot move took: " << elapsed.asSeconds() << "s and called minimax " << minimaxCounter << " times\n\n";
    botWorking = false;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1220, 900), "Nimi :D", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    Station station(true);
    UserInterface ui(&station);

    sf::Thread thread(&handleBot, &station);

    while (window.isOpen())
    {
        if (
            !station._isWhiteTurn && 
            !station.gameOver && !botWorking) {
            botWorking = true;
            thread.launch();
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
                
                if (event.mouseButton.button != sf::Mouse::Left || station.gameOver || !station._isWhiteTurn) continue;
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