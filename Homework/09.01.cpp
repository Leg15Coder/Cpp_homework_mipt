#include <iostream>
#include <string>
#include <source_location>

#ifndef NDEBUG

class Tracer {
public:
    Tracer(const std::string& function_name, const std::source_location& location = std::source_location::current())
        : function_name_(function_name), location_(location) {
        
        std::cout << "Entering function: " << function_name_ << " (" << location_.file_name() << ":" << location_.line() << ")" << std::endl;
    }

    ~Tracer() {
        std::cout << "Exiting function: " << function_name_ << " (" << location_.file_name() << ":" << location_.line() << ")" << std::endl;
    }

private:
    std::string function_name_;
    std::source_location location_;
};

#define trace Tracer tracer_macro_obj(__func__);

#else // NDEBUG

#define trace do {} while (0);

#endif // NDEBUG

void myFunction() {
    trace;
    std::cout << "Inside myFunction" << std::endl;
}

void anotherFunction(int value) {
    trace;
    std::cout << "Inside anotherFunction with value: " << value << std::endl;
}

int main() {
    trace;
    std::cout << "Inside main" << std::endl;
    myFunction();
    anotherFunction(42);
}
