#ifndef PROJEKT_3_PIECE_H
#define PROJEKT_3_PIECE_H

#include <SFML/Graphics.hpp>

enum class PieceColor { BLACK, WHITE };

class Piece {
public:
    Piece(PieceColor color, sf::Vector2f position);
    bool canMove(const sf::Vector2f& newPosition) const;
    bool isKing() const;
    void promote();
    void draw(sf::RenderWindow& window);

private:
    PieceColor color;
    bool king;
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif //PROJEKT_3_PIECE_H
