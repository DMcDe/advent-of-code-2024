using namespace std;
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int locToInt(int r, int c, int m) {
    return r * m + c;
}

pair<int, int> intToLoc(int i, int m) {
    int c = i % m;
    int r = i / m;
    return {r, c};
}

int findAntinodes(const vector<vector<char>> &grid, int m, int n, bool partA) {
    // Store antinode & antenna locations
    unordered_set<int> antinodes;
    unordered_map<char, vector<pair<int, int>>> antennas;

    // Loop to find antennas
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != '.') antennas[grid[i][j]].emplace_back(i, j);
        }
    }

    // Loop to calculate antinode locations
    for (auto it : antennas) {
        // cout << "Iterating through " << it.first << "\n";
        auto vec = it.second;
        int sz = vec.size();
        for (int i = 0; i < sz; i++) {
            for (int j = i + 1; j < sz; j++) {
                // cout << vec[i].first << " " << vec[i].second << "\t" << vec[j].first << " " << vec[j].second << "\t\t";
                int rdif = vec[j].first - vec[i].first;
                int cdif = vec[j].second - vec[i].second;
                // cout << vec[i].first - rdif << " " << vec[i].second - cdif << "\t";
                // cout << vec[j].first + rdif << " " << vec[j].second + cdif << "\n";

                if (partA) {
                    if (vec[i].first - rdif >= 0 && vec[i].second - cdif < n && vec[i].second - cdif >= 0) {
                        antinodes.insert(locToInt(vec[i].first - rdif, vec[i].second - cdif, m));
                    }

                    if (vec[j].first + rdif < m && vec[j].second + cdif < n && vec[j].second + cdif >= 0) {
                        antinodes.insert(locToInt(vec[j].first + rdif, vec[j].second + cdif, m));
                    }
                } else {
                    int k = vec[i].first;
                    int l = vec[i].second;
                    while (k >= 0 && l < n && l >= 0) {
                        // cout << k << " " << l << "\t";
                        antinodes.insert(locToInt(k, l, m));
                        k -= rdif;
                        l -= cdif;
                    }

                    k = vec[j].first;
                    l = vec[j].second;
                    while (k < m && l < n && l >= 0) {
                        // cout << k << " " << l << "\t";
                        antinodes.insert(locToInt(k, l, m));
                        k += rdif;
                        l += cdif;
                    }
                    // cout << "\n";
                }
            }
        }
    }

    return size(antinodes);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./d8-sol [input filename]\n";
        exit(1);
    }

    // Declare grid
    vector<vector<char>> grid;

    // Read in file input
    ifstream file(argv[1]);

    string str;
    int row = 0;
    while (file >> str) {
        grid.push_back({});
        for (auto ch : str) {
            grid[row].push_back(ch);
        }
        row++;
    }

    // Get grid size
    int m = grid.size();
    int n = grid[0].size();

    int partASolution = findAntinodes(grid, m, n, true);

    cout << "Number of antinodes in range: " << partASolution << "\n";

    int partBSolution = findAntinodes(grid, m, n, false);

    cout << "Number of antinodes in range, accounting for resonant harmonics: " << partBSolution << "\n";

    return 0;
}