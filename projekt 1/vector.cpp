#include "vector.h"

void Vector::dodajFilm(std::string tytul, float ocena) {
    filmy film;
    film.setTytul(tytul);
    film.setOcena(ocena);
    vector1.push_back(film);
}

void Vector::usuwanieFilmu(int ktoryFilm) {
    vector1.erase(vector1.begin() + ktoryFilm);
}

void Vector::wyswietlFilmy() {
    for(int i = 0; i < vector1.size(); i++){
        std::cout << vector1[i].getTytul() << " " << vector1[i].getOcena() << std::endl;
    }
}

float Vector::getOcenaFloat(int ktoryFilm) {
    return vector1[ktoryFilm].getOcena();
}

// Funkcja scalająca dla MergeSort
void scalanie(std::vector<filmy> &vector1, int pierwsza, int srodek, int ostatnia){
    int i, j, k;
    int n1 = srodek - pierwsza + 1;
    int n2 =  ostatnia - srodek;

    std::vector<filmy> L(n1), R(n2); // Tworzymy dwie pomocnicze tablice

    // Kopiujemy dane do tablic pomocniczych
    for (i = 0; i < n1; i++)
        L[i] = vector1[pierwsza + i];
    for (j = 0; j < n2; j++)
        R[j] = vector1[srodek + 1+ j];

    i = 0;
    j = 0;
    k = pierwsza;

    // Scalanie tablic pomocniczych z powrotem do tablicy głównej
    while (i < n1 && j < n2)
    {
        if (L[i].getOcena() <= R[j].getOcena())
        {
            vector1[k] = L[i];
            i++;
        }
        else
        {
            vector1[k] = R[j];
            j++;
        }
        k++;
    }

    // Kopiowanie pozostałych elementów z L[]
    while (i < n1)
    {
        vector1[k] = L[i];
        i++;
        k++;
    }

    // Kopiowanie pozostałych elementów z R[]
    while (j < n2)
    {
        vector1[k] = R[j];
        j++;
        k++;
    }
}

void Vector::MergeSort(int pierwsza, int ostatnia) {
    if(pierwsza < ostatnia){
        int srodek = (pierwsza + ostatnia) / 2; // Obliczanie środka

        //podział na dwie części
        MergeSort(pierwsza, srodek);
        MergeSort(srodek + 1, ostatnia);

        scalanie(vector1, pierwsza, srodek, ostatnia); // Scalanie dwóch posortowanych części
    }
}

void Vector::QuickSort(int pierwsza, int ostatnia) {
    int i = pierwsza;
    int j = ostatnia;
    float x = vector1[(pierwsza + ostatnia) / 2].getOcena(); // Wybieramy element środkowy jako punkt odniesienia(pivot)
    do{
        while(vector1[i].getOcena() < x) // Szukamy elementu większego lub równego x od lewej
            i++;
        while(vector1[j].getOcena() > x) // Szukamy elementu mniejszego lub równego od x od prawej
            j--;

        if(i <= j){
            std::swap(vector1[i], vector1[j]); // Zamieniamy miejscami elementy
            i++;
            j--;
        }
    } while(i <= j);

    // Rekurencyjnie sortujemy lewą i prawą część
    if(pierwsza < j)
        QuickSort(pierwsza, j);
    if(i < ostatnia)
        QuickSort(i, ostatnia);
}

// Funkcja QuickSort dodtosowana do sortowania kubełkowego
void QuickSortB(std::vector<filmy>::iterator pierwsza, std::vector<filmy>::iterator ostatnia) {
    std::vector<filmy>::iterator i = pierwsza; // Ustawiamy iterator i na pierwszy element
    std::vector<filmy>::iterator j = ostatnia; // Ustawiamy iterator j na ostatni element

    float x = (*(pierwsza + (ostatnia - pierwsza) / 2)).getOcena(); // Wybieramy element środkowy jako punkt odniesienia

    /*
     * Szukamy elementu większego lub równego x od lewej
     * Szukamy elementu mniejszego lub równego od x od prawej
     * Zamieniamy miejscami elementy
     */
    do{
        while((*i).getOcena() < x)
            i++;
        while((*j).getOcena() > x)
            j--;
        if(i <= j){
            std::swap(*i, *j);
            i++;
            j--;
        }
    } while(i <= j);

    // Rekurencyjnie sortujemy lewą i prawą część
    if(pierwsza < j)
        QuickSortB(pierwsza, j);
    if(i < ostatnia)
        QuickSortB(i, ostatnia);
}

void Vector::BucketSort(int n) {
    std::vector<std::vector<filmy>> bucket(n + 1); // Tworzymy n kubełków

    /*
     * Dla każdego elementu z wektora, obliczamy indeks kubełka
     * i dodajemy element do odpowiedniego kubełka
     */
    for(int i = 0; i < n; i++){
        int index = static_cast<int>(n * (vector1[i].getOcena() / 10)); // Normalizacja oceny, dodatkowo zabezpieczone przez static_cast<int>
        if (index > n) {
            index = n; // Zabezpieczenie przed przekroczeniem zakresu
        }
        bucket[index].push_back(vector1[i]); // Dodajemy element do kubełka
    }

    //Sortujemy każdy kubełek za pomocą QuickSort
    for(int i = 0; i <= n; i++){
        if (!bucket[i].empty()) {
            // Sortuj tylko niepuste wiadra
            QuickSortB(bucket[i].begin(), bucket[i].end() - 1);
        }
    }
    vector1.clear(); // Usuń wszystkie elementy z vector1

    // Łączymy wszystkie kubełki z powrotem do vector1
    for(int i = 0; i <= n; i++){
        for(auto& film : bucket[i]){
            vector1.push_back(film); // Dodajemy filmy z powrotem do vector1 za pomocą push_back zamiast indeksowania
        }
    }

}

bool Vector::czyPosortowane() {
    for(int i = 0; i < vector1.size() - 1; i++){
        if(vector1[i].getOcena() > vector1[i + 1].getOcena())
            return false;
    }
    return true;
}

float Vector::mediana() {
    if(vector1.size() % 2 == 0){
        return (vector1[vector1.size() / 2].getOcena() + vector1[vector1.size() / 2 - 1].getOcena()) / 2;
    }
    else{
        return vector1[vector1.size() / 2].getOcena();
    }
}

float Vector::srednia() {
    float suma = 0;
    for(int i = 0; i < vector1.size(); i++){
        suma += vector1[i].getOcena();
    }
    return suma / vector1.size();
}

int Vector::size() {
    return vector1.size();
}