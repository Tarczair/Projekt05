#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "PiCalculator.h"

int main(int argc, char* argv[]) {
    // Sprawdzamy, czy podano odpowiednią liczbę argumentów
    // Oczekujemy: ./Projekt05 <liczba_krokow> <liczba_watkow>
    if (argc != 3) {
        std::cerr << "Uzycie: " << argv[0] << " <liczba_krokow> <liczba_watkow>" << std::endl;
        return 1;
    }

    long long steps = 0;
    int threads = 0;

    try {
        steps = std::stoll(argv[1]);
        threads = std::stoi(argv[2]);
    }
    catch (...) {
        std::cerr << "Blad parsowania argumentow." << std::endl;
        return 1;
    }

    if (steps <= 0 || threads <= 0) {
        return 1; // Bledne dane
    }

    PiCalculator calculator;

    // Pomiar czasu START
    auto start_time = std::chrono::high_resolution_clock::now();

    // Obliczenia
    double pi = calculator.calculate(steps, threads);

    // Pomiar czasu STOP
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Wypisujemy TYLKO czas na końcu, aby Python łatwo to odczytał.
    // Python bedzie czytal ostatnia linie wyjscia.
    std::cout << std::fixed << std::setprecision(6) << elapsed.count() << std::endl;

    return 0;
}