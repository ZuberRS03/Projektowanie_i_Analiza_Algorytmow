#ifndef PROJEKT_3_GAME_H
#define PROJEKT_3_GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Bot.h"

/*
 * Klasa reprezentująca grę w warcaby.
 * Zawiera logikę gry, obsługę wejścia, aktualizację i renderowanie.
 * Zawiera również wskaźniki na obiekty graczy, aktualnego gracza, planszę oraz okno gry.
 * Zawiera również zmienne pomocnicze takie jak wybrany pionek, czy gracz musi kontynuować bicie.
 */
class Game {
public:
    // Konstruktor
    Game();

    /*
     * Metoda uruchamiająca grę.
     * Zawiera główną pętlę gry.
     * @param void
     * @return void
     */
    void run();

private:
    /*
     * Metoda sprawdzająca, czy aktualny gracz ma możliwe ruchy bicia.
     * @param void
     * @return bool - true, jeśli gracz ma możliwe ruchy bicia, false w przeciwnym wypadku.
     */
    bool hasCaptureMoves() const;

    /*
     * Metoda obsługująca wejście gracza.
     * @param void
     * @return void
     */
    void handlePlayerInput();

    /*
     * Metoda aktualizująca stan gry.
     * @param void
     * @return void
     */
    void render();

    sf::RenderWindow window; // Okno gry
    Board board; // Plansza
    Player* currentPlayer; // Aktualny gracz
    Player* player1; // Gracz 1
    Player* player2; // Gracz 2

    PieceColor currentTurn; // Aktualna tura
    Field* selectedField; // Wybrane pole
    bool isPieceSelected; // Czy wybrano pionek
    sf::Vector2i selectedPosition; // Pozycja wybranego pionka
    bool mustContinueCapturing; // Czy gracz musi kontynuować bicie

    sf::RectangleShape turnIndicator; // Wskaźnik tury
    sf::CircleShape captureIndicator; // Wskaźnik bicia
    void updateCaptureIndicator(); // Deklaracja funkcji aktualizującej wskaźnik bicia

    bool isBotGame; // Flaga gry z botem
};

#endif //PROJEKT_3_GAME_H
