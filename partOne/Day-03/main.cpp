#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Could not open input.txt\n";
        return 1;
    }

    string s;
    long long total = 0;

    while (fin >> s) {
        int n = s.size();
        vector<int> digits(n);
        for (int i = 0; i < n; i++)
            digits[i] = s[i] - '0';

        int best = 0;

        // For each position as tens digit,
        // find the best possible ones digit to the right.
        for (int i = 0; i < n; i++) {
            int tens = digits[i];

            // find max digit to the right
            int maxRight = -1;
            for (int j = i + 1; j < n; j++)
                maxRight = max(maxRight, digits[j]);

            if (maxRight >= 0) {
                int val = tens * 10 + maxRight;
                best = max(best, val);
            }
        }

        total += best;
    }

    cout << total << "\n";
    return 0;
}
