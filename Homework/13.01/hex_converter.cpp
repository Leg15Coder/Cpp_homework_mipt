#include "hex_converter.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::string to_hex_string(const std::vector<std::uint8_t>& bytes) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (const auto& byte : bytes) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    return ss.str();
}

static std::uint8_t hex_char_to_val(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    throw std::invalid_argument("Invalid hex character");
}

std::vector<std::uint8_t> from_hex_string(const std::string& hex_str) {
    if (hex_str.length() % 2 != 0) {
        throw std::invalid_argument("Hex string must have an even number of characters");
    }

    std::vector<std::uint8_t> bytes;
    bytes.reserve(hex_str.length() / 2);

    for (size_t i = 0; i < hex_str.length(); i += 2) {
        std::uint8_t high = hex_char_to_val(hex_str[i]);
        std::uint8_t low = hex_char_to_val(hex_str[i + 1]);
        bytes.push_back((high << 4) | low);
    }

    return bytes;
}
