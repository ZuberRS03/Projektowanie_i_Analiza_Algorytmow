#ifndef PROJEKT_3_MOVE_H
#define PROJEKT_3_MOVE_H

#include <SFML/Graphics.hpp>

struct Move {
    sf::Vector2i startPosition;
    std::vector<sf::Vector2i> endPositions;

    Move(const sf::Vector2i& start, const sf::Vector2i& end) {
        startPosition = start;
        endPositions.push_back(end);
    }

    void addEndPosition(const sf::Vector2i& end) {
        endPositions.push_back(end);
    }
//    sf::Vector2i startPosition;
//    sf::Vector2i endPosition;
//
//    Move(const sf::Vector2i& start, const sf::Vector2i& end)
//            : startPosition(start), endPosition(end) {}
};

#endif //PROJEKT_3_MOVE_H
