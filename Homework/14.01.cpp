#include <iostream>
#include <thread>
#include <exception>
#include <stdexcept>
#include <string>

std::exception_ptr thread_exception = nullptr;

void worker_thread() {
    try {
        std::cout << "Worker thread: Starting work...\n";
        throw std::runtime_error("Error occurred in the worker thread!");
    } catch (...) {
        thread_exception = std::current_exception();
        std::cout << "Worker thread: Exception captured and stored.\n";
    }
}

int main() {
    std::cout << "Main thread: Starting worker thread...\n";
    std::thread t(worker_thread);

    t.join();

    std::cout << "Main thread: Worker thread finished.\n";

    if (thread_exception) {
        try {
            std::rethrow_exception(thread_exception);
        } catch (const std::exception& e) {
            std::cerr << "Main thread: Caught rethrown exception: " << e.what() << "\n";
        } catch (...) {
            std::cerr << "Main thread: Caught an unknown rethrown exception.\n";
        }
    } else {
        std::cout << "Main thread: No exception was thrown in the worker thread.\n";
    }
}
