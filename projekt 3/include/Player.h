#ifndef PROJEKT_3_PLAYER_H
#define PROJEKT_3_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Move.h"

class Player {
public:
    Player(PieceColor color);
    virtual Move getMove(const Board& board) = 0;

protected:
    PieceColor color;
};

#endif //PROJEKT_3_PLAYER_H
