#pragma once
#include <vector>

class PiCalculator {
public:
    /*
     * Oblicza przybli¿on¹ wartoœæ PI metod¹ ca³kowania numerycznego.
     * @param num_steps Iloœæ podzia³ów przedzia³u (dok³adnoœæ).
     * @param num_threads Iloœæ w¹tków do wykorzystania.
     * @return Obliczona wartoœæ PI.
     */
    double calculate(long long num_steps, int num_threads);
};