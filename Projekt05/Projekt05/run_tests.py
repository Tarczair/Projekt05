# -*- coding: utf-8 -*-
import subprocess
import matplotlib.pyplot as plt
import os
import sys

# Konfiguracja testow
EXECUTABLE = "./Projekt05" 
if os.name == 'nt': 
    EXECUTABLE = "Projekt05.exe"

# Zestaw danych do testow
STEPS_LIST = [100_000_000, 1_000_000_000, 3_000_000_000]
MAX_THREADS = 50

def run_cpp_program(steps, threads):
    """Uruchamia program C++ i zwraca czas wykonania jako float"""
    try:
        result = subprocess.run(
            [EXECUTABLE, str(steps), str(threads)],
            capture_output=True,
            text=True,
            check=True
        )
        output_lines = result.stdout.strip().split('\n')
        time_str = output_lines[-1] 
        return float(time_str)
    except Exception as e:
        return None

def main():
    if not os.path.exists(EXECUTABLE):
        print(f"Blad: Nie znaleziono pliku {EXECUTABLE}. Skompiluj kod C++!")
        return

    results = {steps: [] for steps in STEPS_LIST}
    threads_range = range(1, MAX_THREADS + 1)

    print(f"Start testow: watki 1-{MAX_THREADS}...")

    for steps in STEPS_LIST:
        print(f"\nTestowanie dla {steps} krokow...")
        for t in threads_range:
            time_taken = run_cpp_program(steps, t)
            if time_taken is not None:
                results[steps].append(time_taken)
                sys.stdout.write(f"\rWatki: {t}/{MAX_THREADS} | Czas: {time_taken:.4f}s")
                sys.stdout.flush()
            else:
                results[steps].append(0)

    print("\n\nGenerowanie wykresu...")

    plt.figure(figsize=(12, 8))
    for steps in STEPS_LIST:
        times = results[steps]
        label_str = f'Kroki: {steps:,}'
        plt.plot(threads_range, times, marker='o', markersize=3, label=label_str)

    plt.title('Zaleznosc czasu obliczen PI od liczby watkow')
    plt.xlabel('Liczba watkow')
    plt.ylabel('Czas obliczen (sekundy)')
    plt.grid(True, which='both', linestyle='--', linewidth=0.5)
    plt.legend()
    
    output_filename = "wykres_wydajnosci.png"
    plt.savefig(output_filename)
    print(f"Wykres zapisano do pliku: {output_filename}")
    plt.show()

if __name__ == "__main__":
    main()