#include <SFML/Graphics.hpp>

int main() {
    // Utwórz okno gry
    sf::RenderWindow window(sf::VideoMode(691, 691), "Checkers Game");

    // Załaduj tekstury
    sf::Texture boardTexture;
    if (!boardTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/board.jpg")) {
        // Obsługa błędu
        return -1;
    }
    sf::Texture blackPieceTexture;
    if (!blackPieceTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/black.png")) {
        // Obsługa błędu
        return -1;
    }
    sf::Texture whitePieceTexture;
    if (!whitePieceTexture.loadFromFile("E:/studia/sem 4/Projektowanie_i_Analiza_Algorytmow/projekt 3/assets/images/white.png")) {
        // Obsługa błędu
        return -1;
    }

    // Utwórz sprity
    sf::Sprite boardSprite;
    boardSprite.setTexture(boardTexture);

    sf::Sprite blackPieceSprite;
    blackPieceSprite.setTexture(blackPieceTexture);
    blackPieceSprite.setPosition(40, 40); // Przykładowa pozycja
    blackPieceSprite.setScale(0.30f, 0.30f); // Skala dla dopasowania do pola 78x78

    sf::Sprite whitePieceSprite;
    whitePieceSprite.setTexture(whitePieceTexture);
    whitePieceSprite.setPosition(618, 618); // Przykładowa pozycja
    whitePieceSprite.setScale(0.36f, 0.36f); // Skala dla dopasowania do pola 78x78

    // Główna pętla gry
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(boardSprite);
        window.draw(blackPieceSprite);
        window.draw(whitePieceSprite);
        window.display();
    }

    return 0;
}