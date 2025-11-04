#include <cmath>
#include <iostream>
#include <vector>

#define ull unsigned long long int

int main() {
    std::vector<ull> answer = std::vector <ull>();

    for (ull i = 1; i <= 100; i++) {
        std::vector<ull> current = std::vector <ull>();
        ull element = i;

        while (element != 1) {
            current.push_back(element);
            element = element % 2 == 0 ? element / 2 : 3 * element + 1;
        }
        current.push_back(element);


        if (current.size() > answer.size()) {
            answer = current;
        }
    }

    std::cout << answer.size() << ' ' << answer.at(0) << std::endl;
}
