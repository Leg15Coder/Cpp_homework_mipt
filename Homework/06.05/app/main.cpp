#include <iostream>
#include <string>
#include <dlfcn.h>

typedef const char* (*test_func_t)();

int main() {
    std::cout << "Choose library version to load (1 or 2): ";
    std::string version;
    std::cin >> version;

    std::string lib_path;
    if (version == "1") {
        lib_path = "./lib_v1/libversion1.so";
    } else if (version == "2") {
        lib_path = "./lib_v2/libversion2.so";
    } else {
        std::cerr << "Invalid version selected." << std::endl;
        return 1;
    }

    void* handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return 1;
    }

    dlerror();

    test_func_t test_func = (test_func_t) dlsym(handle, "test");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'test': " << dlsym_error << std::endl;
        dlclose(handle);
        return 1;
    }

    std::cout << "Successfully called function from " << lib_path << std::endl;
    std::cout << "Output: " << test_func() << std::endl;

    dlclose(handle);

    return 0;
}
