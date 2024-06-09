#ifndef PROJEKT_3_BOT_H
#define PROJEKT_3_BOT_H

#include "Player.h"
#include "MinMaxAlgorithm.h"
#include "Move.h"

class Bot : public Player {
public:
    Bot(PieceColor color);
    Move getMove(const Board& board) override;

private:
    MinMaxAlgorithm minMaxAlgorithm;
};

#endif //PROJEKT_3_BOT_H
