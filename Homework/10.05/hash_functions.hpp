#pragma once

#include <string>
#include <cstdint>

namespace Hashes
{
    std::uint32_t RSHash(const std::string& str)
    {
        std::uint32_t b = 378551;
        std::uint32_t a = 63689;
        std::uint32_t hash = 0;
        for (char i : str)
        {
            hash = hash * a + i;
            a = a * b;
        }
        return hash;
    }

    std::uint32_t JSHash(const std::string& str)
    {
        std::uint32_t hash = 1315423911;
        for (char i : str)
        {
            hash ^= ((hash << 5) + i + (hash >> 2));
        }
        return hash;
    }

    std::uint32_t PJWHash(const std::string& str)
    {
        const std::uint32_t BitsInUnsignedInt = (std::uint32_t)(sizeof(std::uint32_t) * 8);
        const std::uint32_t ThreeQuarters = (std::uint32_t)((BitsInUnsignedInt * 3) / 4);
        const std::uint32_t OneEighth = (std::uint32_t)(BitsInUnsignedInt / 8);
        const std::uint32_t HighBits = (std::uint32_t)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
        std::uint32_t hash = 0;
        std::uint32_t test = 0;
        for (char i : str)
        {
            hash = (hash << OneEighth) + i;
            if ((test = hash & HighBits) != 0)
            {
                hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
            }
        }
        return hash;
    }

    std::uint32_t ELFHash(const std::string& str)
    {
        std::uint32_t hash = 0;
        std::uint32_t x = 0;
        for (char i : str)
        {
            hash = (hash << 4) + i;
            if ((x = hash & 0xF0000000L) != 0)
            {
                hash ^= (x >> 24);
            }
            hash &= ~x;
        }
        return hash;
    }

    std::uint32_t BKDRHash(const std::string& str)
    {
        std::uint32_t seed = 131;
        std::uint32_t hash = 0;
        for (char i : str)
        {
            hash = (hash * seed) + i;
        }
        return hash;
    }

    std::uint32_t SDBMHash(const std::string& str)
    {
        std::uint32_t hash = 0;
        for (char i : str)
        {
            hash = i + (hash << 6) + (hash << 16) - hash;
        }
        return hash;
    }

    std::uint32_t DJBHash(const std::string& str)
    {
        std::uint32_t hash = 5381;
        for (char i : str)
        {
            hash = ((hash << 5) + hash) + i;
        }
        return hash;
    }

    std::uint32_t DEKHash(const std::string& str)
    {
        std::uint32_t hash = static_cast<std::uint32_t>(str.length());
        for (char i : str)
        {
            hash = ((hash << 5) ^ (hash >> 27)) ^ i;
        }
        return hash;
    }

    std::uint32_t APHash(const std::string& str)
    {
        std::uint32_t hash = 0xAAAAAAAA;
        for (size_t i = 0; i < str.length(); i++)
        {
            hash ^= ((i & 1) == 0) ? ((hash << 7) ^ str[i] * (hash >> 3)) : (~((hash << 11) + (str[i] ^ (hash >> 5))));
        }
        return hash;
    }

}
