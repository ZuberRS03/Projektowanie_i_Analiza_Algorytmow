#include "Board.h"
#include <iostream>

Board::Board() {
    if (!boardTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/board.jpg")) {
        std::cout << "Error loading board texture" << std::endl;
    }
    boardSprite.setTexture(boardTexture);
    fieldSideLength = 78.0f; // Ustalanie długości boku pola
}

void Board::initialize() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            grid[y][x].setPosition(sf::Vector2f(x * fieldSideLength, y * fieldSideLength));
            grid[y][x].setSideLength(fieldSideLength);
            if (y < 3 && (x + y) % 2 == 1) {
                grid[y][x].setState(FieldState::BLACK_PIECE);
                std::cout << "Field (" << x << ", " << y << ") set to BLACK_PIECE" << std::endl;
            } else if (y > 4 && (x + y) % 2 == 1) {
                grid[y][x].setState(FieldState::WHITE_PIECE);
                std::cout << "Field (" << x << ", " << y << ") set to WHITE_PIECE" << std::endl;
            } else {
                grid[y][x].setState(FieldState::EMPTY);
                std::cout << "Field (" << x << ", " << y << ") set to EMPTY" << std::endl;
            }
        }
    }
}

bool Board::isValidMove(const Move& move, bool isCapture) const {
    const Field& startField = *getFieldAt(move.startPosition);
    const Field& endField = *getFieldAt(move.endPosition);
    if (startField.getState() == FieldState::EMPTY || endField.getState() != FieldState::EMPTY) {
        return false;
    }

    sf::Vector2i direction = move.endPosition - move.startPosition;

    if (isCapture) {
        if (abs(direction.x) == 2 && abs(direction.y) == 2) {
            sf::Vector2i middlePos = move.startPosition + direction / 2;
            const Field& middleField = *getFieldAt(middlePos);
            if ((startField.getState() == FieldState::WHITE_PIECE && middleField.getState() == FieldState::BLACK_PIECE) ||
                (startField.getState() == FieldState::BLACK_PIECE && middleField.getState() == FieldState::WHITE_PIECE)) {
                return true;
            }
        }
    } else {
        if (abs(direction.x) == 1 && abs(direction.y) == 1) {
            return true;
        }
    }

    return false;
}

bool Board::canCapture(const sf::Vector2i& position) const {
    const Field& field = *getFieldAt(position);
    if (field.getState() == FieldState::EMPTY) {
        return false;
    }

    std::vector<sf::Vector2i> directions = {{2, 2}, {2, -2}, {-2, 2}, {-2, -2}};
    for (const sf::Vector2i& direction : directions) {
        sf::Vector2i endPosition = position + direction;
        if (isInsideBoard(endPosition)) {
            Move move(position, endPosition);
            if (isValidMove(move, true)) {
                return true;
            }
        }
    }
    return false;
}

void Board::makeMove(const Move& move) {
    Field* startField = getFieldAt(move.startPosition);
    Field* endField = getFieldAt(move.endPosition);
    if (startField && endField) {
        sf::Vector2i direction = move.endPosition - move.startPosition;
        if (abs(direction.x) == 2 && abs(direction.y) == 2) {
            sf::Vector2i capturedPosition = move.startPosition + sf::Vector2i(direction.x / 2, direction.y / 2);
            Field* capturedField = getFieldAt(capturedPosition);
            if (capturedField) {
                capturedField->setState(FieldState::EMPTY);
            }
        }
        endField->setState(startField->getState());
        startField->setState(FieldState::EMPTY);

        // Sprawdzanie promocji pionka na damkę
        if (endField->getState() == FieldState::WHITE_PIECE && move.endPosition.y == 0) {
            endField->setState(FieldState::WHITE_QUEEN);
        } else if (endField->getState() == FieldState::BLACK_PIECE && move.endPosition.y == 7) {
            endField->setState(FieldState::BLACK_QUEEN);
        }

        //std::cout << "Piece moved to position: (" << move.endPosition.x << ", " << move.endPosition.y << ")\n";

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

bool Board::hasCaptureMoves(PieceColor color) const {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if ((color == PieceColor::WHITE && grid[y][x].getState() == FieldState::WHITE_PIECE) ||
                (color == PieceColor::BLACK && grid[y][x].getState() == FieldState::BLACK_PIECE)) {
                if (canCapture(sf::Vector2i(x, y))) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::printBoard() const {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if ((x + y) % 2 == 1) {
                FieldState state = grid[y][x].getState();
                if (state == FieldState::WHITE_PIECE) {
                    std::cout << "| b ";
                } else if (state == FieldState::BLACK_PIECE) {
                    std::cout << "| c ";
                } else {
                    std::cout << "| 0 ";
                }
            } else {
                std::cout << "|   "; // Puste pola
            }
        }
        std::cout << "|" << std::endl;
    }
}