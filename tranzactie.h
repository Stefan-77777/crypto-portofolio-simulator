#ifndef TRANZACTIE_H
#define TRANZACTIE_H

#include<string>

enum class TipTranzactie { CUMPARARE, VANZARE };

struct Tranzactie {
    int cantitate;
    float pretUnitar;
    std::string simbol;
    TipTranzactie tip;
};

#endif