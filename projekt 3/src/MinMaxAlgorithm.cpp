#include "MinMaxAlgorithm.h"
#include <limits>
#include <iostream>

Move MinMaxAlgorithm::calculateBestMove(const Board& board, int depth) {
    std::vector<Move> allPossibleMoves = getAllPossibleMoves(board, PieceColor::BLACK);

    // Jeśli nie ma dostępnych ruchów, zwróć ruch domyślny
    if (allPossibleMoves.empty()) {
        return Move(sf::Vector2i(0, 0), sf::Vector2i(0, 0));
    }

    int bestValue = std::numeric_limits<int>::min();
    Move bestMove = allPossibleMoves[0]; // Ustaw pierwszy dostępny ruch jako najlepszy

    for (const Move& move : allPossibleMoves) {
        Board boardCopy = board;
        boardCopy.makeMove(move);
        int boardValue = minMax(boardCopy, depth - 1, false);
        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestMove = move;
        }
    }

    return bestMove;
}

int MinMaxAlgorithm::evaluateBoard(const Board& board) {
    int value = 0;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            FieldState state = board.getFieldAt(sf::Vector2i(x, y))->getState();
            if (state == FieldState::WHITE_PIECE) {
                value -= 1;
            } else if (state == FieldState::BLACK_PIECE) {
                value += 1;
            } else if (state == FieldState::WHITE_QUEEN) {
                value -= 3;
            } else if (state == FieldState::BLACK_QUEEN) {
                value += 3;
            }
        }
    }
    return value;
}

int MinMaxAlgorithm::minMax(Board& board, int depth, bool isMaximizingPlayer) {

    if (depth == 0) {
        return evaluateBoard(board);
    }

    std::vector<Move> allPossibleMoves = getAllPossibleMoves(board, isMaximizingPlayer ? PieceColor::BLACK : PieceColor::WHITE);

    if (isMaximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const Move& move : allPossibleMoves) {
            Board boardCopy = board;
            boardCopy.makeMove(move);
            int eval = minMax(boardCopy, depth - 1, false);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (const Move& move : allPossibleMoves) {
            Board boardCopy = board;
            boardCopy.makeMove(move);
            int eval = minMax(boardCopy, depth - 1, true);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

std::vector<Move> MinMaxAlgorithm::getAllPossibleMoves(const Board& board, PieceColor color) {
    std::vector<Move> allPossibleMoves;
    std::vector<Move> capturingMoves;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            sf::Vector2i pos(x, y);
            FieldState state = board.getFieldAt(pos)->getState();
            if ((color == PieceColor::WHITE && (state == FieldState::WHITE_PIECE || state == FieldState::WHITE_QUEEN)) ||
                (color == PieceColor::BLACK && (state == FieldState::BLACK_PIECE || state == FieldState::BLACK_QUEEN))) {

                std::vector<sf::Vector2i> possibleEndPositions = getPossibleEndPositions(board, pos, true); // true dla bicia
                for (const sf::Vector2i& endPos : possibleEndPositions) {
                    Move move(pos, endPos);
                    if (board.isValidMove(move, true)) {
                        capturingMoves.push_back(move); // Dodaj ruch bicia do oddzielnej listy

                        // Po każdym możliwym biciu, sprawdź czy są dostępne kolejne bicia
                        Board tempBoard = board;
                        tempBoard.makeMove(move);
                        if (tempBoard.hasCaptureMoves(color)) {
                            std::vector<Move> additionalMoves = getAllPossibleMoves(tempBoard, color);
                            for (Move& additionalMove : additionalMoves) {
                                Move extendedMove = move;
                                for (const sf::Vector2i& endPos : additionalMove.endPositions) {
                                    extendedMove.addEndPosition(endPos);
                                }
                                capturingMoves.push_back(extendedMove);
                            }
                        }
                    }
                }

                possibleEndPositions = getPossibleEndPositions(board, pos, false); // false dla normalnego ruchu
                for (const sf::Vector2i& endPos : possibleEndPositions) {
                    Move move(pos, endPos);
                    if (board.isValidMove(move, false)) {
                        allPossibleMoves.push_back(move); // Dodaj zwykły ruch do listy
                    }
                }
            }
        }
    }

    if (!capturingMoves.empty()) {
        return capturingMoves; // Priorytetowo traktuj ruchy bicia
    }

    return allPossibleMoves; // Zwróć zwykłe ruchy tylko, jeśli nie ma ruchów bicia
}

std::vector<sf::Vector2i> MinMaxAlgorithm::getPossibleEndPositions(const Board& board, const sf::Vector2i& startPos, bool isCapture) {
    std::vector<sf::Vector2i> endPositions;
    FieldState state = board.getFieldAt(startPos)->getState();

    if (state == FieldState::WHITE_QUEEN || state == FieldState::BLACK_QUEEN) {
        // Ruchy i bicia damki
        int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (auto& dir : directions) {
            for (int i = 1; i < 8; ++i) {
                sf::Vector2i endPos = startPos + sf::Vector2i(i * dir[0], i * dir[1]);
                if (!board.isInsideBoard(endPos)) {
                    break; // Zatrzymaj się, jeśli wyjdziesz poza planszę
                }
                if (board.isValidMove(Move(startPos, endPos), isCapture)) {
                    endPositions.push_back(endPos);
                    if (isCapture && board.getFieldAt(endPos)->getState() != FieldState::EMPTY) {
                        break; // Zatrzymaj się po zbiciu
                    }
                    if (!isCapture && board.getFieldAt(endPos)->getState() != FieldState::EMPTY) {
                        break; // Zatrzymaj się, jeśli napotkasz inny pionek
                    }
                }
            }
        }
    } else {
        // Ruchy zwykłego pionka
        int moveDirections[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        int captureDirections[4][2] = {{2, 2}, {2, -2}, {-2, 2}, {-2, -2}};

        // Normalne ruchy
        if (!isCapture) {
            for (auto& dir : moveDirections) {
                sf::Vector2i endPos = startPos + sf::Vector2i(dir[0], dir[1]);
                if (board.isInsideBoard(endPos) && board.isValidMove(Move(startPos, endPos), false)) {
                    endPositions.push_back(endPos);
                }
            }
        }

        // Ruchy bicia
        for (auto& dir : captureDirections) {
            sf::Vector2i endPos = startPos + sf::Vector2i(dir[0], dir[1]);
            if (board.isInsideBoard(endPos) && board.isValidMove(Move(startPos, endPos), true)) {
                endPositions.push_back(endPos);
            }
        }
    }

    return endPositions;
}