#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(PieceColor color) : Player(color) {}

Move HumanPlayer::getMove(const Board& board) {
    // Implementacja pobierania ruchu od gracza ludzkiego
    // Na przykład, można zwrócić domyślny ruch na razie
    return Move(sf::Vector2i(0, 0), sf::Vector2i(1, 1));
}