#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Could not open input.txt\n";
        cout << "0\n";  // Ensure output even on error
        return 1;
    }

    vector<string> grid;
    string line;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        grid.push_back(line);
    }
    fin.close();

    if (grid.empty()) {
        cout << "0\n";
        return 0;
    }

    int R = grid.size();
    int C = grid[0].size();

    // Debug: print grid dimensions
    // cerr << "Grid size: " << R << " x " << C << "\n";

    // Find S
    int sr = -1, sc = -1;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == 'S') {
                sr = r;
                sc = c;
                break;
            }
        }
        if (sr != -1) break;
    }

    // Debug: print S position
    // cerr << "S found at: (" << sr << ", " << sc << ")\n";

    // If no S found
    if (sr == -1) {
        cout << "0\n";
        return 0;
    }

    // BFS for beams - need to track direction too
    // Each beam is (row, col, direction)
    // Directions: 0=down, 1=left, 2=right (since you only push downward initially)
    queue<tuple<int, int, int>> q;

    // Start beam going downward from below S (if in bounds)
    if (sr + 1 < R) {
        q.push({sr + 1, sc, 0});  // 0 means moving downward
    }

    // Count splits
    long long splits = 0;

    // Keep track of visited states to avoid infinite loops
    vector<vector<vector<bool>>> visited(R, vector<vector<bool>>(C, vector<bool>(3, false)));

    while (!q.empty()) {
        auto [r, c, dir] = q.front();
        q.pop();

        // Out of bounds => beam exits
        if (r < 0 || r >= R || c < 0 || c >= C) continue;

        // Check if visited with same direction
        if (visited[r][c][dir]) continue;
        visited[r][c][dir] = true;

        char cell = grid[r][c];

        if (cell == '^') {
            // Split into left and right beams
            splits++;

            // Left beam (if in bounds)
            if (c - 1 >= 0) {
                // When moving left, we continue downward in next step
                q.push({r + 1, c - 1, 0});
            }

            // Right beam (if in bounds)
            if (c + 1 < C) {
                q.push({r + 1, c + 1, 0});
            }
        } else {
            // Continue in current direction
            if (dir == 0) {  // Moving down
                q.push({r + 1, c, 0});
            }
            // Add other directions if needed
        }
    }

    cout << splits << "\n";
    // Force flush
    cout.flush();

    return 0;
}