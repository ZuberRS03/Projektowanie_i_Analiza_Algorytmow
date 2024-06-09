#ifndef PROJEKT_3_PIECE_H
#define PROJEKT_3_PIECE_H

#include <SFML/Graphics.hpp>

enum class PieceColor { BLACK, WHITE };

class Piece {
public:

    Piece(PieceColor color, const sf::Vector2i &position);

    bool canMove(const sf::Vector2i& newPosition) const;
    bool isKing() const;
    void promote();
    void draw(sf::RenderWindow& window);

    PieceColor getColor() const;
    sf::Vector2i getPosition() const;
    void setPosition(const sf::Vector2i& position);

private:
    PieceColor color;
    bool king;
    sf::Vector2i position;
    sf::Sprite sprite;
    sf::Texture texture;


};

#endif //PROJEKT_3_PIECE_H
