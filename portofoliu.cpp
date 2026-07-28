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

bool Portofoliu::cumpara(std::string simbol, int cantitate) {
    Moneda* m = gasesteMoneda(simbol);
    if (m == nullptr) {
        return false;
    }

    float cost = m->getPret() * cantitate;
    if (cost > sold) {
        return false;
    }

    sold -= cost;
    m->adaugaCantitate(cantitate);

    Tranzactie t;
    t.tip = TipTranzactie::CUMPARARE;
    t.cantitate = cantitate;
    t.simbol = simbol;
    t.pretUnitar = m->getPret();
    tranzactii.push_back(t);

    return true;
}

bool Portofoliu::vinde(std::string simbol, int cantitate) {
    Moneda* m = gasesteMoneda(simbol);
    if (m == nullptr) {
        return false;
    }

    if (!m->scadeCantitate(cantitate)) {
        return false;
    }

    float profit = m->getPret() * cantitate;
    sold += profit;

    Tranzactie t;
    t.tip = TipTranzactie::VANZARE;
    t.cantitate = cantitate;
    t.simbol = simbol;
    t.pretUnitar = m->getPret();
    tranzactii.push_back(t);

    return true;
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
