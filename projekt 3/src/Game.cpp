#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(711, 691), "Checkers Game"), currentTurn(PieceColor::WHITE), selectedField(nullptr), isPieceSelected(false), mustContinueCapturing(false), isBotGame(false) {
    board.initialize();

    // Zapytaj użytkownika, czy chce grać z botem
    std::string input;
    std::cout << "Czy chcesz grać z botem? (t/n): ";
    std::cin >> input;
    if (input == "t") {
        player1 = new HumanPlayer(PieceColor::WHITE);
        player2 = new Bot(PieceColor::BLACK);
    } else {
        player1 = new HumanPlayer(PieceColor::WHITE);
        player2 = new HumanPlayer(PieceColor::BLACK);
    }
    currentPlayer = player1;

    // Inicjalizacja wskaźnika tury
    turnIndicator.setSize(sf::Vector2f(20, 691));
    turnIndicator.setPosition(691, 0); // Ustawienie wskaźnika na prawo od szachownicy
    turnIndicator.setFillColor(sf::Color::White); // Początkowy kolor dla białego gracza

    // Inicjalizacja wskaźnika bicia
    captureIndicator.setRadius(7.5f); // Średnica 15 pikseli
    captureIndicator.setFillColor(sf::Color::Transparent); // Początkowo ukryty
    captureIndicator.setPosition(691 + 2.5f, 338 - 7.5f); // Ustawienie początkowej pozycji
}

void Game::run() {
    while (window.isOpen()) {
        handlePlayerInput();
        update();
        render();

    }
}

bool Game::hasCaptureMoves() const {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            FieldState state = board.getFieldAt(sf::Vector2i(x, y))->getState();
            if ((state == FieldState::WHITE_PIECE && currentTurn == PieceColor::WHITE) ||
                (state == FieldState::BLACK_PIECE && currentTurn == PieceColor::BLACK)) {
                if (board.canCapture(sf::Vector2i(x, y))) {
                    return true;
                }
            }
        }
    }
    return false;
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
                        bool isCapture = board.isValidMove(move, true); // Sprawdź ruch bicia
                        if (isCapture) {
                            board.makeMove(move);
                            if (!board.mustContinueCapturing) {
                                isPieceSelected = false;
                                selectedField = nullptr;
                                mustContinueCapturing = false; // Reset mustContinueCapturing
                                currentTurn = (currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
                                currentPlayer = (currentTurn == PieceColor::WHITE) ? player1 : player2;
                                turnIndicator.setFillColor(currentTurn == PieceColor::WHITE ? sf::Color::White : sf::Color::Black); // Zmień kolor wskaźnika tury
                                updateCaptureIndicator(); // Aktualizuj wskaźnik bicia
                            } else {
                                selectedPosition = endPosition;
                                selectedField = endField;
                                mustContinueCapturing = true; // Ustaw mustContinueCapturing na true
                                board.setMustContinueCapturing(true); // Aktualizuj stan mustContinueCapturing w Board
                                std::cout << "Piece can continue capturing at position: (" << endPosition.x << ", " << endPosition.y << ")\n";
                                updateCaptureIndicator(); // Aktualizuj wskaźnik bicia
                            }
                            board.printBoard(); // Wyświetl planszę po ruchu
                        } else if (!mustContinueCapturing && !board.hasCaptureMoves(currentTurn) && board.isValidMove(move, false)) { // Sprawdź zwykły ruch
                            board.makeMove(move);
                            isPieceSelected = false;
                            selectedField = nullptr;
                            currentTurn = (currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
                            currentPlayer = (currentTurn == PieceColor::WHITE) ? player1 : player2;
                            turnIndicator.setFillColor(currentTurn == PieceColor::WHITE ? sf::Color::White : sf::Color::Black); // Zmień kolor wskaźnika tury
                            updateCaptureIndicator(); // Aktualizuj wskaźnik bicia
                            board.printBoard(); // Wyświetl planszę po ruchu
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
                         (field->getState() == FieldState::BLACK_PIECE && currentTurn == PieceColor::BLACK) ||
                         (field->getState() == FieldState::WHITE_QUEEN && currentTurn == PieceColor::WHITE) ||
                         (field->getState() == FieldState::BLACK_QUEEN && currentTurn == PieceColor::BLACK))) {
                        if (!mustContinueCapturing) {
                            isPieceSelected = true;
                            selectedPosition = sf::Vector2i((int)(field->getPosition().x / board.getFieldSideLength()), (int)(field->getPosition().y / board.getFieldSideLength()));
                            selectedField = field;
                            std::cout << "Piece selected at position: (" << selectedPosition.x << ", " << selectedPosition.y << ")\n";
                        }
                    } else {
                        std::cout << "No piece selected or wrong turn at position: (" << mousePos.x << ", " << mousePos.y << ")\n";
                    }
                }
            }
        }
    }
    if (currentPlayer == player2 && currentTurn == PieceColor::BLACK) {
        std::cout << "Bot is making a move..." << std::endl;
        while (currentTurn == PieceColor::BLACK) {
            Move botMove = player2->getMove(board);
            std::cout << "Bot move: (" << botMove.startPosition.x << ", " << botMove.startPosition.y << ") -> ("
                      << botMove.endPositions.back().x << ", " << botMove.endPositions.back().y << ")" << std::endl;
            board.makeMove(botMove);
            if (!board.mustContinueCapturing) {
                currentTurn = PieceColor::WHITE;
                currentPlayer = player1;
                turnIndicator.setFillColor(sf::Color::White);
            }
            updateCaptureIndicator();
        }
    }
}

void Game::update() {
    // Aktualizacja stanu gry
//    if (isBotGame && currentTurn == PieceColor::BLACK) {
//        Move botMove = player2->getMove(board);
//        board.makeMove(botMove);
//        currentTurn = PieceColor::WHITE;
//        currentPlayer = player1;
//        turnIndicator.setFillColor(sf::Color::White);
//        updateCaptureIndicator();
//    }
}

void Game::updateCaptureIndicator() {
    bool captureMoveAvailable = board.hasCaptureMoves(currentTurn);
    captureIndicator.setFillColor(captureMoveAvailable ? sf::Color::Red : sf::Color::Transparent);
}

void Game::render() {
    window.clear();
    board.draw(window);
    window.draw(turnIndicator); // Dodaj rysowanie wskaźnika tury
    window.draw(captureIndicator); // Dodaj rysowanie wskaźnika bicia
    window.display();
}
