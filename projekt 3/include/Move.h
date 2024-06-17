#ifndef PROJEKT_3_MOVE_H
#define PROJEKT_3_MOVE_H

#include <SFML/Graphics.hpp>

/*
 * Struktura reprezentująca ruch
 * Zawiera pozycję początkową oraz końcową
 */
struct Move {
    sf::Vector2i startPosition; // pozycja początkowa
    std::vector<sf::Vector2i> endPositions; // pozycje końcowe

    // konstruktor
    Move(const sf::Vector2i& start, const sf::Vector2i& end) {
        startPosition = start;
        endPositions.push_back(end);
    }

    // dodaje pozycję końcową
    void addEndPosition(const sf::Vector2i& end) {
        endPositions.push_back(end);
    }
};

#endif //PROJEKT_3_MOVE_H
