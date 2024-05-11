#include <iostream> //do cout, cin
#include <fstream> //do otwierania/zamykania plikow
#include <string> //do stringow
#include <time.h> //do mierzenia czasu
#include <cstdlib>
#include "filmy.h"
#include "vector.h"

using namespace std;
clock_t start, stop;

Vector vector1; //wektor z przechowujący filmy

//funkcja wyswietlajaca menu wyboru sortowania oraz przekazująca wybór
int menu_wyboru_sortowania() {
    int wyborSortowania;
    cout << endl;
    cout << "Wybierz jak posortowac: " << endl;
    cout << "1. MergeSort" << endl;
    cout << "2. QuickSort" << endl;
    cout << "3. Kubelkowe" << endl;
    cout << "Twoj wybor:";
    cin >> wyborSortowania;

    return wyborSortowania;
}
//funkcja odwracajaca stringa
string odwroc_stringa(string tekst){
    int dlugoscTekstu = tekst.length();
    for(int i = 0; i < (dlugoscTekstu/2); i++){
        swap(tekst[i],tekst[dlugoscTekstu - 1 - i]);
    }
    return tekst;
}

//funkcja rozdzielajaca dane z pojedynczej linii z pliku
void rozdzielenie_danych(string liniaTekstu){

    string tytul;
    float ocena;
    string ocenaString = "";
    int dlugoscLiniTekstu = liniaTekstu.length();
    int i = dlugoscLiniTekstu - 1;

    /*
     * Sprawdzanie czy ocena jest podana
     * Ocena jesli wystepuje to sprawdzająć od prawej zawsze zaczyn się na 0
     * Jesli nie ma oceny to sprawdzamy czy jest przecinek
     * W przypadku gdy oceny nie ma to ustawiane jest -1
     */
    while(liniaTekstu[i] != '0' and liniaTekstu[i] != ','){
        i--;
    }
    if(liniaTekstu[i] == '0'){
        while(liniaTekstu[i] != ','){
            ocenaString = ocenaString + liniaTekstu[i];
            i--;
        }
        ocenaString = odwroc_stringa(ocenaString);
        ocena = stof(ocenaString); //konwersja oceny zapisanej jako string na float
    } else if(liniaTekstu[i] == ',') {
        ocena = -1; //ocena nie jest podana więc ustawiamy -1
    }

    //reszta linii to tytul
    for(int j = 0; j <= i; j++){
        tytul = tytul + liniaTekstu[j];
    }

    vector1.dodajFilm(tytul, ocena); //dodanie filmu do wektora
}

//funkcja wczytujaca dane z pliku
void wczytywanie_danych( int ile_danych_wczytac){

    ifstream File;
    File.open("E:/studia/sem 4/Analiza algorytmow/projekt 1/program/projekt2_dane.csv"); //otwarcie pliku z danymi

    string tekst;
    getline(File, tekst); //pierwsza linia z pliku jest pomijana poniewaz zawiera naglowki kolumn

    //wczytywanie danych z pliku linia po linii
    for(int i = 0; i < ile_danych_wczytac; i++){
        getline(File, tekst);
        rozdzielenie_danych(tekst);
    }

    File.close(); //zamkniecie pliku
}

//funkcja usuwajaca puste dane
int usun_puste(Vector& vec) {
    int licznikUsunientych = 0;

    /*
     * Sprawdzanie czy ocena jest równa -1
     * Jesli tak to usuwamy film
     */
    for(int i = 0; i < vec.size();) {
        if(vec.getOcenaFloat(i) == -1) {
            vec.usuwanieFilmu(i);
            licznikUsunientych++;
        } else {
            i++;
        }
    }
    return licznikUsunientych; //zwracamy ilosc usunietych pustych danych
}

int main(){
    int ileDanychWczytac = 0;
    cout << "Ile danych wczytac (max 1010291): ";
    cin >> ileDanychWczytac;

    double czasWczytywania = 0;
    cout << "Wczytywanie danych..." << endl;

    //mierzenie czasu wczytywania danych
    start = clock();
    wczytywanie_danych(ileDanychWczytac);
    stop = clock();

    czasWczytywania = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Dane wczytane" << endl;
    cout << endl;

    double czasUsuwania = 0;
    int ileDanych = ileDanychWczytac;
    cout << "Usuwanie pustych danych..." << endl;

    //mierzenie czasu usuwania pustych danych
    start = clock();
    ileDanych = ileDanychWczytac - usun_puste(vector1);
    stop = clock();

    czasUsuwania = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Puste dane usuniete" << endl;

    cout << endl;
    cout <<"------------------------------------------------------------------------------------------------"<< endl;
    vector1.wyswietlFilmy();
    cout <<"------------------------------------------------------------------------------------------------"<< endl;
    cout << endl;

    //menu wyboru sortowania
    int wyborSortowania = menu_wyboru_sortowania();

    double czasSortowania = 0;

    //wzależności od wyboru sortowania wykonywana jest odpowiednia metoda sortowania
    switch(wyborSortowania){
        case 1:
            //mierzenie czasu sortowania
            start = clock();
            vector1.MergeSort(0, ileDanych - 1);
            stop = clock();

            czasSortowania = (double)(stop - start) / CLOCKS_PER_SEC; //konwersja czasu na sekundy
            break;
        case 2:
            //mierzenie czasu sortowania
            start = clock();
            vector1.QuickSort(0, ileDanych - 1);
            stop = clock();

            czasSortowania = (double)(stop - start) / CLOCKS_PER_SEC; //konwersja czasu na sekundy
            break;
        case 3:
            //mierzenie czasu sortowania
            start = clock();
            vector1.BucketSort(ileDanych);
            stop = clock();

            czasSortowania = (double)(stop - start) / CLOCKS_PER_SEC; //konwersja czasu na sekundy
            break;
        default:
            cout << "Nie ma takiej opcji" << endl;
            break;
    }

    cout << endl;
    cout << "Posortowano" << endl;

    //etykieta na wypadek błędnego wyboru
    sprawdzenie:
    cout << endl;
    cout << "Czy sprawdzic posortowanie? (1 - tak, 0 - nie): ";
    int spr;
    cin >> spr;

    cout << endl;
    cout <<"------------------------------------------------------------------------------------------------"<< endl;
    vector1.wyswietlFilmy();
    cout <<"------------------------------------------------------------------------------------------------"<< endl;
    cout << endl;

    //w zależności od wyboru sprawdzenie czy wektor jest posortowany lub nie
    if(spr == 1){
        if(vector1.czyPosortowane() == true){
            cout << "Posortowane poprwnie" << endl;
        } else{
            cout << "Blad w sortowaniu" << endl;
        }
    } else if(spr == 0){
        cout << endl;
    } else{
        cout << "Nie ma takiej opcji, wybierz \"1\" lub \"0\":" << endl;
        goto sprawdzenie;
    }

    //Wypisanie wyników
    cout << "Czas wczytywania danych: " << czasWczytywania << "s" << endl;
    cout << "Czas usuwania pustych danych: " << czasUsuwania << "s" << endl;
    cout << "Czas sortowania: " << czasSortowania << "s" << endl;

    cout << "Mediana: " << vector1.mediana() << endl;
    cout << "Srednia: " << vector1.srednia() << endl;

    return 0;
}