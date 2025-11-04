#include <iostream>

int main() {
    char c = 'a';

    switch (std::cin >> c; c) {
        case 'a'...'z': {
            std::cout << "lowercase letter" << '\n';
            break;
        }

        case 'A'...'Z': {
            std::cout << "upper letter" << '\n';
            break;
        }

        case '0'...'9': {
            std::cout << "number" << '\n';
            break;
        }

        case '.':
        case ',':
        case ';':
        case ':':
        case '"':
        case '\'':
        case '?':
        case '!': {
            std::cout << "punctuation character" << '\n';
            break;
        }

        default: {
            std::cout << "other" << '\n';
            break;
        }
    }

    return 0;
}
