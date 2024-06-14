#include "Board.h"

Board::Board() {
    boardTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/board.jpg");
    boardSprite.setTexture(boardTexture);
    fieldSideLength = 691.0f / 8.0f; // Calculate side length of each field
}

void Board::initialize() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            grid[y][x].setPosition(sf::Vector2f(x * fieldSideLength, y * fieldSideLength));
            grid[y][x].setSideLength(fieldSideLength);
            if (y < 3 && (x + y) % 2 == 1) {
                grid[y][x].setState(FieldState::BLACK_PIECE);
            } else if (y > 4 && (x + y) % 2 == 1) {
                grid[y][x].setState(FieldState::WHITE_PIECE);
            } else {
                grid[y][x].setState(FieldState::EMPTY);
            }
        }
    }
}

bool Board::isValidMove(const Move& move) const {
    const Field& startField = *getFieldAt(move.startPosition);
    const Field& endField = *getFieldAt(move.endPosition);
    if (startField.getState() == FieldState::EMPTY || endField.getState() != FieldState::EMPTY) {
        return false;
    }

    // Logika sprawdzająca poprawność ruchu
    sf::Vector2i direction = move.endPosition - move.startPosition;
    if (abs(direction.x) == 1 && abs(direction.y) == 1) {
        // Ruch na sąsiednie pole
        return true;
    }
    return false; // Przykład, dostosuj logikę dla bicia itd.
}

void Board::makeMove(const Move& move) {
    Field* startField = getFieldAt(move.startPosition);
    Field* endField = getFieldAt(move.endPosition);
    if (startField && endField) {
        endField->setState(startField->getState());
        startField->setState(FieldState::EMPTY);
    }
}

void Board::draw(sf::RenderWindow& window) {
    window.draw(boardSprite);
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            grid[y][x].draw(window);
        }
    }
}

Field* Board::getFieldAt(const sf::Vector2i& position) const {
    if (isInsideBoard(position)) {
        return const_cast<Field*>(&grid[position.y][position.x]);
    }
    return nullptr;
}

Field* Board::getFieldContainingPoint(const sf::Vector2i& point) const {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (grid[y][x].contains(point)) {
                return const_cast<Field*>(&grid[y][x]);
            }
        }
    }
    return nullptr;
}

bool Board::isInsideBoard(const sf::Vector2i& position) const {
    return position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8;
}

float Board::getFieldSideLength() const {
    return fieldSideLength;
}