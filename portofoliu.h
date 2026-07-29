#ifndef PORTOFOLIU_H
#define PORTOFOLIU_H

#include<iostream>
#include<vector>
#include "moneda.h"
#include "tranzactie.h"

enum class RezultatCumparare {
    SUCCES,
    MONEDA_INEXISTENTA,
    FONDURI_INSUFICIENTE
};

enum class RezultatVanzare {
    SUCCES,
    MONEDA_INEXISTENTA,
    CANTITATE_INSUFICIENTA
};

class Portofoliu {
    public:
        Portofoliu(float soldInitial);

        RezultatCumparare cumpara(std::string simbol, int cantitate);
        RezultatVanzare vinde(std::string simbol, int cantitate);
        float calculeazaProfit() const;

        float getSold() const;
        float getSoldInitial() const;
        const std::vector<Moneda>& getMonede() const;
        const std::vector<Tranzactie>& getIstoric() const;

        void adaugaMoneda(Moneda moneda);
        void actualizeazaPiata();

    private:
        float sold;
        float soldInitial;
        std::vector<Moneda> monede;
        std::vector<Tranzactie> tranzactii;

        Moneda* gasesteMoneda(std::string simbol);
};

#endif