#ifndef PROGRAM_VECTOR_H
#define PROGRAM_VECTOR_H

#include <iostream>
#include <vector>
#include "filmy.h"

class Vector {
private:
    std::vector<filmy> vector1;

public:
    //konstruktor
    Vector() {}

    /*
     * @brief Funkcja dodajaca film do wektora
     * @param tytul, ocena
     * @return brak
    */
    void dodajFilm(std::string tytul, float ocena);

    /*
     * @brief Funkcja usuwajaca film z wektora
     * @param ktoryFilm
     * @return brak
    */
    void usuwanieFilmu(int ktoryFilm);

    /*
     * @brief Funkcja wyswietlajaca filmy z wektora
     * @param brak
     * @return brak
    */
    void wyswietlFilmy();

    /*
     * @brief Funkcja zwracajaca ocene filmu z wektora
     * @param ktoryFilm
     * @return ocena
    */
    float getOcenaFloat(int ktoryFilm);

    /*
     * @brief Funkcja sortujaca wektor metoda sortowania przez scalanie
     * @param pierwsza, ostatnia
     * @return brak
    */
    void MergeSort(int pierwsza, int ostatnia);

    /*
     * @brief Funkcja sortujaca wektor metoda sortowania szybkiego
     * @param pierwsza, ostatnia
     * @return brak
    */
    void QuickSort(int pierwsza, int ostatnia);

    /*
     * @brief Funkcja sortujaca wektor metoda sortowania kubełkowego
     * @param ileLiczb
     * @return brak
    */
    void BucketSort(int ileLiczb);

    /*
     * @brief Funkcja sprawdzajaca czy wektor jest posortowany prawidłowo
     * @param brak
     * @return czyPosortowane
    */
    bool czyPosortowane();

    /*
     * @brief Funkcja zwracajaca mediana z wektora
     * @param brak
     * @return mediana
    */
    float mediana();

    /*
     * @brief Funkcja zwracajaca srednia z wektora
     * @param brak
     * @return srednia
    */
    float srednia();

    /*
     * @brief Funkcja zwracajaca rozmiar wektora
     * @param brak
     * @return size
    */
    int size();

};


#endif //PROGRAM_VECTOR_H
