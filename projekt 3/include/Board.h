#ifndef PROJEKT_3_BOARD_H
#define PROJEKT_3_BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Field.h"
#include "Move.h"

class Board {
public:
    Board();
    void initialize();
    bool isValidMove(const Move& move, bool isCapturing = false) const;
    bool canCapture(const sf::Vector2i& position) const;
    void makeMove(const Move& move);
    void draw(sf::RenderWindow& window);
    Field* getFieldAt(const sf::Vector2i& position) const;
    Field* getFieldContainingPoint(const sf::Vector2i& point) const;
    float getFieldSideLength() const;
    bool hasCaptureMoves(PieceColor color) const;
    void setMustContinueCapturing(bool value);
    bool isInsideBoard(const sf::Vector2i& position) const;

    void printBoard() const;

    bool mustContinueCapturing;
private:
    Field grid[8][8];
    sf::Texture boardTexture;
    sf::Sprite boardSprite;
    float fieldSideLength;
};


#endif //PROJEKT_3_BOARD_H
