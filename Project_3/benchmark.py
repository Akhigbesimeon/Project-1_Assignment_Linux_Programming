import time
import random
from pure_python import sum_of_squares_py
import fast_calc

def run_benchmark():
    # Generate a large list of floats
    data_size = 10_000_000
    print(f"Generating dataset of {data_size} floats...")
    data = [random.random() for _ in range(data_size)]

    print("Benchmarking Pure Python...")
    start_py = time.time()
    result_py = sum_of_squares_py(data)
    end_py = time.time()
    time_py = end_py - start_py

    print("Benchmarking C Extension...")
    start_c = time.time()
    result_c = fast_calc.sum_of_squares(data)
    end_c = time.time()
    time_c = end_c - start_c

    print("\n-- Benchmark Results --")
    print(f"Pure Python Time:  {time_py:.4f} seconds")
    print(f"C Extension Time:  {time_c:.4f} seconds")
    print(f"Speedup Factor:    {time_py / time_c:.2f}x")
    
    # Verify results match
    assert abs(result_py - result_c) < 1e-9, "Results do not match!"

if __name__ == "__main__":
    run_benchmark()
