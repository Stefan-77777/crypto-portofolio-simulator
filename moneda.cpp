#include "moneda.h"
#include<string>
#include<cstdlib>

Moneda::Moneda(std::string nume, std::string simbol, float pretInitial) {
    this->nume = nume;
    this->simbol = simbol;
    this->pret = pretInitial;
    this-> cantitate = 0;
}

float Moneda::getPret() const {
    return pret;
}

int Moneda::getCantitate() const {
    return cantitate;
}

std::string Moneda::getNume() const {
    return nume;
}

std::string Moneda::getSimbol() const {
    return simbol;
}

void Moneda::adaugaCantitate(int cantitate) {
    this->cantitate += cantitate;
}

bool Moneda::scadeCantitate(int cantitate) {
    if (this->cantitate >= cantitate) {
        this->cantitate -= cantitate;
        return true;
    } else {
        return false;
    }
}

void Moneda::actualizeazaPret() {
    int variatieFactor = (rand() % 11) - 5;
    float factor = 1.0f + (variatieFactor / 100.0f);
    pret = pret * factor;
}