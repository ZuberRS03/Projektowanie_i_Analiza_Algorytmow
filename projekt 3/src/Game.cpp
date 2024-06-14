#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(691, 691), "Checkers Game"), currentTurn(PieceColor::WHITE), selectedField(nullptr), isPieceSelected(false) {
    board.initialize();
    player1 = new HumanPlayer(PieceColor::WHITE);
    player2 = new HumanPlayer(PieceColor::BLACK);
    currentPlayer = player1;
}

void Game::run() {
    while (window.isOpen()) {
        handlePlayerInput();
        update();
        render();

    }
}

void Game::handlePlayerInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (isPieceSelected) {
                    // Ruch pionka
                    Field* endField = board.getFieldContainingPoint(mousePos);
                    if (endField) {
                        sf::Vector2i endPosition((int)(endField->getPosition().x / board.getFieldSideLength()), (int)(endField->getPosition().y / board.getFieldSideLength()));
                        Move move(selectedPosition, endPosition);
                        if (board.isValidMove(move)) {
                            board.makeMove(move);
                            isPieceSelected = false;
                            selectedField = nullptr;
                            // Zmiana tury
                            currentTurn = (currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
                            currentPlayer = (currentTurn == PieceColor::WHITE) ? player1 : player2;
                            std::cout << "Piece moved to position: (" << endPosition.x << ", " << endPosition.y << ")\n";
                            board.printBoard(); // Wywołanie funkcji printBoard
                        } else {
                            isPieceSelected = false;
                            selectedField = nullptr;
                            std::cout << "Invalid move to position: (" << endPosition.x << ", " << endPosition.y << ")\n";
                        }
                    }
                } else {
                    // Wybór pionka
                    Field* field = board.getFieldContainingPoint(mousePos);
                    if (field && field->getState() != FieldState::EMPTY &&
                        ((field->getState() == FieldState::WHITE_PIECE && currentTurn == PieceColor::WHITE) ||
                         (field->getState() == FieldState::BLACK_PIECE && currentTurn == PieceColor::BLACK))) {
                        isPieceSelected = true;
                        selectedPosition = sf::Vector2i((int)(field->getPosition().x / board.getFieldSideLength()), (int)(field->getPosition().y / board.getFieldSideLength()));
                        selectedField = field;
                        std::cout << "Piece selected at position: (" << selectedPosition.x << ", " << selectedPosition.y << ")\n";
                    } else {
                        std::cout << "No piece selected or wrong turn at position: (" << mousePos.x << ", " << mousePos.y << ")\n";
                    }
                }
            }
        }
    }
}

void Game::update() {
    // Aktualizacja stanu gry
}

void Game::render() {
    window.clear();
    board.draw(window);
    window.display();
}
