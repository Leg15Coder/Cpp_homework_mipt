#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////

void transform(std::string const & path_1, std::string const & path_2)
{
    std::ifstream in(path_1);
    if (!in.is_open()) return;

    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    
    struct Chunk {
        std::string text;
        bool is_raw;
    };
    std::vector<Chunk> chunks;
    
    auto it = content.begin();
    std::string current_normal;
    
    while (it != content.end()) {
        // Raw string
        if (*it == 'R' && std::next(it) != content.end() && *std::next(it) == '"') {
            if (!current_normal.empty()) {
                chunks.push_back({current_normal, false});
                current_normal.clear();
            }
            
            std::string raw;
            raw += *it++; // R
            raw += *it++; // "
            std::string delimiter;
            while (it != content.end() && *it != '(') {
                delimiter += *it;
                raw += *it++;
            }
            if (it != content.end()) raw += *it++; // (
            
            std::string end_marker = ")" + delimiter + "\"";
            auto end_pos = content.find(end_marker, std::distance(content.begin(), it));
            if (end_pos != std::string::npos) {
                auto end_it = content.begin() + end_pos + end_marker.length();
                raw.append(it, end_it);
                it = end_it;
            }
            chunks.push_back({raw, true});
            continue;
        }

        // Standard string
        if (*it == '"') {
            current_normal += *it++;
            while (it != content.end() && !(*it == '"' && *std::prev(it) != '\\')) {
                current_normal += *it++;
            }
            if (it != content.end()) current_normal += *it++;
            continue;
        }

        // Comments
        if (*it == '/') {
            if (std::next(it) != content.end() && *std::next(it) == '/') {
                while (it != content.end() && *it != '\n') ++it;
                continue;
            } else if (std::next(it) != content.end() && *std::next(it) == '*') {
                std::advance(it, 2);
                while (it != content.end() && !(*it == '/' && *std::prev(it) == '*')) ++it;
                if (it != content.end()) ++it;
                continue;
            }
        }
        
        current_normal += *it++;
    }
    if (!current_normal.empty()) chunks.push_back({current_normal, false});

    std::string full_processed;
    std::vector<bool> is_raw_char;
    for (auto const& c : chunks) {
        full_processed += c.text;
        for (size_t i = 0; i < c.text.size(); ++i) is_raw_char.push_back(c.is_raw);
    }

    std::ofstream out(path_2);
    size_t start = 0;
    while (start < full_processed.size()) {
        size_t end = full_processed.find('\n', start);
        if (end == std::string::npos) end = full_processed.size();
        
        std::string_view line(full_processed.data() + start, end - start);
        
        bool all_whitespace = true;
        bool has_raw = false;
        for (size_t i = start; i < end; ++i) {
            if (!std::isspace(static_cast<unsigned char>(full_processed[i]))) {
                all_whitespace = false;
            }
            if (is_raw_char[i]) has_raw = true;
        }
        
        if (has_raw || !all_whitespace) {
            out << line << "\n";
        }
        
        start = end + 1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto path_1 = "source.cpp";
    auto path_2 = "output.cpp";

    transform(path_1, path_2);

    std::cout << (std::stringstream() << std::ifstream(path_1).rdbuf()).str() << "\n\n\n";           
    std::cout << (std::stringstream() << std::ifstream(path_2).rdbuf()).str() << "\n\n\n";

    std::filesystem::remove(path_2);
}

////////////////////////////////////////////////////////////////////////////////////////////
