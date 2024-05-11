#include "filmy.h"

std::string filmy::getTytul() {
    return tytul;
}

void filmy::setTytul(string Tytul) {
    this->tytul = Tytul;
}

float filmy::getOcena() {
    return ocena;
}

void filmy::setOcena(float Ocena) {
    this->ocena = Ocena;
}
