#include "Field.h"

Field::Field() : state(FieldState::EMPTY), sideLength(0) {}

FieldState Field::getState() const {
    return state;
}

void Field::setState(FieldState state) {
    this->state = state;
    switch (state) {
        case FieldState::WHITE_PIECE:
            texture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/white.png");
            sprite.setTexture(texture);
            sprite.setScale(sideLength / 200.0f, sideLength / 200.0f); // Adjust scale for piece size
            break;
        case FieldState::BLACK_PIECE:
            texture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/black.png");
            sprite.setTexture(texture);
            sprite.setScale(sideLength / 200.0f, sideLength / 200.0f); // Adjust scale for piece size
            break;
        case FieldState::EMPTY:
            sprite.setTexture(texture);
            break;
    }
}

void Field::setPosition(const sf::Vector2f& position) {
    this->position = position;
    sprite.setPosition(position);
}

sf::Vector2f Field::getPosition() const {
    return position;
}

void Field::setSideLength(float length) {
    this->sideLength = length;
}

float Field::getSideLength() const {
    return sideLength;
}

bool Field::contains(const sf::Vector2i& point) const {
    return point.x >= position.x && point.x < position.x + sideLength &&
           point.y >= position.y && point.y < position.y + sideLength;
}

void Field::draw(sf::RenderWindow& window) {
    if (state != FieldState::EMPTY) {
        window.draw(sprite);
    }
}

