rm -rf build
rm -rf gcm.cache
mkdir -p build

g++ -std=c++23 -fmodules-ts -x c++-system-header cassert
g++ -std=c++23 -fmodules-ts -x c++-system-header cmath
g++ -std=c++23 -fmodules-ts -x c++-system-header compare
g++ -std=c++23 -fmodules-ts -x c++-system-header stdexcept
g++ -std=c++23 -fmodules-ts -x c++-system-header iostream
g++ -std=c++23 -fmodules-ts -x c++-system-header numeric
g++ -std=c++23 -fmodules-ts -x c++-system-header sstream
g++ -std=c++23 -fmodules-ts -x c++-system-header string
g++ -std=c++23 -fmodules-ts -x c++-system-header optional
g++ -std=c++23 -fmodules-ts -x c++-system-header variant
g++ -std=c++23 -fmodules-ts -x c++-system-header vector

g++ -std=c++23 -fmodules-ts exception.cxx rational.cxx rational_impl.cxx 06.02.cpp -Wall -Wextra -Wpedantic -fsanitize=address,undefined -o build/module.out && ./build/module.out

rm -rf build
rm -rf gcm.cache
