#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "moneda.h"
#include "portofoliu.h"

int main() {
    srand(time(0));

    Portofoliu portofoliu(10000.0f);

    portofoliu.adaugaMoneda(Moneda("Bitcoin", "BTC", 65432.15f));
    portofoliu.adaugaMoneda(Moneda("Ethereum", "ETH", 3245.80f));
    portofoliu.adaugaMoneda(Moneda("Litecoin", "LTC", 98.65f));
    portofoliu.adaugaMoneda(Moneda("Ripple", "XRP", 0.612f));
    portofoliu.adaugaMoneda(Moneda("Cardano", "ADA", 0.482f));

    int optiune;
    do {
        std::cout << "\n=== SIMULATOR INVESTITII CRYPTO ===\n";
        std::cout << "Sold disponibil: $" << portofoliu.getSold() << "\n\n";
        std::cout << "1. Cumpara\n";
        std::cout << "2. Vinde\n";
        std::cout << "3. Portofoliu\n";
        std::cout << "4. Piata\n";
        std::cout << "5. Salveaza\n";
        std::cout << "6. Iesire\n";
        std::cout << "Alege o optiune: ";
        std::cin >> optiune;

        switch (optiune) {
            case 1: {
                std::string simbol;
                int cantitate;

                std::cout << "Simbol moneda: ";
                std::cin >> simbol;
                std::cout << "Cantitate: ";
                std::cin >> cantitate;

                RezultatCumparare rezultat = portofoliu.cumpara(simbol, cantitate);
                switch (rezultat) {
                    case RezultatCumparare::SUCCES:
                        std::cout << "Cumparare reusita!\n";
                        break;
                    case RezultatCumparare::FONDURI_INSUFICIENTE:
                        std::cout << "Fonduri insuficiente!\n";
                        break;
                    case RezultatCumparare::MONEDA_INEXISTENTA:
                        std::cout << "Moneda nu exista!\n";
                        break;
                }
                break;
            }
            case 2: {
                std::string simbol;
                int cantitate;

                std::cout << "Simbol moneda: ";
                std::cin >> simbol;
                std::cout << "Cantitate: ";
                std::cin >> cantitate;

                RezultatVanzare rezultat = portofoliu.vinde(simbol, cantitate);
                switch (rezultat) {
                    case RezultatVanzare::SUCCES:
                        std::cout << "Vanzare reusita!\n";
                        break;
                    case RezultatVanzare::CANTITATE_INSUFICIENTA:
                        std::cout << "Cantitate insuficienta!\n";
                        break;
                    case RezultatVanzare::MONEDA_INEXISTENTA:
                        std::cout << "Moneda nu exista!\n";
                        break;
                }
                break;
            }
            case 3: {
                std::cout << "\n== Stare curenta ==\n";
                std::cout << "Sold: " << portofoliu.getSold() << std::endl;
                std::cout << "Monede detinute\n";
                
                const std::vector<Moneda>& monede = portofoliu.getMonede();
                for (int i = 0; i < monede.size(); i++) {
                    std::cout << "\n----------------\n";
                    std::cout << "Nume: " << monede[i].getNume() << "\n";
                    std::cout << "Simbol: " << monede[i].getSimbol() << "\n";
                    std::cout << "Pret: " << monede[i].getPret() << "\n";
                    std::cout << "Cantitate: " << monede[i].getCantitate() << "\n";
                    std::cout << "----------------\n";
                }
                break;
            }
            case 4: {
                portofoliu.actualizeazaPiata();
                
                std::cout << "\n== Piata actualizata ==\n";
                const std::vector<Moneda>& monede = portofoliu.getMonede();
                for (int i = 0; i < monede.size(); i++) {
                    std::cout << monede[i].getNume() << " (" << monede[i].getSimbol() << "): $"
                        << monede[i].getPret() << "\n";
                }
                break;
            }
            case 5: {
                std::ofstream fisierPortofoliu("portofoliu.txt");
                fisierPortofoliu << portofoliu.getSold() << "\n";
                fisierPortofoliu << portofoliu.getSoldInitial() << "\n";

                const std::vector<Moneda>& monede = portofoliu.getMonede();
                for (int i = 0; i < monede.size(); i++) {
                    fisierPortofoliu << monede[i].getSimbol() << "|"
                                     << monede[i].getPret() << "|"
                                     << monede[i].getCantitate() << "\n";
                }
                fisierPortofoliu.close();

                std::ofstream fisierIstoric("istoric.txt");
                const std::vector<Tranzactie>& tranzactii = portofoliu.getIstoric();
                for (int i = 0; i < tranzactii.size(); i++) {
                    int tipNumeric = static_cast<int>(tranzactii[i].tip);
                    fisierIstoric << tipNumeric << "|"
                                  << tranzactii[i].simbol << "|"
                                  << tranzactii[i].pretUnitar << "|"
                                  << tranzactii[i].cantitate << "\n";
                }
                fisierIstoric.close();

                std::cout << "Portofoliu salvat cu succes!\n";
                break;
            }
            case 6:
                std::cout << "La revedere!\n";
                break;
            default:
                std::cout << "Optiune invalida.\n";
        }
    } while (optiune != 6);

    return 0;
}