#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(711, 691), "Checkers Game"), currentTurn(PieceColor::WHITE), selectedField(nullptr), isPieceSelected(false), mustContinueCapturing(false), isBotGame(false) {
    board.initialize(); // Inicjalizacja planszy

    // Zapytaj użytkownika, czy chce grać z botem
    std::string input; // Zmienna przechowująca odpowiedź użytkownika
    std::cout << "Czy chcesz grać z botem? (t/n): "; // Zapytanie o grę z botem
    std::cin >> input; // Pobranie odpowiedzi
    if (input == "t") { // Jeśli odpowiedź to "t"
        player1 = new HumanPlayer(PieceColor::WHITE); // Ustaw gracza 1 jako człowieka
        player2 = new Bot(PieceColor::BLACK); // Ustaw gracza 2 jako bota
    } else {
        player1 = new HumanPlayer(PieceColor::WHITE); // Ustaw gracza 1 jako człowieka
        player2 = new HumanPlayer(PieceColor::BLACK); // Ustaw gracza 2 jako człowieka
    }
    currentPlayer = player1; // Ustaw aktualnego gracza na gracza 1

    // Inicjalizacja wskaźnika tury
    turnIndicator.setSize(sf::Vector2f(20, 691)); // Ustawienie wskaźnika na wysokość okna
    turnIndicator.setPosition(691, 0); // Ustawienie wskaźnika na prawo od szachownicy
    turnIndicator.setFillColor(sf::Color::White); // Początkowy kolor dla białego gracza

    // Inicjalizacja wskaźnika bicia
    captureIndicator.setRadius(7.5f); // Średnica 15 pikseli
    captureIndicator.setFillColor(sf::Color::Transparent); // Początkowo ukryty
    captureIndicator.setPosition(691 + 2.5f, 338 - 7.5f); // Ustawienie początkowej pozycji
}

void Game::run() {
    while (window.isOpen()) { // Dopóki okno jest otwarte
        handlePlayerInput(); // Obsługa wejścia gracza
        render(); // Renderowanie planszy
    }
}

bool Game::hasCaptureMoves() const {
    for (int y = 0; y < 8; ++y) { // Dla każdego rzędu
        for (int x = 0; x < 8; ++x) { // Dla każdej kolumny
            FieldState state = board.getFieldAt(sf::Vector2i(x, y))->getState(); // Pobierz stan pola
            if ((state == FieldState::WHITE_PIECE && currentTurn == PieceColor::WHITE) ||
                (state == FieldState::BLACK_PIECE && currentTurn == PieceColor::BLACK)) { // Sprawdź, czy pionek należy do aktualnego gracza
                if (board.canCapture(sf::Vector2i(x, y))) { // Sprawdź, czy pionek może wykonać bicie
                    return true; // Zwróć true
                }
            }
        }
    }
    return false; // Zwróć false
}

void Game::handlePlayerInput() {
    sf::Event event; // Zmienna przechowująca zdarzenie
    while (window.pollEvent(event)) { // Pobierz zdarzenie z okna
        if (event.type == sf::Event::Closed) // Sprawdź, czy zdarzenie to zamknięcie okna
            window.close(); // Zamknij okno

        if (event.type == sf::Event::MouseButtonPressed) { // Sprawdź, czy zdarzenie to naciśnięcie przycisku myszy
            if (event.mouseButton.button == sf::Mouse::Left) { // Sprawdź, czy naciśnięto lewy przycisk myszy
                sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Pobierz pozycję myszy

                if (isPieceSelected) { // Jeśli wybrano pionka
                    // Ruch pionka
                    Field* endField = board.getFieldContainingPoint(mousePos); // Pobierz pole, na które kliknięto
                    if (endField) { // Sprawdź, czy pole istnieje
                        sf::Vector2i endPosition((int)(endField->getPosition().x / board.getFieldSideLength()), (int)(endField->getPosition().y / board.getFieldSideLength())); // Pobierz pozycję pola
                        Move move(selectedPosition, endPosition); // Utwórz ruch
                        bool isCapture = board.isValidMove(move, true); // Sprawdź ruch bicia
                        if (isCapture) { // Sprawdź, czy ruch jest biciem
                            board.makeMove(move); // Wykonaj ruch
                            if (!board.mustContinueCapturing) { // Sprawdź, czy gracz musi kontynuować bicie
                                isPieceSelected = false; // Zresetuj isPieceSelected
                                selectedField = nullptr; // Zresetuj selectedField
                                mustContinueCapturing = false; // Reset mustContinueCapturing
                                currentTurn = (currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE; // Zmień turę
                                currentPlayer = (currentTurn == PieceColor::WHITE) ? player1 : player2; // Zmień aktualnego gracza
                                turnIndicator.setFillColor(currentTurn == PieceColor::WHITE ? sf::Color::White : sf::Color::Black); // Zmień kolor wskaźnika tury
                                updateCaptureIndicator(); // Aktualizuj wskaźnik bicia
                            } else { // Jeśli gracz musi kontynuować bicie
                                selectedPosition = endPosition; // Ustaw selectedPosition na pozycję końcową
                                selectedField = endField; // Ustaw selectedField na pole końcowe
                                mustContinueCapturing = true; // Ustaw mustContinueCapturing na true
                                board.setMustContinueCapturing(true); // Aktualizuj stan mustContinueCapturing w Board
                                updateCaptureIndicator(); // Aktualizuj wskaźnik bicia
                            }
                            board.printBoard(); // Wyświetl planszę po ruchu
                        } else if (!mustContinueCapturing && !board.hasCaptureMoves(currentTurn) && board.isValidMove(move, false)) { // Sprawdź zwykły ruch
                            board.makeMove(move); // Wykonaj ruch
                            isPieceSelected = false; // Zresetuj isPieceSelected
                            selectedField = nullptr; // Zresetuj selectedField
                            currentTurn = (currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE; // Zmień turę
                            currentPlayer = (currentTurn == PieceColor::WHITE) ? player1 : player2; // Zmień aktualnego gracza
                            turnIndicator.setFillColor(currentTurn == PieceColor::WHITE ? sf::Color::White : sf::Color::Black); // Zmień kolor wskaźnika tury
                            updateCaptureIndicator(); // Aktualizuj wskaźnik bicia
                            board.printBoard(); // Wyświetl planszę po ruchu
                        } else { // Jeśli ruch jest niepoprawny
                            isPieceSelected = false; // Zresetuj isPieceSelected
                            selectedField = nullptr; // Zresetuj selectedField
                        }
                    }
                } else { // Jeśli nie wybrano pionka
                    // Wybór pionka
                    Field* field = board.getFieldContainingPoint(mousePos); // Pobierz pole, na które kliknięto
                    if (field && field->getState() != FieldState::EMPTY &&
                        ((field->getState() == FieldState::WHITE_PIECE && currentTurn == PieceColor::WHITE) ||
                         (field->getState() == FieldState::BLACK_PIECE && currentTurn == PieceColor::BLACK) ||
                         (field->getState() == FieldState::WHITE_QUEEN && currentTurn == PieceColor::WHITE) ||
                         (field->getState() == FieldState::BLACK_QUEEN && currentTurn == PieceColor::BLACK))) { // Sprawdź, czy pole istnieje i czy należy do aktualnego gracza
                        if (!mustContinueCapturing) { // Sprawdź, czy gracz musi kontynuować bicie
                            isPieceSelected = true; // Ustaw isPieceSelected na true
                            selectedPosition = sf::Vector2i((int)(field->getPosition().x / board.getFieldSideLength()), (int)(field->getPosition().y / board.getFieldSideLength())); // Ustaw selectedPosition na pozycję wybranego pola
                            selectedField = field; // Ustaw selectedField na pole, które wybrano
                            std::cout << "Piece selected at position: (" << selectedPosition.x << ", " << selectedPosition.y << ")\n";
                        }
                    } else { // Jeśli pole nie istnieje lub nie należy do aktualnego gracza
                        std::cout << "No piece selected or wrong turn at position: (" << mousePos.x << ", " << mousePos.y << ")\n";
                    }
                }
            }
        }
    }
    // Dla bota
    if (dynamic_cast<Bot*>(currentPlayer) && currentTurn == PieceColor::BLACK) { // Jeśli aktualny gracz to bot i tura czarnego gracza
        std::cout << "Bot is making a move..." << std::endl;
        while (currentTurn == PieceColor::BLACK) { // Dopóki tura czarnego gracza
            Move botMove = player2->getMove(board); // Pobierz ruch bota
            std::cout << "Bot move: (" << botMove.startPosition.x << ", " << botMove.startPosition.y << ") -> ("
                      << botMove.endPositions.back().x << ", " << botMove.endPositions.back().y << ")" << std::endl;
            board.makeMove(botMove); // Wykonaj ruch bota
            if (!board.mustContinueCapturing) { // Jeśli bot nie musi kontynuować bicia
                currentTurn = PieceColor::WHITE; // Zmień turę na białego gracza
                currentPlayer = player1; // Zmień aktualnego gracza na białego gracza
                turnIndicator.setFillColor(sf::Color::White); // Zmień kolor wskaźnika tury na biały
            }
            updateCaptureIndicator(); // Aktualizuj wskaźnik bicia
        }
    }
}

void Game::updateCaptureIndicator() {
    bool captureMoveAvailable = board.hasCaptureMoves(currentTurn); // Sprawdź, czy gracz może wykonać bicie
    captureIndicator.setFillColor(captureMoveAvailable ? sf::Color::Red : sf::Color::Transparent); // Ustaw kolor wskaźnika bicia
}

void Game::render() {
    window.clear(); // Wyczyść okno
    board.draw(window); // Dodaj rysowanie planszy
    window.draw(turnIndicator); // Dodaj rysowanie wskaźnika tury
    window.draw(captureIndicator); // Dodaj rysowanie wskaźnika bicia
    window.display(); // Wyświetl okno
}
