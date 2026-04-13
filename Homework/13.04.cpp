//////////////////////////////////////////////////////////////////////////////////////

// chapter : Streams

//////////////////////////////////////////////////////////////////////////////////////

// section : Filesystem

//////////////////////////////////////////////////////////////////////////////////////

// content : Iterator std::filesystem::directory_iterator
//
// content : Type std::filesystem::directory_entry
//
// content : Type std::filesystem::file_status
//
// content : Function std::filesystem::is_directory
//
// content : Function std::filesystem::is_regular_file
//
// content : Function std::filesystem::is_symlink
//
// content : Enumeration std::filesystem::perms
//
// content : Function std::filesystem::file_size
//
// content : Iterator std::filesystem::recursive_directory_iterator
//
// content : Clock std::chrono::file_clock

//////////////////////////////////////////////////////////////////////////////////////

// support : ls -la with regex filter

//////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////

auto make_type(std::filesystem::file_status const & status)
{
    if (std::filesystem::is_directory   (status)) { return 'd'; }

    if (std::filesystem::is_regular_file(status)) { return 'f'; }

    if (std::filesystem::is_symlink     (status)) { return 'l'; }

    return '?';
}

//////////////////////////////////////////////////////////////////////////////////////

auto make_permissions(std::filesystem::perms permissions) -> std::string
{
    auto lambda = [permissions](auto x, auto y)
    { 
        return (permissions & x) == std::filesystem::perms::none ? '-' : y;
    };

    return
    {
        lambda(std::filesystem::perms::owner_read,  'r'),

        lambda(std::filesystem::perms::owner_write, 'w'),

        lambda(std::filesystem::perms::owner_exec,  'x') 
    };
}

//////////////////////////////////////////////////////////////////////////////////////

auto size(std::filesystem::path const & path)
{
	auto size = 0uz;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (auto const & entry : std::filesystem::recursive_directory_iterator(path))
		{
			if (!std::filesystem::is_directory(entry.status()))
			{
				size += std::filesystem::file_size(entry);
			}
		}
	}

	return size;
}

//////////////////////////////////////////////////////////////////////////////////////

auto size(std::filesystem::directory_entry const & entry)
{
    auto size = 0uz;

    if (std::filesystem::is_regular_file(entry.status()))
    {
        size = std::filesystem::file_size(entry);
    }
    else
    {
        size = ::size(entry.path());
    }

    std::array < char, 4 > array = { 'B', 'K', 'M', 'G' };

    auto i = 0uz;

    while (i++ < 3 && size >= 1 << 10)
    {
        size /= (1 << 10);
    }

    return (std::stringstream() << size << array[i - 1]).str();
}

//////////////////////////////////////////////////////////////////////////////////////

void show(std::filesystem::path const & path, std::string const & pattern)
{
    try {
        std::regex re(pattern);
        if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
        {
            for (auto const & entry : std::filesystem::directory_iterator(path))
            {
                std::string filename = entry.path().filename().string();
                if (std::regex_search(filename, re))
                {
                    auto time = std::chrono::file_clock::to_sys(entry.last_write_time());
                    auto time_t = std::chrono::system_clock::to_time_t(time);
                    char time_buf[100];
                    std::strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", std::localtime(&time_t));

                    std::cout << "show : entry : "
                              << make_type(entry.status()) << " | "
                              << make_permissions(entry.status().permissions()) << " | "
                              << size(entry) << " | "
                              << time_buf << " | "
                              << filename << "\n";
                }
            }
        }
    } catch (const std::regex_error& e) {
        std::cerr << "Regex error: " << e.what() << "\n";
    }
}

//////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    std::string pattern = ".*";
    if (argc > 1) {
        pattern = argv[1];
    } else {
        std::cout << "Enter regex pattern: ";
        if (!(std::cin >> pattern)) pattern = ".*";
    }

	show(std::filesystem::current_path(), pattern);
}

//////////////////////////////////////////////////////////////////////////////////////
