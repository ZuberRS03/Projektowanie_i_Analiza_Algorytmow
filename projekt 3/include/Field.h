#ifndef PROJEKT_3_FIELD_H
#define PROJEKT_3_FIELD_H

#include <SFML/Graphics.hpp>

/*
 * Enum reprezentujący kolor bierki.
 */
enum class PieceColor {
    WHITE,
    BLACK
};

/*
 * Enum reprezentujący stan pola na planszy.
 */
enum class FieldState {
    EMPTY,
    WHITE_PIECE,
    BLACK_PIECE,
    WHITE_QUEEN,
    BLACK_QUEEN
};

/*
 * Klasa reprezentująca pojedyncze pole na planszy.
 * Pole może być puste, zawierać białą lub czarną bierkę, białą lub czarną damkę.
 */
class Field {
public:
    // Konstruktor
    Field();

    /*
     * Metoda zwracająca stan pola.
     * @param void
     * @return FieldState
     */
    FieldState getState() const;

    /*
     * Metoda ustawiająca stan pola.
     * @param FieldState state
     * @return void
     */
    void setState(FieldState state);

    /*
     * Metoda ustawiająca pozycję pola.
     * @param const sf::Vector2f& position
     * @return void
     */
    void setPosition(const sf::Vector2f& position);

    /*
     * Metoda zwracająca pozycję pola.
     * @param void
     * @return sf::Vector2f
     */
    sf::Vector2f getPosition() const;

    /*
     * Metoda ustawiająca długość boku pola.
     * @param float length
     * @return void
     */
    void setSideLength(float length);

    /*
     * Metoda zwracająca długość boku pola.
     * @param void
     * @return float
     */
    float getSideLength() const;

    /*
     * Metoda sprawdzająca, czy pole zawiera punkt.
     * @param const sf::Vector2i& point
     * @return bool
     */
    bool contains(const sf::Vector2i& point) const;

    /*
     * Metoda rysująca pole na oknie.
     * @param sf::RenderWindow& window
     * @return void
     */
    void draw(sf::RenderWindow& window);


private:
    FieldState state; // Stan pola
    sf::Vector2f position; // Pozycja pola
    float sideLength; // Długość boku pola
    sf::Sprite sprite; // Sprite pola

    // Statyczne tekstury
    static sf::Texture whitePieceTexture; // Biały pionek
    static sf::Texture blackPieceTexture; // Czarny pionek
    static sf::Texture whiteQueenTexture; // Biała damka
    static sf::Texture blackQueenTexture; // Czarna damka

};

#endif //PROJEKT_3_FIELD_H
