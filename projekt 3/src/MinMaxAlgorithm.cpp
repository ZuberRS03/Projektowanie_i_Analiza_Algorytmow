#include "MinMaxAlgorithm.h"
#include <limits>
#include <iostream>

Move MinMaxAlgorithm::calculateBestMove(const Board& board, int depth) {
    std::cout << "Calculating best move for bot..." << std::endl;
    int bestValue = std::numeric_limits<int>::min();
    Move bestMove(sf::Vector2i(0, 0), sf::Vector2i(0, 0));

    std::vector<Move> allPossibleMoves = getAllPossibleMoves(board, PieceColor::BLACK); // Zmieniono na PieceColor::BLACK dla bota

    std::cout << "Calculating best move for bot..." << std::endl;
    for (const Move& move : allPossibleMoves) {
        std::cout << "Evaluating move: (" << move.startPosition.x << ", " << move.startPosition.y << ") -> ("
                  << move.endPosition.x << ", " << move.endPosition.y << ")" << std::endl;
        Board boardCopy = board; // Utwórz kopię planszy
        boardCopy.makeMove(move);
        int boardValue = minMax(boardCopy, depth - 1, false);
        std::cout << "Move value: " << boardValue << std::endl;
        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestMove = move;
        }
    }

    std::cout << "Best move selected: (" << bestMove.startPosition.x << ", " << bestMove.startPosition.y << ") -> ("
              << bestMove.endPosition.x << ", " << bestMove.endPosition.y << ")" << std::endl;
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
    std::vector<Move> allMoves;
    std::vector<Move> capturingMoves;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            sf::Vector2i pos(x, y);
            FieldState state = board.getFieldAt(pos)->getState();
            if ((color == PieceColor::WHITE && (state == FieldState::WHITE_PIECE || state == FieldState::WHITE_QUEEN)) ||
                (color == PieceColor::BLACK && (state == FieldState::BLACK_PIECE || state == FieldState::BLACK_QUEEN))) {

                std::vector<sf::Vector2i> possibleEndPositions = getPossibleEndPositions(board, pos);
                for (const sf::Vector2i& endPos : possibleEndPositions) {
                    Move move(pos, endPos);
                    if (board.isValidMove(move, true)) {
                        capturingMoves.push_back(move);  // Dodaj ruch bicia do oddzielnej listy
                    } else if (board.isValidMove(move, false)) {
                        allMoves.push_back(move);  // Dodaj zwykły ruch do listy
                    }
                }
            }
        }
    }

    if (!capturingMoves.empty()) {
        return capturingMoves;  // Priorytetowo traktuj ruchy bicia
    }
    return allMoves;  // Zwróć zwykłe ruchy tylko, jeśli nie ma ruchów bicia
}

std::vector<sf::Vector2i> MinMaxAlgorithm::getPossibleEndPositions(const Board& board, const sf::Vector2i& startPos) {
    std::vector<sf::Vector2i> endPositions;
    FieldState state = board.getFieldAt(startPos)->getState();

    if (state == FieldState::WHITE_QUEEN || state == FieldState::BLACK_QUEEN) {
        // Ruchy damki
        int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (auto& dir : directions) {
            for (int i = 1; i < 8; ++i) {
                sf::Vector2i endPos = startPos + sf::Vector2i(i * dir[0], i * dir[1]);
                if (!board.isInsideBoard(endPos)) {
                    break; // Zatrzymaj się, jeśli wyjdziesz poza planszę
                }
                endPositions.push_back(endPos);
                if (board.getFieldAt(endPos)->getState() != FieldState::EMPTY) {
                    break; // Zatrzymaj się, jeśli napotkasz inny pionek
                }
            }
        }
    } else {
        // Ruchy zwykłego pionka
        int moveDirections[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        int captureDirections[4][2] = {{2, 2}, {2, -2}, {-2, 2}, {-2, -2}};

        // Normalne ruchy
        for (auto& dir : moveDirections) {
            sf::Vector2i endPos = startPos + sf::Vector2i(dir[0], dir[1]);
            if (board.isInsideBoard(endPos) && board.isValidMove(Move(startPos, endPos), false)) {
                endPositions.push_back(endPos);
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