#include "Board.h"
#include <iostream>

Board::Board() {
    if (!boardTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/board.jpg")) {  // Wczytywanie tekstury planszy
        std::cout << "Error loading board texture" << std::endl; // Wyświetlenie błędu
    }
    boardSprite.setTexture(boardTexture); // Ustawienie tekstury planszy
    fieldSideLength = 78.0f; // Ustalanie długości boku pola
}

void Board::initialize() {
    for (int y = 0; y < 8; ++y) { // Pętla po rzędach
        for (int x = 0; x < 8; ++x) { // Pętla po kolumnach
            grid[y][x].setPosition(sf::Vector2f(x * fieldSideLength, y * fieldSideLength)); // Ustawienie pozycji pola
            grid[y][x].setSideLength(fieldSideLength); // Ustawienie długości boku pola
            if (y < 3 && (x + y) % 2 == 1) { // Jeśli pole jest w pierwszych trzech rzędach i jest czarne
                grid[y][x].setState(FieldState::BLACK_PIECE); // Ustawienie stanu pola na czarny pionek
                std::cout << "Field (" << x << ", " << y << ") set to BLACK_PIECE" << std::endl; // Wyświetlenie informacji o ustawieniu stanu pola
            } else if (y > 4 && (x + y) % 2 == 1) { // Jeśli pole jest w ostatnich trzech rzędach i jest czarne
                grid[y][x].setState(FieldState::WHITE_PIECE); // Ustawienie stanu pola na biały pionek
                std::cout << "Field (" << x << ", " << y << ") set to WHITE_PIECE" << std::endl; // Wyświetlenie informacji o ustawieniu stanu pola
            } else { // W przeciwnym wypadku
                grid[y][x].setState(FieldState::EMPTY); // Ustawienie stanu pola na puste
                std::cout << "Field (" << x << ", " << y << ") set to EMPTY" << std::endl; // Wyświetlenie informacji o ustawieniu stanu pola
            }
        }
    }
}

bool Board::isValidMove(const Move& move, bool isCapture) const {
    const Field& startField = *getFieldAt(move.startPosition); // Pobranie pola startowego
    const Field& endField = *getFieldAt(move.endPositions[0]); // Pobranie pola końcowego
    if (startField.getState() == FieldState::EMPTY || endField.getState() != FieldState::EMPTY) { // Jeśli pole startowe jest puste lub pole końcowe nie jest puste
        return false; // Zwrócenie wartości false
    }

    sf::Vector2i direction = move.endPositions[0] - move.startPosition; // Obliczenie kierunku ruchu

    if (isCapture) { // Jeśli ruch jest biciem
        if (startField.getState() == FieldState::WHITE_QUEEN || startField.getState() == FieldState::BLACK_QUEEN) { // Jeśli pionek jest damką
            if (abs(direction.x) == abs(direction.y)) { // Jeśli ruch jest po skosie
                int stepX = direction.x / abs(direction.x); // Obliczenie kroku w osi x
                int stepY = direction.y / abs(direction.y); // Obliczenie kroku w osi y
                bool captured = false; // Ustawienie wartości captured na false
                sf::Vector2i checkPos = move.startPosition + sf::Vector2i(stepX, stepY); // Obliczenie pozycji do sprawdzenia
                while (checkPos != move.endPositions[0]) { // Dopóki pozycja do sprawdzenia nie jest równa pozycji końcowej
                    Field* checkField = getFieldAt(checkPos); // Pobranie pola do sprawdzenia
                    if (checkField->getState() != FieldState::EMPTY) { // Jeśli pole nie jest puste
                        if ((checkField->getState() == FieldState::WHITE_PIECE || checkField->getState() == FieldState::WHITE_QUEEN) &&
                            (startField.getState() == FieldState::BLACK_PIECE || startField.getState() == FieldState::BLACK_QUEEN)) { // Jeśli pole jest białym pionkiem lub damką i pionek jest czarny
                            if (captured) { // Jeśli captured jest true
                                return false; // Nie można zbić więcej niż jednego pionka na raz
                            }
                            captured = true; // Ustawienie captured na true
                        } else if ((checkField->getState() == FieldState::BLACK_PIECE || checkField->getState() == FieldState::BLACK_QUEEN) &&
                                   (startField.getState() == FieldState::WHITE_PIECE || startField.getState() == FieldState::WHITE_QUEEN)) { // Jeśli pole jest czarnym pionkiem lub damką i pionek jest biały
                            if (captured) { // Jeśli captured jest true
                                return false; // Nie można zbić więcej niż jednego pionka na raz
                            }
                            captured = true; // Ustawienie captured na true
                        } else { // W przeciwnym wypadku
                            return false; // Nie można zbić własnego pionka
                        }
                    }
                    checkPos += sf::Vector2i(stepX, stepY); // Zwiększenie pozycji do sprawdzenia
                }
                return captured; // Zwrócenie wartości captured
            }
        } else if (abs(direction.x) == 2 && abs(direction.y) == 2) { // Jeśli ruch jest o 2 pola
            sf::Vector2i middlePos = move.startPosition + direction / 2; // Obliczenie pozycji środkowej
            const Field& middleField = *getFieldAt(middlePos); // Pobranie pola środkowego
            if ((startField.getState() == FieldState::WHITE_PIECE && (middleField.getState() == FieldState::BLACK_PIECE || middleField.getState() == FieldState::BLACK_QUEEN)) ||
                (startField.getState() == FieldState::BLACK_PIECE && (middleField.getState() == FieldState::WHITE_PIECE || middleField.getState() == FieldState::WHITE_QUEEN))) { // Jeśli pionek jest białym i pole środkowe jest czarnym pionkiem lub damką lub pionek jest czarnym i pole środkowe jest białym pionkiem lub damką
                return true; // Zwrócenie wartości true
            }
        }
    } else { // W przeciwnym wypadku
        if (startField.getState() == FieldState::WHITE_PIECE && direction.y == -1 && abs(direction.x) == 1) { // Jeśli pionek jest białym pionkiem i ruch jest o 1 pole do góry
            return true; // Zwrócenie wartości true
        } else if (startField.getState() == FieldState::BLACK_PIECE && direction.y == 1 && abs(direction.x) == 1) { // Jeśli pionek jest czarnym pionkiem i ruch jest o 1 pole w dół
            return true; // Zwrócenie wartości true
        } else if ((startField.getState() == FieldState::WHITE_QUEEN || startField.getState() == FieldState::BLACK_QUEEN) && abs(direction.x) == abs(direction.y)) { // Jeśli pionek jest damką i ruch jest po skosie
            for (int i = 1; i < abs(direction.x); ++i) { // Pętla od 1 do wartości bezwzględnej kierunku x
                sf::Vector2i intermediatePos = move.startPosition + sf::Vector2i(i * (direction.x / abs(direction.x)), i * (direction.y / abs(direction.y))); // Obliczenie pozycji pośredniej
                if (getFieldAt(intermediatePos)->getState() != FieldState::EMPTY) { // Jeśli pole pośrednie nie jest puste
                    return false; // Zwrócenie wartości false
                }
            }
            return true; // Zwrócenie wartości true
        }
    }

    return false; // Zwrócenie wartości false
}



bool Board::canCapture(const sf::Vector2i& position) const {
    const Field& field = *getFieldAt(position); // Pobranie pola
    if (field.getState() == FieldState::EMPTY) { // Jeśli pole jest puste
        return false; // Zwrócenie wartości false
    }

    std::vector<sf::Vector2i> directions = {{2, 2}, {2, -2}, {-2, 2}, {-2, -2}}; // Utworzenie wektora kierunków
    for (const sf::Vector2i& direction : directions) { // Pętla po kierunkach
        sf::Vector2i endPosition = position + direction; // Obliczenie pozycji końcowej
        if (isInsideBoard(endPosition)) { // Jeśli pozycja końcowa jest w planszy
            Move move(position, endPosition); // Utworzenie ruchu
            if (isValidMove(move, true)) { // Jeśli ruch jest poprawny
                return true; // Zwrócenie wartości true
            }
        }
    }

    if (field.getState() == FieldState::WHITE_QUEEN || field.getState() == FieldState::BLACK_QUEEN) { // Jeśli pionek jest damką
        directions = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; // Utworzenie wektora kierunków
        for (const sf::Vector2i& direction : directions) { // Pętla po kierunkach
            sf::Vector2i checkPos = position + direction; // Obliczenie pozycji do sprawdzenia
            bool canCapture = false; // Ustawienie wartości canCapture na false
            while (isInsideBoard(checkPos)) { // Dopóki pozycja do sprawdzenia jest w planszy
                const Field& checkField = *getFieldAt(checkPos); // Pobranie pola do sprawdzenia
                if (checkField.getState() != FieldState::EMPTY && checkField.getState() != field.getState() &&
                    ((field.getState() == FieldState::WHITE_QUEEN && (checkField.getState() == FieldState::BLACK_PIECE || checkField.getState() == FieldState::BLACK_QUEEN)) ||
                     (field.getState() == FieldState::BLACK_QUEEN && (checkField.getState() == FieldState::WHITE_PIECE || checkField.getState() == FieldState::WHITE_QUEEN)))) { // Jeśli pole do sprawdzenia nie jest puste i nie jest takie samo jak pole oraz pionek jest białą damką i pole do sprawdzenia jest czarnym pionkiem lub damką lub pionek jest czarną damką i pole do sprawdzenia jest białym pionkiem lub damką
                    sf::Vector2i nextPos = checkPos + direction; // Obliczenie następnej pozycji
                    if (isInsideBoard(nextPos) && getFieldAt(nextPos)->getState() == FieldState::EMPTY) { // Jeśli następna pozycja jest w planszy i pole jest puste
                        canCapture = true; // Ustawienie canCapture na true
                        break; // Przerwanie pętli
                    }
                }
                checkPos += direction; // Zwiększenie pozycji do sprawdzenia
            }
            if (canCapture) return true; // Jeśli canCapture jest true, zwrócenie wartości true
        }
    }

    return false; // Zwrócenie wartości false
}

void Board::makeMove(const Move& move) {
    Field* startField = getFieldAt(move.startPosition); // Pobranie pola startowego
    if (!startField) return; // Jeśli pole startowe nie istnieje, zakończenie funkcji

    for (const sf::Vector2i& endPos : move.endPositions) { // Pętla po pozycjach końcowych
        Field* endField = getFieldAt(endPos); // Pobranie pola końcowego
        if (!endField) continue; // Jeśli pole końcowe nie istnieje, kontynuacja pętli

        sf::Vector2i direction = endPos - sf::Vector2i(startField->getPosition().x / fieldSideLength, startField->getPosition().y / fieldSideLength); // Obliczenie kierunku ruchu
        bool captured = false; // Ustawienie captured na false

        if ((startField->getState() == FieldState::WHITE_QUEEN || startField->getState() == FieldState::BLACK_QUEEN) && abs(direction.x) == abs(direction.y)) { // Jeśli pionek jest damką i ruch jest po skosie
            int stepX = direction.x / abs(direction.x); // Obliczenie kroku w osi x
            int stepY = direction.y / abs(direction.y); // Obliczenie kroku w osi y
            sf::Vector2i checkPos = sf::Vector2i(startField->getPosition().x / fieldSideLength, startField->getPosition().y / fieldSideLength) + sf::Vector2i(stepX, stepY); // Obliczenie pozycji do sprawdzenia
            while (checkPos != endPos) { // Dopóki pozycja do sprawdzenia nie jest równa pozycji końcowej
                Field* checkField = getFieldAt(checkPos); // Pobranie pola do sprawdzenia
                if (checkField->getState() != FieldState::EMPTY) { // Jeśli pole nie jest puste
                    if (checkField->getState() != startField->getState() && !captured) { // Jeśli pole nie jest takie samo jak pole startowe i captured jest false
                        checkField->setState(FieldState::EMPTY); // Ustawienie stanu pola na puste
                        captured = true; // Ustawienie captured na true
                    } else {
                        return; // Nie można zbić więcej niż jednego pionka na raz
                    }
                }
                checkPos += sf::Vector2i(stepX, stepY); // Zwiększenie pozycji do sprawdzenia
            }
        } else if (abs(direction.x) == 2 && abs(direction.y) == 2) { // Jeśli ruch jest o 2 pola
            sf::Vector2i capturedPosition = sf::Vector2i(startField->getPosition().x / fieldSideLength, startField->getPosition().y / fieldSideLength) + sf::Vector2i(direction.x / 2, direction.y / 2); // Obliczenie pozycji zbitego pionka
            Field* capturedField = getFieldAt(capturedPosition); // Pobranie pola zbitego pionka
            if (capturedField && capturedField->getState() != startField->getState()) { // Jeśli pole zbitego pionka istnieje i nie jest takie samo jak pole startowe
                capturedField->setState(FieldState::EMPTY); // Ustawienie stanu pola na puste
                captured = true; // Ustawienie captured na true
            } else { // W przeciwnym wypadku
                return; // Nie można zbić własnego pionka
            }
        }

        endField->setState(startField->getState()); // Ustawienie stanu pola końcowego na stan pola startowego
        startField->setState(FieldState::EMPTY); // Ustawienie stanu pola startowego na puste
        bool promotion = false; // Ustawienie promotion na false

        if (endField->getState() == FieldState::WHITE_PIECE && endPos.y == 0) { // Jeśli pole końcowe jest białym pionkiem i jest na pierwszym rzędzie
            endField->setState(FieldState::WHITE_QUEEN); // Ustawienie stanu pola końcowego na białą damkę
            promotion = true; // Ustawienie promotion na true
        } else if (endField->getState() == FieldState::BLACK_PIECE && endPos.y == 7) { // Jeśli pole końcowe jest czarnym pionkiem i jest na ostatnim rzędzie
            endField->setState(FieldState::BLACK_QUEEN); // Ustawienie stanu pola końcowego na czarną damkę
            promotion = true; // Ustawienie promotion na true
        }

        if (!promotion && captured && canCapture(endPos)) { // Jeśli nie ma promocji, captured jest true i można zbić więcej pionków
            mustContinueCapturing = true; // Ustawienie mustContinueCapturing na true
        } else { // W przeciwnym wypadku
            mustContinueCapturing = false; // W przeciwnym wypadku ustawienie mustContinueCapturing na false
        }
    }
}

void Board::draw(sf::RenderWindow& window) {
    window.draw(boardSprite); // Narysowanie planszy
    for (int y = 0; y < 8; ++y) { // Pętla po rzędach
        for (int x = 0; x < 8; ++x) { // Pętla po kolumnach
            grid[y][x].draw(window); // Narysowanie pola
        }
    }
}

Field* Board::getFieldAt(const sf::Vector2i& position) const {
    if (isInsideBoard(position)) { // Jeśli pozycja jest w planszy
        return const_cast<Field*>(&grid[position.y][position.x]); // Zwrócenie pola
    }
    return nullptr; // W przeciwnym wypadku zwrócenie wartości nullptr
}

Field* Board::getFieldContainingPoint(const sf::Vector2i& point) const {
    for (int y = 0; y < 8; ++y) { // Pętla po rzędach
        for (int x = 0; x < 8; ++x) { // Pętla po kolumnach
            if (grid[y][x].contains(point)) { // Jeśli pole zawiera punkt
                return const_cast<Field*>(&grid[y][x]); // Zwrócenie pola
            }
        }
    }
    return nullptr; // W przeciwnym wypadku zwrócenie wartości nullptr
}

bool Board::isInsideBoard(const sf::Vector2i& position) const {
    return position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8; // Zwrócenie wartości true jeśli pozycja jest w planszy, w przeciwnym wypadku false
}

float Board::getFieldSideLength() const {
    return fieldSideLength; // Zwrócenie długości boku pola
}

bool Board::hasCaptureMoves(PieceColor color) const {
    for (int y = 0; y < 8; ++y) { // Pętla po rzędach
        for (int x = 0; x < 8; ++x) { // Pętla po kolumnach
            FieldState state = grid[y][x].getState(); // Pobranie stanu pola
            if ((color == PieceColor::WHITE && (state == FieldState::WHITE_PIECE || state == FieldState::WHITE_QUEEN)) ||
                (color == PieceColor::BLACK && (state == FieldState::BLACK_PIECE || state == FieldState::BLACK_QUEEN))) { // Jeśli kolor jest biały i stan pola jest białym pionkiem lub damką lub kolor jest czarny i stan pola jest czarnym pionkiem lub damką
                if (canCapture(sf::Vector2i(x, y))) { // Jeśli można zbić pionka
                    return true; // Zwrócenie wartości true
                }
            }
        }
    }
    return false; // Zwrócenie wartości false
}


void Board::printBoard() const {
    for (int y = 0; y < 8; ++y) { // Pętla po rzędach
        for (int x = 0; x < 8; ++x) { // Pętla po kolumnach
            if ((x + y) % 2 == 1) { // Jeśli pole jest czarne
                FieldState state = grid[y][x].getState(); // Pobranie stanu pola
                if (state == FieldState::WHITE_PIECE) {
                    std::cout << "| b "; // Biały pionek
                } else if (state == FieldState::BLACK_PIECE) {
                    std::cout << "| c "; // Czarny pionek
                } else if (state == FieldState::WHITE_QUEEN) {
                    std::cout << "| Q "; // Biała dama
                } else if (state == FieldState::BLACK_QUEEN) {
                    std::cout << "| k "; // Czarna dama
                } else {
                    std::cout << "| 0 "; // Puste pole
                }
            } else {
                std::cout << "|   "; // Puste pola
            }
        }
        std::cout << "|" << std::endl; // Zakończenie linii
    }
    std::cout <<"---------------------------------------------------"<< std::endl;
}

void Board::setMustContinueCapturing(bool value) {
    mustContinueCapturing = value; // Ustawienie mustContinueCapturing na wartość value
}