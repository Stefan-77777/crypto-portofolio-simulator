#include "portofoliu.h"
#include "tranzactie.h"
#include<string>

Portofoliu::Portofoliu(float soldInitial) {
    sold = soldInitial;
    this->soldInitial = soldInitial;
}

Moneda* Portofoliu::gasesteMoneda(std::string simbol) {
    for (Moneda& m : monede) {
        if (m.getSimbol() == simbol) {
            return &m;
        }
    }
    return nullptr;
}

RezultatCumparare Portofoliu::cumpara(std::string simbol, int cantitate) {
    Moneda* m = gasesteMoneda(simbol);
    if (m == nullptr) {
        return RezultatCumparare::MONEDA_INEXISTENTA;
    }

    float cost = m->getPret() * cantitate;
    if (cost > sold) {
        return RezultatCumparare::FONDURI_INSUFICIENTE;
    }

    sold -= cost;
    m->adaugaCantitate(cantitate);

    Tranzactie t;
    t.tip = TipTranzactie::CUMPARARE;
    t.cantitate = cantitate;
    t.simbol = simbol;
    t.pretUnitar = m->getPret();
    tranzactii.push_back(t);

    return RezultatCumparare::SUCCES;
}

RezultatVanzare Portofoliu::vinde(std::string simbol, int cantitate) {
    Moneda* m = gasesteMoneda(simbol);
    if (m == nullptr) {
        return RezultatVanzare::MONEDA_INEXISTENTA;
    }

    if (!m->scadeCantitate(cantitate)) {
        return RezultatVanzare::CANTITATE_INSUFICIENTA;
    }

    float profit = m->getPret() * cantitate;
    sold += profit;

    Tranzactie t;
    t.tip = TipTranzactie::VANZARE;
    t.cantitate = cantitate;
    t.simbol = simbol;
    t.pretUnitar = m->getPret();
    tranzactii.push_back(t);

    return RezultatVanzare::SUCCES;
}

float Portofoliu::calculeazaProfit() const {
    float valoareCurenta = sold;
    for (const Moneda& m : monede) {
        valoareCurenta += m.getCantitate() * m.getPret();
    }
    return valoareCurenta - soldInitial;
}

float Portofoliu::getSold() const {
    return sold;
}

const std::vector<Moneda>& Portofoliu::getMonede() const {
    return monede;
}

const std::vector<Tranzactie>& Portofoliu::getIstoric() const {
    return tranzactii;
}

void Portofoliu::adaugaMoneda(Moneda moneda) {
    monede.push_back(moneda);
}

void Portofoliu::actualizeazaPiata() {
    for (Moneda& m : monede) {
        m.actualizeazaPret();
    }
}

float Portofoliu::getSoldInitial() const {
    return soldInitial;
}