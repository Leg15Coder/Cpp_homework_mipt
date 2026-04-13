#include "hex_converter.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdint>
#include <stdexcept>

int main() {
    std::vector<std::uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF, 0x12, 0x34, 0x56, 0x78};

    std::cout << "Original data: ";
    for(const auto& byte : data) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;

    std::string hex_string = to_hex_string(data);
    std::cout << "As hex string: " << hex_string << std::endl;

    try {
        std::vector<std::uint8_t> converted_data = from_hex_string(hex_string);
        std::cout << "Converted back: ";
        for(const auto& byte : converted_data) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        std::cout << std::dec << std::endl;

        if (data == converted_data) {
            std::cout << "Conversion successful!" << std::endl;
        } else {
            std::cout << "Conversion failed!" << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error during conversion: " << e.what() << std::endl;
    }
}
