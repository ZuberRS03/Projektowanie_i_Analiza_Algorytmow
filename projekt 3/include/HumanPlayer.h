#ifndef PROJEKT_3_HUMANPLAYER_H
#define PROJEKT_3_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(PieceColor color);
    Move getMove(const Board& board) override;
};

#endif //PROJEKT_3_HUMANPLAYER_H
