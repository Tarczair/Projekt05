/**
 * @file PiCalculator.cpp
 * @brief Implementacja metod klasy PiCalculator.
 */

#include "PiCalculator.h"
#include <thread>
#include <vector>

 /**
  * @brief Glowna metoda obliczeniowa wykorzystujaca metode prostokatow.
  * * Algorytm opiera sie na calkowaniu numerycznym funkcji \f$ f(x) = \frac{4}{1+x^2} \f$.
  * Praca jest dzielona na @p num_threads watkow, gdzie kazdy operuje na wlasnej
  * sumie czastkowej w celu unikniecia problemu wyscigu (data race).
  * * @param num_steps Liczba krokow (precyzja calki).
  * @param num_threads Liczba uzytych watkow.
  * @return double Przyblizona wartosc liczby PI.
  */
using namespace std;

double PiCalculator::calculate(long long num_steps, int num_threads) {
    double step = 1.0 / (double)num_steps;
    /**
    * Wektor przechowujacy wyniki czastkowe z kazdego watku
    * Uzywamy wektora, aby uniknac wyscigu danych (data race) przy sumowaniu
    */
    vector<double> partial_sums(num_threads, 0.0);
    vector<thread> threads;

    /**
    * Obliczamy ile krokow petli przypada na jeden watek
    */
    long long steps_per_thread = num_steps / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        /**
        * Uruchamiamy watek z wyrazeniem lambda
        * Przekazujemy zmienne przez wartosc [=] oraz wektor wynikow przez referencje [&partial_sums]
        */
        threads.emplace_back([=, &partial_sums]() {
            long long start = i * steps_per_thread;
            /**
            * Ostatni watek bierze na siebie ewentualna reszte z dzielenia
            */
            long long end = (i == num_threads - 1) ? num_steps : (i + 1) * steps_per_thread;

            double local_sum = 0.0;
            /**
            * Petla calkowania numerycznego (metoda prostokatow z punktem srodkowym)
            */

            for (long long j = start; j < end; ++j) {
                double x = (j + 0.5) * step;
                local_sum += 4.0 / (1.0 + x * x);
            }
            /**
            * Zapisz wynik czastkowy w odpowiednim miejscu wektora
            */
            partial_sums[i] = local_sum;
            });
    }

    /**
    * Czekamy na zakonczenie wszystkich watkow (join)
    */
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    /**
    * Sumujemy wyniki czastkowe
    */

    double total_sum = 0.0;
    for (double sum : partial_sums) {
        total_sum += sum;
    }

    return total_sum * step;
}