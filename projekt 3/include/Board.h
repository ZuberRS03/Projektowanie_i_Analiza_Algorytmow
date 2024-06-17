#ifndef PROJEKT_3_BOARD_H
#define PROJEKT_3_BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Field.h"
#include "Move.h"

/*
 * Clasa Reprezentująca planszę do gry
 * Zawiera tablicę pól, na których znajdują się pionki
 * Zawiera metody do sprawdzania poprawności ruchów, wykonywania ruchów, rysowania planszy
 */
class Board {
public:
    // Konstruktor planszy
    Board();

    /*
     * Metoda inicjalizująca planszę
     * Ustawia pionki na odpowiednich polach
     * @param void
     * @return void
     */
    void initialize();

    /*
     * Metoda sprawdzająca czy dany ruch jest poprawny
     * @param const Move& move - ruch do sprawdzenia
     * @param bool isCapturing - czy ruch jest ruchem bicia
     * @return bool - czy ruch jest poprawny
     */
    bool isValidMove(const Move& move, bool isCapturing = false) const;

    /*
     * Metoda sprawdzająca czy dany pionek może wykonać bicie
     * @param const sf::Vector2i& position - pozycja pionka
     * @return bool - czy pionek może wykonać bicie
     */
    bool canCapture(const sf::Vector2i& position) const;

    /*
     * Metoda wykonująca ruch
     * @param const Move& move - ruch do wykonania
     * @return void
     */
    void makeMove(const Move& move);

    /*
     * Metoda rysująca planszę
     * @param sf::RenderWindow& window - okno, na którym ma być narysowana plansza
     * @return void
     */
    void draw(sf::RenderWindow& window);

    /*
     * Metoda zwracająca pole planszy na danej pozycji
     * @param const sf::Vector2i& position - pozycja pola
     * @return Field* - wskaźnik na pole
     */
    Field* getFieldAt(const sf::Vector2i& position) const;

    /*
     * Metoda zwracająca pole planszy zawierające dany punkt
     * @param const sf::Vector2i& point - punkt
     * @return Field* - wskaźnik na pole
     */
    Field* getFieldContainingPoint(const sf::Vector2i& point) const;

    /*
     * Metoda zwracająca długość boku pola w pikselach
     * @param void
     * @return float - długość boku pola
     */
    float getFieldSideLength() const;

    /*
     * Metoda sprawdzająca czy dany kolor może wykonać ruch bicia
     * @param PieceColor color - kolor pionków
     * @return bool - czy dany kolor może wykonać ruch bicia
     */
    bool hasCaptureMoves(PieceColor color) const;

    /*
     * Metoda ustawiająca flagę kontynuacji bicia
     * @param bool value - wartość flagi
     * @return void
     */
    void setMustContinueCapturing(bool value);

    /*
     * Metoda sprawdzająca czy dana pozycja znajduje się na planszy
     * @param const sf::Vector2i& position - pozycja
     * @return bool - czy pozycja znajduje się na planszy
     */
    bool isInsideBoard(const sf::Vector2i& position) const;

    /*
     * Metoda wyświetlająca planszę w konsoli
     * @param void
     * @return void
     */
    void printBoard() const;

    // Flaga kontynuacji bicia
    bool mustContinueCapturing;
private:
    Field grid[8][8]; // Tablica pól planszy
    sf::Texture boardTexture; // Tekstura planszy
    sf::Sprite boardSprite; // Sprite planszy
    float fieldSideLength; // Długość boku pola w pikselach
};


#endif //PROJEKT_3_BOARD_H
