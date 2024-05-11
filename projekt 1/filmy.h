#ifndef PROGRAM_FILMY_H
#define PROGRAM_FILMY_H

#include <iostream>

using namespace std;

class filmy {
protected:

    string tytul;
    float ocena;

public:


    /*
     * @brief Funkcja ustawiajaca tytul filmu
     * @param Tytul
     * @return brak
    */
    void setTytul(string Tytul);

    /*
     * @brief Funkcja zwracajaca tytul filmu
     * @param brak
     * @return tytul
    */
    string getTytul();

    /*
     * @brief Funkcja ustawiajaca ocene filmu
     * @param Ocena
     * @return brak
    */
    void setOcena(float Ocena);

    /*
     * @brief Funkcja zwracajaca ocene filmu
     * @param brak
     * @return ocena
    */
    float getOcena();

};


#endif //PROGRAM_FILMY_H
