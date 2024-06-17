#ifndef PROJEKT_3_MINMAXALGORITHM_H
#define PROJEKT_3_MINMAXALGORITHM_H

#include "Board.h"
#include "Move.h"
#include <vector>
#include <iostream>

/*
 * Klasa implementująca algorytm min-max
 * Wartość planszy jest obliczana na podstawie różnicy pomiędzy ilością pionków gracza a ilością pionków przeciwnika
 * Im większa różnica, tym lepsza plansza
 * Algorytm przeszukuje drzewo gry o określonej głębokości i wybiera najlepszy ruch
 */
class MinMaxAlgorithm {
public:
    /*
     * Metoda zwracająca najlepszy ruch dla danego stanu planszy
     * @param board - plansza
     * @param depth - głębokość przeszukiwania drzewa gry
     * @return najlepszy ruch
     */
    Move calculateBestMove(const Board& board, int depth);

    /*
     * Metoda obliczająca wartość planszy
     * @param board - plansza
     * @return wartość planszy
     */
    int evaluateBoard(const Board& board);

    /*
     * Metoda implementująca algorytm min-max
     * @param board - plansza
     * @param depth - głębokość przeszukiwania drzewa gry
     * @param isMaximizingPlayer - czy gracz maksymalizujący
     * @return wartość planszy
     */
    int minMax(Board& board, int depth, bool isMaximizingPlayer);

private:

    /*
     * Metoda zwracająca wszystkie możliwe ruchy dla danego koloru
     * @param board - plansza
     * @param color - kolor pionków
     * @return wektor możliwych ruchów
     */
    std::vector<Move> getAllPossibleMoves(const Board& board, PieceColor color);

    /*
     * Metoda zwracająca wszystkie możliwe pozycje końcowe dla danego pionka
     * @param board - plansza
     * @param startPos - pozycja początkowa
     * @param isCapturing - czy pionek zbija
     * @return wektor możliwych pozycji końcowych
     */
    std::vector<sf::Vector2i> getPossibleEndPositions(const Board& board, const sf::Vector2i& startPos, bool isCapturing);
};

#endif //PROJEKT_3_MINMAXALGORITHM_H
