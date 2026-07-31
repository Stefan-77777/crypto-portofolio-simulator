#ifndef TRANZACTIE_H
#define TRANZACTIE_H

#include <string>
#include <ctime>

enum class TipTranzactie { CUMPARARE, VANZARE };

struct Tranzactie {
    int cantitate;
    float pretUnitar;
    std::string simbol;
    TipTranzactie tip;
    std::time_t timp;
};

#endif