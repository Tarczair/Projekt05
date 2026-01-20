/**
 * @file Projekt05.cpp
 * @brief Glowny modul programu wykonawczego.
 * * Odpowiada za:
 * - Parsowanie argumentow linii komend.
 * - Inicjalizacje procesu obliczeniowego.
 * - Precyzyjny pomiar czasu rzeczywistego wykonania zadania.
 */

#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include "PiCalculator.h"

 /**
  * @brief Funkcja main.
  * * Przyjmuje argumenty:
  * 1. Liczba krokow (long long)
  * 2. Liczba watkow (int)
  * * Wynik czasowy jest wypisywany na standardowe wyjscie w formacie zmiennoprzecinkowym.
  */

using namespace std;

int main(int argc, char* argv[]) {

    /**
    * Sprawdzamy, czy podano odpowiednia liczbe argumentow
    * Oczekujemy: ./Projekt05 <liczba_krokow> <liczba_watkow>
    */

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

    /**
    * Pomiar czasu START
    */

    auto start_time = chrono::high_resolution_clock::now();

    /**
    * Obliczenia
    */
    double pi = calculator.calculate(steps, threads);

    /**
    * Pomiar czasu STOP
    */
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    /**
    * Wypisujemy TYLKO czas na koncu, aby Python latwo to odczytal.
    * Python bedzie czytal ostatnia linie wyjscia.
    */

    cout << fixed << setprecision(6) << elapsed.count() << endl;

    return 0;
}