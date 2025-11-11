#include <iostream>
#include <array>
#include <cstdint>


class IPv4 {
public:
    IPv4() : data{0, 0, 0, 0} {}

    IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) : data{a, b, c, d} {}

    IPv4(const IPv4& other) = default;

    IPv4& operator=(const IPv4& other) = default;

    IPv4& operator++() {
        for (int i = 3; i >= 0; --i) {
            if (data[i] < 255) {
                ++data[i];
                break;
            } else {
                data[i] = 0;
            }
        }
        return *this;
    }

    IPv4 operator++(int) {
        IPv4 temp = *this;
        ++(*this);
        return temp;
    }

    IPv4& operator--() {
        for (int i = 3; i >= 0; --i) {
            if (data[i] > 0) {
                --data[i];
                break;
            } else {
                data[i] = 255;
            }
        }
        return *this;
    }

    IPv4 operator--(int) {
        IPv4 temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator==(const IPv4& lhs, const IPv4& rhs) {
        return lhs.data == rhs.data;
    }

    friend bool operator!=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const IPv4& lhs, const IPv4& rhs) {
        return lhs.data < rhs.data;
    }

    friend bool operator>(const IPv4& lhs, const IPv4& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const IPv4& lhs, const IPv4& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
        os << static_cast<int>(ip.data[0]) << '.' 
           << static_cast<int>(ip.data[1]) << '.' 
           << static_cast<int>(ip.data[2]) << '.' 
           << static_cast<int>(ip.data[3]);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ip) {
        int a, b, c, d;
        char dot1, dot2, dot3;
        
        is >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d;
        
        if (dot1 != '.' || dot2 != '.' || dot3 != '.') {
            return is;
        }
        
        if (a < 0 || a > 255 || b < 0 || b > 255 || 
            c < 0 || c > 255 || d < 0 || d > 255) {
            
            ip.data[0] = static_cast<std::uint8_t>(a);
            ip.data[1] = static_cast<std::uint8_t>(b);
            ip.data[2] = static_cast<std::uint8_t>(c);
            ip.data[3] = static_cast<std::uint8_t>(d);
        }
        
        return is;
    }

    std::uint8_t operator[](std::size_t index) const {
        return data[index];
    }

    std::uint8_t& operator[](std::size_t index) {
        return data[index];
    }

private:
    std::array<std::uint8_t, 4> data;
};


int main() {
    // Тестирование конструкторов
    IPv4 ip1;
    IPv4 ip2(192, 168, 1, 1);
    IPv4 ip3 = ip2;

    std::cout << "ip1 (default): " << ip1 << std::endl;
    std::cout << "ip2 (192.168.1.1): " << ip2 << std::endl;
    std::cout << "ip3 (copy of ip2): " << ip3 << std::endl;

    // Тестирование инкремента
    std::cout << "\nTesting increment:" << std::endl;
    IPv4 ip4(192, 168, 1, 254);
    std::cout << "Original: " << ip4 << std::endl;
    std::cout << "Prefix ++: " << ++ip4 << std::endl;
    std::cout << "Postfix ++: " << ip4++ << std::endl;
    std::cout << "After postfix ++: " << ip4 << std::endl;

    // Тестирование декремента
    std::cout << "\nTesting decrement:" << std::endl;
    IPv4 ip5(192, 168, 2, 1);
    std::cout << "Original: " << ip5 << std::endl;
    std::cout << "Prefix --: " << --ip5 << std::endl;
    std::cout << "Postfix --: " << ip5-- << std::endl;
    std::cout << "After postfix --: " << ip5 << std::endl;

    // Тестирование сравнения
    std::cout << "\nTesting comparison:" << std::endl;
    IPv4 ip6(10, 0, 0, 1);
    IPv4 ip7(10, 0, 0, 2);
    std::cout << ip6 << " == " << ip7 << " : " << (ip6 == ip7) << std::endl;
    std::cout << ip6 << " != " << ip7 << " : " << (ip6 != ip7) << std::endl;
    std::cout << ip6 << " < " << ip7 << " : " << (ip6 < ip7) << std::endl;
    std::cout << ip6 << " > " << ip7 << " : " << (ip6 > ip7) << std::endl;

    // Тестирование ввода/вывода
    std::cout << "\nTesting input/output:" << std::endl;
    IPv4 ip8;
    std::cout << "Enter IP address (format: xxx.xxx.xxx.xxx): ";
    
    if (std::cin >> ip8) {
        std::cout << "You entered: " << ip8 << std::endl;
        
        std::cout << "Next 5 IP addresses:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << ++ip8 << std::endl;
        }
    } else {
        std::cout << "Invalid input format!" << std::endl;
    }

    // Тестирование граничных случаев
    IPv4 ip9(255, 255, 255, 255);
    std::cout << "Max IP: " << ip9 << std::endl;
    std::cout << "After ++: " << ++ip9 << std::endl;

    IPv4 ip10(0, 0, 0, 0);
    std::cout << "Min IP: " << ip10 << std::endl;
    std::cout << "After --: " << --ip10 << std::endl;
}
