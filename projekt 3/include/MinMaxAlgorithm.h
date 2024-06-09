#ifndef PROJEKT_3_MINMAXALGORITHM_H
#define PROJEKT_3_MINMAXALGORITHM_H

#include "Board.h"
#include "Move.h"

class MinMaxAlgorithm {
public:
    Move calculateBestMove(const Board& board, int depth);
    int evaluateBoard(const Board& board);
    int minMax(Board& board, int depth, bool isMaximizingPlayer);

private:
    // Funkcje pomocnicze
};

#endif //PROJEKT_3_MINMAXALGORITHM_H
