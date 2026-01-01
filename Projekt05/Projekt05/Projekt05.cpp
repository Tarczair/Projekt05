#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "PiCalculator.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Sprawdzamy, czy podano odpowiednią liczbę argumentów
    // Oczekujemy: ./Projekt05 <liczba_krokow> <liczba_watkow>
    if (argc != 3) {
        cerr << "Uzycie: " << argv[0] << " <liczba_krokow> <liczba_watkow>" << endl;
        return 1;
    }

    long long steps = 0;
    int threads = 0;

    try {
        steps = stoll(argv[1]);
        threads = stoi(argv[2]);
    }
    catch (...) {
        cerr << "Blad parsowania argumentow." << endl;
        return 1;
    }

    if (steps <= 0 || threads <= 0) {
        return 1; // Bledne dane
    }

    PiCalculator calculator;

    // Pomiar czasu START
    auto start_time = chrono::high_resolution_clock::now();

    // Obliczenia
    double pi = calculator.calculate(steps, threads);

    // Pomiar czasu STOP
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    // Wypisujemy TYLKO czas na końcu, aby Python łatwo to odczytał.
    // Python bedzie czytal ostatnia linie wyjscia.
    cout << fixed << setprecision(6) << elapsed.count() << endl;

    return 0;
}