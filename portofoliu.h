#ifndef PORTOFOLIU_H
#define PORTOFOLIU_H

#include<iostream>
#include<vector>
#include "moneda.h"
#include "tranzactie.h"

class Portofoliu {
    public:
        Portofoliu(float soldInitial);

        bool cumpara(std::string simbol, int cantitate);
        bool vinde(std::string simbol, int cantitate);
        float calculeazaProfit() const;

        float getSold() const;
        const std::vector<Moneda>& getMonede() const;
        const std::vector<Tranzactie>& getIstoric() const;

        void adaugaMoneda(Moneda moneda);

    private:
        float sold;
        float soldInitial;
        std::vector<Moneda> monede;
        std::vector<Tranzactie> tranzactii;

        Moneda* gasesteMoneda(std::string simbol);
};

#endif