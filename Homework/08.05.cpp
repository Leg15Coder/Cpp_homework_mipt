#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <string>
#include <cmath>
#include <cassert>
#include <iomanip>


template <typename D = std::chrono::duration<double>>
class Timer {
public:
    Timer(std::string const & scope) : m_scope(scope), running(false) {}

    ~Timer()
	{
        if (running) {
            stop();
        }
		std::cout << m_scope << " : " << std::fixed << std::setprecision(6) << average() << "\n";
	}

    auto elapsed() const
	{
		return std::chrono::duration_cast < D > (clock_t::now() - m_begin);
	}

    void start() {
        if (running) {
            throw std::logic_error("Timer is already running.");
        }
        running = true;
        m_begin = clock_t::now();
    }

    void stop() {
        if (!running) {
            throw std::logic_error("Timer is not running.");
        }
        auto end_time = clock_t::now();
        durations.push_back(std::chrono::duration_cast<D>(end_time - m_begin));
        running = false;
    }

    double average() const {
        if (durations.empty()) {
            return 0.0;
        }

        D total_duration(0);
        for(const auto& d : durations) {
            total_duration += d;
        }
        
        return (total_duration / durations.size()).count();
    }

private:
    using clock_t = std::chrono::steady_clock;

    bool running;
    clock_t::time_point m_begin;
    std::string m_scope;
    std::vector<D> durations;
};

auto calculate(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
	}

	return x;
}

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

int main() {
    Timer timer("main : timer");

    assert(equal(calculate(1'000'000), 1'000'000));

    for (int i = 0; i < 5; ++i) {
        try {
            timer.start();
            std::this_thread::sleep_for(std::chrono::milliseconds(50 + i * 10));
            timer.stop();
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    double avg_time = timer.average();
    std::cout << "Average time: " << avg_time << " seconds.\n";

    try {
        timer.start();
        timer.start();
    } catch (const std::logic_error& e) {
        std::cerr << "Caught expected exception: " << e.what() << '\n';
        try {
            timer.stop(); 
        } catch(const std::logic_error& stop_e) {}
    }

    try {
        timer.stop();
    } catch (const std::logic_error& e) {
        std::cerr << "Caught expected exception: " << e.what() << '\n';
    }
}
