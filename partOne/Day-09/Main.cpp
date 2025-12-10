#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Cannot open input.txt" << endl;
        return 1;
    }

    vector<pair<int, int>> points;
    set<pair<int, int>> pointSet;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        size_t comma = line.find(',');
        if (comma == string::npos) continue;
        int x = stoi(line.substr(0, comma));
        int y = stoi(line.substr(comma + 1));
        points.push_back({x, y});
        pointSet.insert({x, y});
    }

    long long maxArea = 0;
    int n = points.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x1 = points[i].first, y1 = points[i].second;
            int x2 = points[j].first, y2 = points[j].second;

            if (x1 == x2 || y1 == y2) continue;

            long long width = llabs(x1 - x2) + 1;
            long long height = llabs(y1 - y2) + 1;
            long long area = width * height;

            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    cout << maxArea << endl;

    return 0;
}