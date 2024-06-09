#ifndef PROJEKT_3_GAME_H
#define PROJEKT_3_GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
    void handlePlayerInput();
    void update();
    void render();

    sf::RenderWindow window;
    Board board;
    Player* currentPlayer;
    Player* player1;
    Player* player2;
};

#endif //PROJEKT_3_GAME_H
