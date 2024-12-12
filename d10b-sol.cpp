using namespace std;
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

void updateNeighbors(queue<pair<int, int>> &q, const vector<vector<int>> &grid, vector<vector<int>> &paths, 
                     vector<vector<bool>> &vis, int r, int c, int m, int n) {
    vector<pair<int, int>> neighbors = {{r - 1, c}, {r + 1, c}, {r, c - 1}, {r, c + 1}};
    int num = grid[r][c];
    int count = paths[r][c];

    // cout << "---At " << r << " " << c << " with value " << grid[r][c] << "---\n";
    
    for (auto p : neighbors) {
        if (p.first >= 0 && p.first < m && p.second >= 0 && p.second < n) {
            if (grid[p.first][p.second] == num - 1) {
                // cout << "Investigating: " << p.first << " " << p.second << " with value " << grid[p.first][p.second] << " ";
                paths[p.first][p.second] += count;

                if (!vis[p.first][p.second]) {
                    q.push(p);
                    vis[p.first][p.second] = true;
                }

                // cout << "New count: " << paths[p.first][p.second] << "\n";
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./day10 [input file name]\n";
        exit(1);
    }

    vector<vector<int>> grid;
    vector<vector<int>> paths;
    vector<vector<bool>> vis;
    queue<pair<int, int>> q;

    ifstream file(argv[1]);

    string str;
    int row = 0;
    while (file >> str) {
        int col = 0;
        grid.push_back({});
        paths.push_back({});
        vis.push_back({});

        for (auto ch : str) {
            grid[row].push_back(ch - '0');

            if (ch == '9') {
                paths[row].push_back(1);
                vis[row].push_back(true);
                q.emplace(row, col);
            } else {
                paths[row].push_back(0);
                vis[row].push_back(false);
            }

            col++;
        }

        row++;
    }

    int m = grid.size();
    int n = grid[0].size();
    
    while (!q.empty()) {
        auto elt = q.front();
        q.pop();
        updateNeighbors(q, grid, paths, vis, elt.first, elt.second, m, n);
    }

    int sum = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // cout << paths[i][j] << " ";
            if (grid[i][j] == 0) sum += paths[i][j];
        }
        // cout << "\n";
    }

    cout << "The trailheads sum to " << sum << " paths.\n";

    return 0;
}