#ifndef MONEDA_H
#define MONEDA_H

#include<string>

class Moneda {
    public:
        Moneda(std::string nume, std::string simbol, float pretInitial);

        void actualizeazaPret();
        void adaugaCantitate(int cantitate);
        bool scadeCantitate(int cantitate);

        float getPret() const;
        int getCantitate() const;
        std::string getNume() const;
        std::string getSimbol() const;

    private:
        std::string nume;
        std::string simbol;
        float pret;
        int cantitate;
};

#endif