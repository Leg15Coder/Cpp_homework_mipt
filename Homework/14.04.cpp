#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <numeric>
#include <chrono>
#include <future>


long long monte_carlo_worker(long long iterations) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    long long count_inside = 0;
    for (long long i = 0; i < iterations; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        if (x * x + y * y <= 1.0) {
            ++count_inside;
        }
    }
    return count_inside;
}

int main() {
    const long long total_iterations = 100'000'000;
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 2;

    std::cout << "Starting Monte Carlo Pi estimation with " << total_iterations 
              << " iterations using " << num_threads << " threads...\n";

    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<std::future<long long>> futures;
    long long iterations_per_thread = total_iterations / num_threads;

    for (unsigned int i = 0; i < num_threads; ++i) {
        long long iter = (i == num_threads - 1) 
                         ? (total_iterations - iterations_per_thread * i) 
                         : iterations_per_thread;
        
        futures.push_back(std::async(std::launch::async, monte_carlo_worker, iter));
    }

    long long total_inside = 0;
    for (auto& f : futures) {
        total_inside += f.get();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    double pi_estimate = 4.0 * static_cast<double>(total_inside) / total_iterations;

    std::cout.precision(10);
    std::cout << "Pi estimate: " << pi_estimate << "\n";
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
}
