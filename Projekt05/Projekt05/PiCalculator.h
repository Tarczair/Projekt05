/**
 * @file PiCalculator.h
 * @brief Definicja klasy PiCalculator.
 */

#ifndef PICALCULATOR_H
#define PICALCULATOR_H

 /**
  * @class PiCalculator
  * @brief Klasa odpowiedzialna za obliczenia matematyczne liczby PI.
  * * Klasa udostepnia metody do rownoleglego obliczania wartosci PI
  * z wykorzystaniem biblioteki standardowej watkow C++11.
  */
class PiCalculator {
public:
    /**
     * @brief Metoda obliczajaca PI.
     * @param num_steps Liczba iteracji algorytmu.
     * @param num_threads Liczba watkow roboczych.
     * @return double Wynik obliczen.
     */
    double calculate(long long num_steps, int num_threads);
};

#endif