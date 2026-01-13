#include <iostream>
#include <chrono>
#include <iomanip>
#include "PiCalculator.h"

int main() {
    long long steps;
    int threads;

    std::cout << "=== Obliczanie liczby PI metoda calkowania ===" << std::endl;
    std::cout << "Podaj ilosc krokow (np. 100000000): ";
    if (!(std::cin >> steps)) return 1;

    std::cout << "Podaj ilosc watkow (np. 1 - 50): ";
    if (!(std::cin >> threads)) return 1;

    if (steps <= 0 || threads <= 0) {
        std::cerr << "Bledne dane wejsciowe. Liczby musza byc dodatnie." << std::endl;
        return 1;
    }

    PiCalculator calculator;

    std::cout << "Rozpoczynam obliczenia..." << std::endl;

    // Pomiar czasu START
    auto start_time = std::chrono::high_resolution_clock::now();

    // Wywołanie obliczeń
    double pi = calculator.calculate(steps, threads);

    // Pomiar czasu STOP
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Wypisanie wyników
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Obliczone PI: " << pi << std::endl;
    std::cout << "Wzorcowe PI:  3.141592653589793" << std::endl;
    std::cout << "Czas trwania: " << std::fixed << std::setprecision(6) << elapsed.count() << " sekund" << std::endl;
    std::cout << "Uzyte watki:  " << threads << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    return 0;
}