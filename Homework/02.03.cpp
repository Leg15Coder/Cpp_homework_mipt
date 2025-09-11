#include <iostream>

int main() {
    char c = 'a';

    switch (std::cin >> c; c) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 'u':
        case 't':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'l': {
            std::cout << "lowercase letter" << '\n';
            break;
        }

        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'U':
        case 'T':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case 'L': {
            std::cout << "upper letter" << '\n';
            break;
        }

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
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
