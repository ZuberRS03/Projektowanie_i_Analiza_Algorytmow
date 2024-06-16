#include "Bot.h"

Bot::Bot(PieceColor color) : Player(color), minMaxAlgorithm() {
    // Inicjalizacja bota
}

Move Bot::getMove(const Board& board) {
    Move bestMove = minMaxAlgorithm.calculateBestMove(board, 3); // Przykładowa głębokość 3
    return bestMove;
}
