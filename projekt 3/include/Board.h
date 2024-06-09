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

    Piece* getPieceAt(const sf::Vector2i& position) const;
    sf::Vector2i getGridPositionFromPixel(int x, int y) const;

private:
    std::vector<std::vector<Piece*>> grid;
    sf::Texture boardTexture;
    sf::Sprite boardSprite;

    bool isInsideBoard(const sf::Vector2i& position) const;
};


#endif //PROJEKT_3_BOARD_H
