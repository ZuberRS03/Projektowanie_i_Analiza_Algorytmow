#include "Field.h"
#include <iostream>


// Inicjalizacja statycznych zmiennych dla tekstur
sf::Texture Field::whitePieceTexture;
sf::Texture Field::blackPieceTexture;
sf::Texture Field::whiteQueenTexture;
sf::Texture Field::blackQueenTexture;

Field::Field() : state(FieldState::EMPTY), sideLength(0) {
    // Inicjalizacja tekstur
    if (whitePieceTexture.getSize().x == 0) { // Jeśli tekstura nie została wczytana
        if (!whitePieceTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/white.png")) {
            std::cout << "Error loading white piece texture" << std::endl;
        }
    }
    if (blackPieceTexture.getSize().x == 0) {  // Jeśli tekstura nie została wczytana
        if (!blackPieceTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/black.png")) {
            std::cout << "Error loading black piece texture" << std::endl;
        }
    }
    if (whiteQueenTexture.getSize().x == 0) {  // Jeśli tekstura nie została wczytana
        if (!whiteQueenTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/Quen_White_v2.png")) {
            std::cout << "Error loading white queen texture" << std::endl;
        }
    }
    if (blackQueenTexture.getSize().x == 0) {  // Jeśli tekstura nie została wczytana
        if (!blackQueenTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/Quen_Black_v2.png")) {
            std::cout << "Error loading black queen texture" << std::endl;
        }
    }

}

FieldState Field::getState() const {
    return state; // Zwracanie stanu pola
}

void Field::setState(FieldState state) {
    this->state = state; // Ustawianie stanu pola
    switch (state) { // Ustawianie tekstury w zależności od stanu
        case FieldState::WHITE_PIECE: // Jeśli biały pionek
            sprite.setTexture(whitePieceTexture); // Ustawienie tekstury białego pionka
            sprite.setScale(sideLength / 250.0f, sideLength / 250.0f); // Ustawienie skali dla rozmiaru pionka
            break; // Zakończenie instrukcji
        case FieldState::BLACK_PIECE: // Jeśli czarny pionek
            sprite.setTexture(blackPieceTexture); // Ustawienie tekstury czarnego pionka
            sprite.setScale(sideLength / 250.0f, sideLength / 250.0f); // Ustawienie skali dla rozmiaru pionka
            break; // Zakończenie instrukcji
        case FieldState::WHITE_QUEEN: // Jeśli biała dama
            sprite.setTexture(whiteQueenTexture); // Ustawienie tekstury białej damy
            sprite.setScale(sideLength / 250.0f, sideLength / 250.0f); // Ustawienie skali dla rozmiaru pionka
            break; // Zakończenie instrukcji
        case FieldState::BLACK_QUEEN: // Jeśli czarna dama
            sprite.setTexture(blackQueenTexture); // Ustawienie tekstury czarnej damy
            sprite.setScale(sideLength / 250.0f, sideLength / 250.0f); // Ustawienie skali dla rozmiaru pionka
            break; // Zakończenie instrukcji
        case FieldState::EMPTY: // Jeśli pole jest puste
            sprite.setTexture(whitePieceTexture); // Ustawienie tekstury białego pionka (domyślnie puste pole)
            break;
    }
}

void Field::setPosition(const sf::Vector2f& position) {
    this->position = position; // Ustawienie pozycji pola
    sprite.setPosition(position.x + 40, position.y + 40); // Uwzględnianie marginesów

}

sf::Vector2f Field::getPosition() const {
    return position; // Zwracanie pozycji pola
}

void Field::setSideLength(float length) {
    this->sideLength = length; // Ustawienie długości boku pola
}

float Field::getSideLength() const {
    return sideLength; // Zwracanie długości boku pola
}

bool Field::contains(const sf::Vector2i& point) const {
    return point.x >= position.x + 40 && point.x < position.x + 40 + sideLength &&
           point.y >= position.y + 40 && point.y < position.y + 40 + sideLength; // Uwzględnianie marginesów

}

void Field::draw(sf::RenderWindow& window) {
    if (state != FieldState::EMPTY) { // Jeśli pole nie jest puste
        window.draw(sprite); // Rysowanie pionka
    } else {
        //std::cout << "Field at position: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ") is empty" << std::endl;
    }
}

