#ifndef PROJEKT_3_HUMANPLAYER_H
#define PROJEKT_3_HUMANPLAYER_H

#include "Player.h"

/*
 * Klasa reprezentująca gracza sterowanego przez człowieka
 * Klasa HumanPlayer dziedzicząca po klasie Player
 */
class HumanPlayer : public Player {
public:
    // Konstruktor
    HumanPlayer(PieceColor color);

    /*
     * Metoda zwracająca ruch gracza
     * @param board - referencja do planszy
     * @return Move - ruch gracza
     */
    Move getMove(const Board& board) override;
};

#endif //PROJEKT_3_HUMANPLAYER_H
