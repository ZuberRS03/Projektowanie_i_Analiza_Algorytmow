#include "Field.h"
#include <iostream>


// Inicjalizacja statycznych zmiennych
sf::Texture Field::whitePieceTexture;
sf::Texture Field::blackPieceTexture;

Field::Field() : state(FieldState::EMPTY), sideLength(0) {
    // Load textures only once
    if (whitePieceTexture.getSize().x == 0) { // Check if texture is not loaded
        if (!whitePieceTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/white.png")) {
            std::cout << "Error loading white piece texture" << std::endl;
        }
    }
    if (blackPieceTexture.getSize().x == 0) { // Check if texture is not loaded
        if (!blackPieceTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/black.png")) {
            std::cout << "Error loading black piece texture" << std::endl;
        }
    }

}

FieldState Field::getState() const {
    return state;
}

void Field::setState(FieldState state) {
    this->state = state;
    switch (state) {
        case FieldState::WHITE_PIECE:
            sprite.setTexture(whitePieceTexture);
            sprite.setScale(sideLength / 250.0f, sideLength / 250.0f); // Adjust scale for piece size
            break;
        case FieldState::BLACK_PIECE:
            sprite.setTexture(blackPieceTexture);
            sprite.setScale(sideLength / 250.0f, sideLength / 250.0f); // Adjust scale for piece size
            break;
        case FieldState::EMPTY:
            sprite.setTexture(whitePieceTexture); // Use white texture as default
            break;
    }
    std::cout << "Field initialized with state: " << (state == FieldState::WHITE_PIECE ? "WHITE_PIECE" : state == FieldState::BLACK_PIECE ? "BLACK_PIECE" : "EMPTY") << " at position: (" << position.x << ", " << position.y << ")" << std::endl;
}

void Field::setPosition(const sf::Vector2f& position) {
    this->position = position;
    sprite.setPosition(position.x + 40, position.y + 40); // Uwzględnianie marginesów
    std::cout << "Set position for sprite: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
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
    return point.x >= position.x + 40 && point.x < position.x + 40 + sideLength &&
           point.y >= position.y + 40 && point.y < position.y + 40 + sideLength; // Uwzględnianie marginesów
}

void Field::draw(sf::RenderWindow& window) {
    if (state != FieldState::EMPTY) {
        //std::cout << "Drawing piece at position: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ") with state: " << (state == FieldState::WHITE_PIECE ? "WHITE_PIECE" : "BLACK_PIECE") << std::endl;
        window.draw(sprite);
    } else {
        //std::cout << "Field at position: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ") is empty" << std::endl;
    }
}

