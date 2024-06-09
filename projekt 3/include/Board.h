#ifndef PROJEKT_3_BOARD_H
#define PROJEKT_3_BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Piece.h"
#include "Move.h"

class Board {
public:
    Board();
    void initialize();
    bool isValidMove(const Move& move) const;
    void makeMove(const Move& move);
    std::vector<Move> getPossibleMoves(PieceColor color) const;
    void draw(sf::RenderWindow& window);

private:
    std::vector<std::vector<Piece*>> grid;
    sf::Texture boardTexture;
    sf::Sprite boardSprite;
};


#endif //PROJEKT_3_BOARD_H
