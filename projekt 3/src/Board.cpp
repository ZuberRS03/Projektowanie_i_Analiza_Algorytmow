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
        if (startField.getState() == FieldState::WHITE_QUEEN || startField.getState() == FieldState::BLACK_QUEEN) {
            if (abs(direction.x) == abs(direction.y)) {
                int stepX = direction.x / abs(direction.x);
                int stepY = direction.y / abs(direction.y);
                bool captured = false;
                sf::Vector2i checkPos = move.startPosition + sf::Vector2i(stepX, stepY);
                while (checkPos != move.endPosition) {
                    Field* checkField = getFieldAt(checkPos);
                    if (checkField->getState() != FieldState::EMPTY) {
                        if ((checkField->getState() == FieldState::WHITE_PIECE || checkField->getState() == FieldState::WHITE_QUEEN) &&
                            (startField.getState() == FieldState::BLACK_PIECE || startField.getState() == FieldState::BLACK_QUEEN)) {
                            if (captured) {
                                return false; // Nie można zbić więcej niż jednego pionka na raz
                            }
                            captured = true;
                        } else if ((checkField->getState() == FieldState::BLACK_PIECE || checkField->getState() == FieldState::BLACK_QUEEN) &&
                                   (startField.getState() == FieldState::WHITE_PIECE || startField.getState() == FieldState::WHITE_QUEEN)) {
                            if (captured) {
                                return false; // Nie można zbić więcej niż jednego pionka na raz
                            }
                            captured = true;
                        } else {
                            return false; // Nie można zbić własnego pionka
                        }
                    }
                    checkPos += sf::Vector2i(stepX, stepY);
                }
                return captured;
            }
        } else if (abs(direction.x) == 2 && abs(direction.y) == 2) {
            sf::Vector2i middlePos = move.startPosition + direction / 2;
            const Field& middleField = *getFieldAt(middlePos);
            if ((startField.getState() == FieldState::WHITE_PIECE && (middleField.getState() == FieldState::BLACK_PIECE || middleField.getState() == FieldState::BLACK_QUEEN)) ||
                (startField.getState() == FieldState::BLACK_PIECE && (middleField.getState() == FieldState::WHITE_PIECE || middleField.getState() == FieldState::WHITE_QUEEN))) {
                return true;
            }
        }
    } else {
        if (startField.getState() == FieldState::WHITE_PIECE && direction.y == -1 && abs(direction.x) == 1) {
            return true;
        } else if (startField.getState() == FieldState::BLACK_PIECE && direction.y == 1 && abs(direction.x) == 1) {
            return true;
        } else if ((startField.getState() == FieldState::WHITE_QUEEN || startField.getState() == FieldState::BLACK_QUEEN) && abs(direction.x) == abs(direction.y)) {
            for (int i = 1; i < abs(direction.x); ++i) {
                sf::Vector2i intermediatePos = move.startPosition + sf::Vector2i(i * (direction.x / abs(direction.x)), i * (direction.y / abs(direction.y)));
                if (getFieldAt(intermediatePos)->getState() != FieldState::EMPTY) {
                    return false;
                }
            }
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

    if (field.getState() == FieldState::WHITE_QUEEN || field.getState() == FieldState::BLACK_QUEEN) {
        directions = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (const sf::Vector2i& direction : directions) {
            sf::Vector2i checkPos = position + direction;
            bool canCapture = false;
            while (isInsideBoard(checkPos)) {
                const Field& checkField = *getFieldAt(checkPos);
                if (checkField.getState() != FieldState::EMPTY && checkField.getState() != field.getState() &&
                    ((field.getState() == FieldState::WHITE_QUEEN && (checkField.getState() == FieldState::BLACK_PIECE || checkField.getState() == FieldState::BLACK_QUEEN)) ||
                     (field.getState() == FieldState::BLACK_QUEEN && (checkField.getState() == FieldState::WHITE_PIECE || checkField.getState() == FieldState::WHITE_QUEEN)))) {
                    sf::Vector2i nextPos = checkPos + direction;
                    if (isInsideBoard(nextPos) && getFieldAt(nextPos)->getState() == FieldState::EMPTY) {
                        canCapture = true;
                        break;
                    }
                }
                checkPos += direction;
            }
            if (canCapture) return true;
        }
    }

    return false;
}

void Board::makeMove(const Move& move) {
    Field* startField = getFieldAt(move.startPosition);
    Field* endField = getFieldAt(move.endPosition);
    if (startField && endField) {
        sf::Vector2i direction = move.endPosition - move.startPosition;
        bool captured = false;

        if ((startField->getState() == FieldState::WHITE_QUEEN || startField->getState() == FieldState::BLACK_QUEEN) && abs(direction.x) == abs(direction.y)) {
            int stepX = direction.x / abs(direction.x);
            int stepY = direction.y / abs(direction.y);
            sf::Vector2i checkPos = move.startPosition + sf::Vector2i(stepX, stepY);
            while (checkPos != move.endPosition) {
                Field* checkField = getFieldAt(checkPos);
                if (checkField->getState() != FieldState::EMPTY) {
                    if (checkField->getState() != startField->getState() && !captured) {
                        checkField->setState(FieldState::EMPTY);
                        captured = true;
                    } else {
                        return; // Nie można zbić więcej niż jednego pionka na raz
                    }
                }
                checkPos += sf::Vector2i(stepX, stepY);
            }
        } else if (abs(direction.x) == 2 && abs(direction.y) == 2) {
            sf::Vector2i capturedPosition = move.startPosition + sf::Vector2i(direction.x / 2, direction.y / 2);
            Field* capturedField = getFieldAt(capturedPosition);
            if (capturedField && capturedField->getState() != startField->getState()) {
                capturedField->setState(FieldState::EMPTY);
                captured = true;
            } else {
                return; // Nie można zbić własnego pionka
            }
        }

        endField->setState(startField->getState());
        startField->setState(FieldState::EMPTY);
        bool promotion = false;

        if (endField->getState() == FieldState::WHITE_PIECE && move.endPosition.y == 0) {
            endField->setState(FieldState::WHITE_QUEEN);
            promotion = true;
        } else if (endField->getState() == FieldState::BLACK_PIECE && move.endPosition.y == 7) {
            endField->setState(FieldState::BLACK_QUEEN);
            promotion = true;
        }

        if (!promotion && captured && canCapture(move.endPosition)) {
            mustContinueCapturing = true;
        } else {
            mustContinueCapturing = false;
        }
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
            FieldState state = grid[y][x].getState();
            if ((color == PieceColor::WHITE && (state == FieldState::WHITE_PIECE || state == FieldState::WHITE_QUEEN)) ||
                (color == PieceColor::BLACK && (state == FieldState::BLACK_PIECE || state == FieldState::BLACK_QUEEN))) {
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
                } else if (state == FieldState::WHITE_QUEEN) {
                    std::cout << "| Q ";
                } else if (state == FieldState::BLACK_QUEEN) {
                    std::cout << "| k ";
                } else {
                    std::cout << "| 0 ";
                }
            } else {
                std::cout << "|   "; // Puste pola
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout <<"---------------------------------------------------"<< std::endl;
}

void Board::setMustContinueCapturing(bool value) {
    mustContinueCapturing = value;
}