# Crypto Portfolio Simulator

Un program in C++ care simuleaza tranzactii cu monede virtuale folosind bani fictivi, cu preturi care fluctueaza aleatoriu. Proiect construit incremental, cu accent pe design orientat-obiect si separarea logicii de interfata.

## Features

- **Cumparare / Vanzare** — tranzactii pe 5 monede predefinite (BTC, ETH, LTC, XRP, ADA), cu validare de fonduri si cantitate disponibila
- **Piata reactiva** — preturile fluctueaza aleatoriu (+/- 5%) la fiecare actualizare
- **Portofoliu** — afisare sold, monede detinute, si calcul de profit/pierdere fata de investitia initiala
- **Istoric tranzactii** — fiecare tranzactie retine tip, simbol, cantitate, pret si timestamp; submeniu dedicat cu sortare crescatoare/descrescatoare dupa data
- **Persistenta completa** — salvare si incarcare a starii portofoliului si a istoricului in fisiere text (`portofoliu.txt`, `istoric.txt`)

## Arhitectura

Proiectul e structurat in 3 fisiere `.h`/`.cpp`, fiecare cu o singura responsabilitate:

- **`Moneda`** (class) — nume, simbol, pret, cantitate detinuta; date private cu getteri si metode controlate (`adaugaCantitate`, `scadeCantitate`, `actualizeazaPret`)
- **`Tranzactie`** (struct) — inregistrare istorica imutabila: tip (`enum class TipTranzactie`), simbol, cantitate, pret, timestamp
- **`Portofoliu`** (class) — sold, sold initial, lista de monede si istoric de tranzactii; logica de business completa (`cumpara`, `vinde`, `calculeazaProfit`, `actualizeazaPiata`), fara niciun `cout` in interior — toata afisarea se face din `main.cpp`

Alegerea struct vs class: `Tranzactie` e doar date (fara comportament), celelalte doua au logica si stare protejata.

## Skills exersate

- Struct vs class, incapsulare (date private + interfata publica)
- Pointeri (`Moneda*`) si referinte (`Moneda&`) — diferenta intre copie si acces direct la date reale
- `enum class` pentru siguranta la compilare (`TipTranzactie`, `RezultatCumparare`, `RezultatVanzare`)
- Numere aleatoare (`rand()`, `srand()`) pentru simularea pietei
- Fisiere text (`ifstream`/`ofstream`), parsare cu `stringstream` si delimitatori custom
- `std::sort` cu lambda pentru sortare custom
- `std::time_t` / `ctime()` pentru timestamp-uri

## Compilare

```bash
g++ main.cpp moneda.cpp portofoliu.cpp -o simulator.exe -std=c++17
```

## Roadmap

- Interfata grafica (GUI)