#ifndef PROJEKT_3_BOT_H
#define PROJEKT_3_BOT_H

#include "Player.h"
#include "MinMaxAlgorithm.h"
#include "Move.h"

/*
 * Klasa reprezentująca bota
 * Bot dziedziczy po klasie Player
 * Bot korzysta z algorytmu min-max do wyboru najlepszego ruchu
 */
class Bot : public Player {
public:
    // Konstruktor klasy Bot
    Bot(PieceColor color);

    /*
     * Funkcja zwracająca najlepszy ruch dla bota
     * @param board - referencja do planszy
     * @return Move - najlepszy ruch dla bota
     */
    Move getMove(const Board& board) override;

private:
    // Obiekt klasy MinMaxAlgorithm
    MinMaxAlgorithm minMaxAlgorithm;
};

#endif //PROJEKT_3_BOT_H
