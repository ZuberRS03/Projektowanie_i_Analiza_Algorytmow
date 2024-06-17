#ifndef PROJEKT_3_PLAYER_H
#define PROJEKT_3_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Move.h"

/*
 * Klasa abstrakcyjna Player reprezentująca gracza
 */
class Player {
public:
    // Konstruktor
    Player(PieceColor color);

    /*
     * Metoda virtualna zwracająca ruch gracza
     */
    virtual Move getMove(const Board& board) = 0;

protected:
    PieceColor color; // Kolor gracza
};

#endif //PROJEKT_3_PLAYER_H
