#include "MinMaxAlgorithm.h"
#include <limits>
#include <iostream>

Move MinMaxAlgorithm::calculateBestMove(const Board& board, int depth) {
    std::vector<Move> allPossibleMoves = getAllPossibleMoves(board, PieceColor::BLACK); // Znajdź wszystkie możliwe ruchy dla bota

    // Jeśli nie ma dostępnych ruchów, zwróć ruch domyślny (nie wykonuje się)
    if (allPossibleMoves.empty()) {
        return Move(sf::Vector2i(0, 0), sf::Vector2i(0, 0));
    }

    int bestValue = std::numeric_limits<int>::min(); // Najlepsza wartość to najmniejsza możliwa
    Move bestMove = allPossibleMoves[0]; // Ustaw pierwszy dostępny ruch jako najlepszy

    for (const Move& move : allPossibleMoves) { // Dla każdego możliwego ruchu
        Board boardCopy = board; // Skopiuj planszę
        boardCopy.makeMove(move); // Wykonaj ruch
        int boardValue = minMax(boardCopy, depth - 1, false); // Oblicz wartość planszy po ruchu
        if (boardValue > bestValue) { // Jeśli wartość planszy jest lepsza od najlepszej dotychczas
            bestValue = boardValue; // Ustaw nową najlepszą wartość
            bestMove = move; // Ustaw nowy najlepszy ruch
        }
    }

    return bestMove; // Zwróć najlepszy ruch
}

int MinMaxAlgorithm::evaluateBoard(const Board& board) {
    int value = 0; // Wartość planszy
    for (int y = 0; y < 8; ++y) { // Dla każdego pola na planszy
        for (int x = 0; x < 8; ++x) { // Dla każdego pola na planszy
            FieldState state = board.getFieldAt(sf::Vector2i(x, y))->getState(); // Pobierz stan pola
            if (state == FieldState::WHITE_PIECE) { // Jeśli pole jest białym pionkiem
                value -= 1; // Zwiększ wartość planszy
            } else if (state == FieldState::BLACK_PIECE) { // Jeśli pole jest czarnym pionkiem
                value += 1; // Zmniejsz wartość planszy
            } else if (state == FieldState::WHITE_QUEEN) { // Jeśli pole jest białą damką
                value -= 3; // Zwiększ wartość planszy
            } else if (state == FieldState::BLACK_QUEEN) { // Jeśli pole jest czarną damką
                value += 3; // Zmniejsz wartość planszy
            }
        }
    }
    return value; // Zwróć wartość planszy
}

int MinMaxAlgorithm::minMax(Board& board, int depth, bool isMaximizingPlayer) {

    if (depth == 0) { // Jeśli osiągnięto maksymalną głębokość
        return evaluateBoard(board); // Zwróć wartość planszy
    }

    std::vector<Move> allPossibleMoves = getAllPossibleMoves(board, isMaximizingPlayer ? PieceColor::BLACK : PieceColor::WHITE); // Znajdź wszystkie możliwe ruchy dla gracza

    if (isMaximizingPlayer) { // Jeśli gracz maksymalizujący
        int maxEval = std::numeric_limits<int>::min(); // Najlepsza wartość to najmniejsza możliwa
        for (const Move& move : allPossibleMoves) { // Dla każdego możliwego ruchu
            Board boardCopy = board; // Skopiuj planszę
            boardCopy.makeMove(move); // Wykonaj
            int eval = minMax(boardCopy, depth - 1, false); // Oblicz wartość planszy po ruchu
            maxEval = std::max(maxEval, eval);  // Jeśli wartość planszy jest lepsza od najlepszej dotychczas
        }
        return maxEval; // Zwróć najlepszą wartość
    } else { // Jeśli gracz minimalizujący
        int minEval = std::numeric_limits<int>::max(); // Najlepsza wartość to największa możliwa
        for (const Move& move : allPossibleMoves) { // Dla każdego możliwego ruchu
            Board boardCopy = board; // Skopiuj planszę
            boardCopy.makeMove(move); // Wykonaj ruch
            int eval = minMax(boardCopy, depth - 1, true); // Oblicz wartość planszy po ruchu
            minEval = std::min(minEval, eval); // Jeśli wartość planszy jest gorsza od najlepszej dotychczas
        }
        return minEval; // Zwróć najlepszą wartość
    }
}

std::vector<Move> MinMaxAlgorithm::getAllPossibleMoves(const Board& board, PieceColor color) {
    std::vector<Move> allPossibleMoves; // Lista wszystkich możliwych ruchów
    std::vector<Move> capturingMoves; // Lista wszystkich możliwych ruchów bicia

    for (int y = 0; y < 8; ++y) { // Dla każdego pola na planszy
        for (int x = 0; x < 8; ++x) { // Dla każdego pola na planszy
            sf::Vector2i pos(x, y); // Pozycja pionka
            FieldState state = board.getFieldAt(pos)->getState(); // Stan pola
            if ((color == PieceColor::WHITE && (state == FieldState::WHITE_PIECE || state == FieldState::WHITE_QUEEN)) ||
                (color == PieceColor::BLACK && (state == FieldState::BLACK_PIECE || state == FieldState::BLACK_QUEEN))) { // Jeśli pionek należy do gracza

                std::vector<sf::Vector2i> possibleEndPositions = getPossibleEndPositions(board, pos, true); // true dla bicia
                for (const sf::Vector2i& endPos : possibleEndPositions) { // Dla każdego możliwego zakończenia ruchu
                    Move move(pos, endPos); // Stwórz ruch
                    if (board.isValidMove(move, true)) { // Jeśli ruch jest możliwy
                        capturingMoves.push_back(move); // Dodaj ruch bicia do oddzielnej listy

                        // Po każdym możliwym biciu, sprawdź czy są dostępne kolejne bicia
                        Board tempBoard = board; // Skopiuj planszę
                        tempBoard.makeMove(move); // Wykonaj ruch
                        if (tempBoard.hasCaptureMoves(color)) { // Jeśli są dostępne kolejne ruchy bicia
                            std::vector<Move> additionalMoves = getAllPossibleMoves(tempBoard, color); // Znajdź kolejne ruchy bicia
                            for (Move& additionalMove : additionalMoves) { // Dla każdego możliwego ruchu bicia
                                Move extendedMove = move; // Stwórz ruch z dodatkowymi zakończeniami
                                for (const sf::Vector2i& endPos : additionalMove.endPositions) { // Dla każdego możliwego zakończenia ruchu
                                    extendedMove.addEndPosition(endPos); // Dodaj zakończenie do ruchu
                                }
                                capturingMoves.push_back(extendedMove); // Dodaj ruch do listy
                            }
                        }
                    }
                }

                possibleEndPositions = getPossibleEndPositions(board, pos, false); // false dla normalnego ruchu
                for (const sf::Vector2i& endPos : possibleEndPositions) { // Dla każdego możliwego zakończenia ruchu
                    Move move(pos, endPos); // Stwórz ruch
                    if (board.isValidMove(move, false)) { // Jeśli ruch jest możliwy
                        allPossibleMoves.push_back(move); // Dodaj zwykły ruch do listy
                    }
                }
            }
        }
    }

    if (!capturingMoves.empty()) { // Jeśli są dostępne ruchy bicia
        return capturingMoves; // Priorytetowo traktuj ruchy bicia
    }

    return allPossibleMoves; // Zwróć zwykłe ruchy tylko, jeśli nie ma ruchów bicia
}

std::vector<sf::Vector2i> MinMaxAlgorithm::getPossibleEndPositions(const Board& board, const sf::Vector2i& startPos, bool isCapture) {
    std::vector<sf::Vector2i> endPositions; // Lista wszystkich możliwych zakończeń ruchu
    FieldState state = board.getFieldAt(startPos)->getState(); // Stan pola

    if (state == FieldState::WHITE_QUEEN || state == FieldState::BLACK_QUEEN) { // Jeśli damka
        // Ruchy i bicia damki
        int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; // Kierunki ruchu damki
        for (auto& dir : directions) { // Dla każdego kierunku
            for (int i = 1; i < 8; ++i) { // Dla każdego możliwego zasięgu ruchu
                sf::Vector2i endPos = startPos + sf::Vector2i(i * dir[0], i * dir[1]); // Oblicz zakończenie ruchu
                if (!board.isInsideBoard(endPos)) { // Jeśli zakończenie ruchu jest poza planszą
                    break; // Zatrzymaj się, jeśli wyjdziesz poza planszę
                }
                if (board.isValidMove(Move(startPos, endPos), isCapture)) { // Jeśli ruch jest możliwy
                    endPositions.push_back(endPos); // Dodaj zakończenie ruchu do listy
                    if (isCapture && board.getFieldAt(endPos)->getState() != FieldState::EMPTY) { // Jeśli ruch jest biciem i napotkano pionek
                        break; // Zatrzymaj się po zbiciu
                    }
                    if (!isCapture && board.getFieldAt(endPos)->getState() != FieldState::EMPTY) { // Jeśli ruch jest zwykłym ruchem i napotkano pionek
                        break; // Zatrzymaj się, jeśli napotkasz inny pionek
                    }
                }
            }
        }
    } else {
        // Ruchy zwykłego pionka
        int moveDirections[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; // Kierunki ruchu
        int captureDirections[4][2] = {{2, 2}, {2, -2}, {-2, 2}, {-2, -2}}; // Kierunki bicia

        // Normalne ruchy
        if (!isCapture) { // Jeśli ruch nie jest biciem
            for (auto& dir : moveDirections) { // Dla każdego kierunku ruchu
                sf::Vector2i endPos = startPos + sf::Vector2i(dir[0], dir[1]); // Oblicz zakończenie ruchu
                if (board.isInsideBoard(endPos) && board.isValidMove(Move(startPos, endPos), false)) { // Jeśli ruch jest możliwy
                    endPositions.push_back(endPos); // Dodaj zakończenie ruchu do listy
                }
            }
        }

        // Ruchy bicia
        for (auto& dir : captureDirections) { // Dla każdego kierunku bicia
            sf::Vector2i endPos = startPos + sf::Vector2i(dir[0], dir[1]); // Oblicz zakończenie ruchu
            if (board.isInsideBoard(endPos) && board.isValidMove(Move(startPos, endPos), true)) { // Jeśli ruch jest możliwy
                endPositions.push_back(endPos); // Dodaj zakończenie ruchu do listy
            }
        }
    }

    return endPositions; // Zwróć listę zakończeń ruchu
}