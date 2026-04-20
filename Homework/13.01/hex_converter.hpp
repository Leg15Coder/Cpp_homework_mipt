#ifndef HEX_CONVERTER_HPP
#define HEX_CONVERTER_HPP

#include <vector>
#include <string>
#include <cstdint>

std::string to_hex_string(const std::vector<std::uint8_t>& bytes);

std::vector<std::uint8_t> from_hex_string(const std::string& hex_str);

#endif // HEX_CONVERTER_HPP
