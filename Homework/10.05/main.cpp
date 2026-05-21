#include <cstddef>
#include <cstdint>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include "hash_functions.hpp"

auto make_strings(std::size_t size_1, std::size_t size_2)
{
    std::set<std::string> strings;
    std::string string(size_2, '_');
    std::uniform_int_distribution distribution(97, 122);
    std::default_random_engine engine;

    while (std::size(strings) < size_1)
    {
        for (auto &element : string)
        {
            element = distribution(engine);
        }
        strings.insert(string);
    }
    return strings;
}

int main()
{
    using HashFunction = std::function<std::uint32_t(const std::string&)>;
    std::vector<std::pair<std::string, HashFunction>> hash_functions = {
        {"RSHash", Hashes::RSHash},
        {"JSHash", Hashes::JSHash},
        {"PJWHash", Hashes::PJWHash},
        {"ELFHash", Hashes::ELFHash},
        {"BKDRHash", Hashes::BKDRHash},
        {"SDBMHash", Hashes::SDBMHash},
        {"DJBHash", Hashes::DJBHash},
        {"DEKHash", Hashes::DEKHash},
        {"APHash", Hashes::APHash}};

    std::ofstream data_file("collision_data.csv");
    data_file << "Function,HashedStrings,Collisions\n";

    const size_t max_strings = 100000;
    const size_t step = 1000;
    const size_t string_length = 10;

    for (const auto& func_pair : hash_functions)
    {
        for (size_t i = step; i <= max_strings; i += step)
        {
            auto strings = make_strings(i, string_length);
            std::set<std::uint32_t> hashes;
            for (const auto& s : strings)
            {
                hashes.insert(func_pair.second(s));
            }
            size_t collisions = strings.size() - hashes.size();
            data_file << func_pair.first << "," << i << "," << collisions << "\n";
        }
    }
}
