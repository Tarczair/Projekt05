#include "PiCalculator.h"
#include <thread>
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

double PiCalculator::calculate(long long num_steps, int num_threads) {
    double step = 1.0 / (double)num_steps;

    // Wektor przechowuj¹cy wyniki cz¹stkowe z ka¿dego w¹tku
    // U¿ywamy wektora, aby unikn¹æ wyœcigu danych (data race) przy sumowaniu
    vector<double> partial_sums(num_threads, 0.0);
    vector<thread> threads;

    // Obliczamy ile kroków pêtli przypada na jeden w¹tek
    long long steps_per_thread = num_steps / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        // Uruchamiamy w¹tek z wyra¿eniem lambda
        // Przekazujemy zmienne przez wartoœæ [=] oraz wektor wyników przez referencjê [&partial_sums]
        threads.emplace_back([=, &partial_sums]() {
            long long start = i * steps_per_thread;
            // Ostatni w¹tek bierze na siebie ewentualn¹ resztê z dzielenia
            long long end = (i == num_threads - 1) ? num_steps : (i + 1) * steps_per_thread;

            double local_sum = 0.0;

            // Pêtla ca³kowania numerycznego (metoda prostok¹tów z punktem œrodkowym)
            for (long long j = start; j < end; ++j) {
                double x = (j + 0.5) * step;
                local_sum += 4.0 / (1.0 + x * x);
            }

            // Zapisz wynik cz¹stkowy w odpowiednim miejscu wektora
            partial_sums[i] = local_sum;
            });
    }

    // Czekamy na zakoñczenie wszystkich w¹tków (join)
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Sumujemy wyniki cz¹stkowe
    double total_sum = 0.0;
    for (double sum : partial_sums) {
        total_sum += sum;
    }

    return total_sum * step;
}