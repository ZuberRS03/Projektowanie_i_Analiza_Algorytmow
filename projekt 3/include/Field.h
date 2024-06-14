#ifndef PROJEKT_3_FIELD_H
#define PROJEKT_3_FIELD_H

#include <SFML/Graphics.hpp>

enum class PieceColor {
    WHITE,
    BLACK
};

enum class FieldState {
    EMPTY,
    WHITE_PIECE,
    BLACK_PIECE
};

class Field {
public:
    Field();
    FieldState getState() const;
    void setState(FieldState state);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setSideLength(float length);
    float getSideLength() const;
    bool contains(const sf::Vector2i& point) const;
    void draw(sf::RenderWindow& window);

private:
    FieldState state;
    sf::Vector2f position;
    float sideLength;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //PROJEKT_3_FIELD_H
