#ifndef PROJEKT_3_MINMAXALGORITHM_H
#define PROJEKT_3_MINMAXALGORITHM_H

#include "Board.h"
#include "Move.h"
#include <vector>
#include <iostream>

class MinMaxAlgorithm {
public:
    Move calculateBestMove(const Board& board, int depth);
    int evaluateBoard(const Board& board);
    int minMax(Board& board, int depth, bool isMaximizingPlayer);

private:
    std::vector<Move> getAllPossibleMoves(const Board& board, PieceColor color);
    std::vector<sf::Vector2i> getPossibleEndPositions(const Board& board, const sf::Vector2i& startPos, bool isCapturing);
};

#endif //PROJEKT_3_MINMAXALGORITHM_H
