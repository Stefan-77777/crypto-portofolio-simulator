#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "moneda.h"
#include "portofoliu.h"

int main() {
    srand(time(0));

    Portofoliu portofoliu(10000.0f);

    std::ifstream fisierPortofoliu("portofoliu.txt");

    if (fisierPortofoliu.is_open()) {
        float soldSalvat, soldInitialSalvat;
        fisierPortofoliu >> soldSalvat;
        fisierPortofoliu >> soldInitialSalvat;
        fisierPortofoliu.ignore(); // sare peste \n ramas dupa citirea numerelor

        portofoliu = Portofoliu(soldInitialSalvat);
        portofoliu.setSold(soldSalvat);

        std::string linie;
        while (std::getline(fisierPortofoliu, linie)) {
            std::stringstream ss(linie);
            std::string nume, simbol, pretStr, cantitateStr;
            std::getline(ss, nume, '|');
            std::getline(ss, simbol, '|');
            std::getline(ss, pretStr, '|');
            std::getline(ss, cantitateStr, '|');

            Moneda m(nume, simbol, std::stof(pretStr));
            m.adaugaCantitate(std::stoi(cantitateStr));
            portofoliu.adaugaMoneda(m);
        }
        fisierPortofoliu.close();

        std::ifstream fisierIstoric("istoric.txt");
        if (fisierIstoric.is_open()) {
            std::string linieIstoric;
            while (std::getline(fisierIstoric, linieIstoric)) {
                std::stringstream ss(linieIstoric);
                std::string tipStr, simbol, pretStr, cantitateStr, timpStr;
                std::getline(ss, tipStr, '|');
                std::getline(ss, simbol, '|');
                std::getline(ss, pretStr, '|');
                std::getline(ss, cantitateStr, '|');
                std::getline(ss, timpStr, '|');

                Tranzactie t;
                t.tip = static_cast<TipTranzactie>(std::stoi(tipStr));
                t.simbol = simbol;
                t.pretUnitar = std::stof(pretStr);
                t.cantitate = std::stoi(cantitateStr);
                t.timp = std::stoll(timpStr);

                portofoliu.adaugaTranzactie(t);
            }
            fisierIstoric.close();
        }

        std::cout << "Progres incarcat cu succes!\n";
    } else {
        std::cout << "Nu s-a gasit progres salvat, se porneste cu valori implicite.\n";
        portofoliu.adaugaMoneda(Moneda("Bitcoin", "BTC", 65432.15f));
        portofoliu.adaugaMoneda(Moneda("Ethereum", "ETH", 3245.80f));
        portofoliu.adaugaMoneda(Moneda("Litecoin", "LTC", 98.65f));
        portofoliu.adaugaMoneda(Moneda("Ripple", "XRP", 0.612f));
        portofoliu.adaugaMoneda(Moneda("Cardano", "ADA", 0.482f));
    }

    int optiune;
    do {
        std::cout << "\n=== SIMULATOR INVESTITII CRYPTO ===\n";
        std::cout << "Sold disponibil: $" << portofoliu.getSold() << "\n\n";
        std::cout << "1. Cumpara\n";
        std::cout << "2. Vinde\n";
        std::cout << "3. Portofoliu\n";
        std::cout << "4. Piata\n";
        std::cout << "5. Salveaza\n";
        std::cout << "6. Istoric\n";
        std::cout << "0. Iesire\n";
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
                std::cout << "Profit: " << portofoliu.calculeazaProfit() << std::endl;
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
                    fisierPortofoliu << monede[i].getNume() << "|"
                                     << monede[i].getSimbol() << "|"
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
                                  << tranzactii[i].cantitate << "|"
                                  << tranzactii[i].timp << "\n";
                }
                fisierIstoric.close();

                std::cout << "Portofoliu salvat cu succes!\n";
                break;
            }
            case 6: {
                int optiune;
                do {
                    std::cout << "\n== Istoric tranzactii ==\n";
                    std::cout << "1. Crescator (cele mai vechi primele)\n";
                    std::cout << "2. Descrescator (cele mai recente primele)\n";
                    std::cout << "0. Inapoi\n";
                    std::cout << "Alege o optiune: ";
                    std::cin >> optiune;

                    if (optiune == 1 || optiune == 2) {
                        std::vector<Tranzactie> istoricSortat = portofoliu.getIstoric();

                        if (optiune == 1) {
                            std::sort(istoricSortat.begin(), istoricSortat.end(),
                                [](const Tranzactie& a, const Tranzactie& b) {
                                    return a.timp < b.timp;
                                });
                        } else {
                            std::sort(istoricSortat.begin(), istoricSortat.end(),
                                [](const Tranzactie& a, const Tranzactie& b) {
                                    return a.timp > b.timp;
                                });
                        }

                        for (int i = 0; i < istoricSortat.size(); i++) {
                            std::string tipText = (istoricSortat[i].tip == TipTranzactie::CUMPARARE) ? "CUMPARARE" : "VANZARE";
                            std::cout << "\n----------------\n";
                            std::cout << "Tip: " << tipText << "\n";
                            std::cout << "Simbol: " << istoricSortat[i].simbol << "\n";
                            std::cout << "Cantitate: " << istoricSortat[i].cantitate << "\n";
                            std::cout << "Pret: " << istoricSortat[i].pretUnitar << "\n";
                            std::cout << "Data: " << std::ctime(&istoricSortat[i].timp);
                        }
                    }
                } while (optiune != 0);
                break;
            }
            case 0:
                std::cout << "La revedere!\n";
                break;
            default:
                std::cout << "Optiune invalida.\n";
        }
    } while (optiune != 0);

    return 0;
}