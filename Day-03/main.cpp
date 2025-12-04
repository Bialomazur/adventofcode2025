// main.cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Cannot open input.txt – make sure it's in the same folder as the executable\n";
        return 1;
    }

    long long total = 0;
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) continue;

        char bestTens  = '0';   // highest digit seen so far (for the tens place)
        char bestUnits = '0';   // second-highest digit (for the units place)

        for (char c : line) {
            if (c < '0' || c > '9') continue;   // skip any unexpected characters

            if (c > bestTens) {
                bestUnits = bestTens;   // previous best becomes candidate for units
                bestTens  = c;
            } else if (c > bestUnits) {
                bestUnits = c;
            }
        }

        // If the line has less than 2 digits the problem guarantees at least two,
        // but we guard anyway:
        if (bestTens == '0') bestTens = line[0];
        if (bestUnits == '0') bestUnits = bestTens;

        int joltage = 10 * (bestTens - '0') + (bestUnits - '0');
        total += joltage;
    }

    std::cout << "Total output joltagee: " << total << '\n';
    return 0;
}