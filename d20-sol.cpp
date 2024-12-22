using namespace std;

#include <fstream>
#include <iostream>
#include <vector>
#include <set>

int traverseGrid(vector<vector<int>> &grid, int sr, int sc) {
    vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int loc = grid[sr][sc];
    int m = grid.size(), n = grid[0].size();
    int r = sr, c = sc;
    int count = 0;

    while (loc != -2) {
        grid[r][c] = ++count;
        // cout << "Visiting " << r << " " << c << ": " << grid[r][c] << "\n";
        for (auto p : moves) {
            if (r + p.first >= 0 && r + p.first < m && c + p.second >= 0 && c + p.second < n) {
                // cout << grid[r + p.first][c + p.second] << " ";
                if (grid[r + p.first][c + p.second] == 0 || grid[r + p.first][c + p.second] == -2) {
                    r += p.first;
                    c += p.second;
                    loc = grid[r][c];
                    break;
                }
            }
        }
    }

    grid[r][c] = ++count;

    return count;
}

int countCheats(const vector<vector<int>> &grid, int r, int c, int m, int n, int threshold) {
    vector<pair<int, int>> moves = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};

    int cheats = 0;

    for (auto p : moves) {
        if (r + p.first >= 0 && r + p.first < m && c + p.second >= 0 && c + p.second < n) {
            if (grid[r + p.first][c + p.second] - grid[r][c]  - 2 >= threshold) {
                cheats++;
                cout << "Found a cheat for " << grid[r + p.first][c + p.second] - grid[r][c] - 2 << " picoseconds: ";
                cout << "From (" << r << ", " << c << ") to (" << r + p.first << ", " << c + p.second << ")\n";
            }
        }
    }

    return cheats;
}

int traverseCheats(const vector<vector<int>> &grid, int sr, int sc, int threshold, int pathLength) {
    vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int r = sr, c = sc;
    int m = grid.size(), n = grid[0].size();
    int loc = grid[r][c];
    int cheats = 0;

    while (loc < pathLength - threshold + 1) {
        cheats += countCheats(grid, r, c, m, n, threshold);
        for (auto p : moves) {
            if (r + p.first >= 0 && r + p.first < m && c + p.second >= 0 && c + p.second < n) {
                // cout << grid[r + p.first][c + p.second] << " ";
                if (grid[r + p.first][c + p.second] == loc + 1) {
                    r += p.first;
                    c += p.second;
                    loc = grid[r][c];
                    break;
                }
            }
        }
    }

    return cheats;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./day20 [input file name] [threshold]\n";
        exit (1);
    }

    vector<vector<int>> grid;

    // Read in maze
    ifstream file(argv[1]);
    string str;

    int row = 0;
    int col = 0;
    int startR, startC;
    while (getline(file, str)) {
        col = 0;
        grid.push_back({});
        for (char ch : str) {
            if (ch == '#') {
                grid[row].push_back(-1);
            } else if (ch == 'S') {
                startR = row;
                startC = col;
                grid[row].push_back(0);
            } else if (ch == 'E') {
                grid[row].push_back(-2);
            } else {
                grid[row].push_back(0);
            }
            col++;
        }
        row++;
    }

    int m = grid.size();
    int n = grid[0].size();

    int realPath = traverseGrid(grid, startR, startC);
    int threshold = atoi(argv[2]);

    // Verify grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << traverseCheats(grid, startR, startC, threshold, realPath) << " cheats save " << threshold << "+ picoseconds.\n";

    return 0;
}