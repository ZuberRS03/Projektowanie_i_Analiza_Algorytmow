#ifndef PROJEKT_3_GAME_H
#define PROJEKT_3_GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Bot.h"

class Game {
public:
    Game();
    void run();

private:
    bool hasCaptureMoves() const;
    void handlePlayerInput();
    void update();
    void render();

    sf::RenderWindow window;
    Board board;
    Player* currentPlayer;
    Player* player1;
    Player* player2;

    PieceColor currentTurn;
    Field* selectedField;
    bool isPieceSelected;
    sf::Vector2i selectedPosition;
    bool mustContinueCapturing;

    sf::RectangleShape turnIndicator; // Dodaj wskaźnik tury
    sf::CircleShape captureIndicator; // Dodaj wskaźnik bicia
    void updateCaptureIndicator(); // Deklaracja funkcji aktualizującej wskaźnik bicia

    bool isBotGame; // Flaga gry z botem
};

#endif //PROJEKT_3_GAME_H
