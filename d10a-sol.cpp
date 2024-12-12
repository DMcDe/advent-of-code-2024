using namespace std;
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

//TODO: Think I have to rework this to start at 0s and move to 9s
//Current way counts number of ways to get to peaks, not number of reachable peaks

void updateNeighbors(stack<pair<int, int>> &stk, const vector<vector<int>> &grid, vector<vector<bool>> &vis,
                     int &sum, int r, int c, int m, int n) {
    vector<pair<int, int>> neighbors = {{r - 1, c}, {r + 1, c}, {r, c - 1}, {r, c + 1}};
    int num = grid[r][c];

    if (num == 9) {
        sum++;
        return;
    } else if (num == 0) {
        for (int i = 0; i < m; i++) {
            // Reset what was visited
            fill(vis[i].begin(), vis[i].end(), false);
        }
        vis[r][c] = true;
    }

    // cout << "---At " << r << " " << c << " with value " << grid[r][c] << "---\n";
    
    for (auto p : neighbors) {
        if (p.first >= 0 && p.first < m && p.second >= 0 && p.second < n) {
            if (grid[p.first][p.second] == num + 1) {
                // cout << "Investigating: " << p.first << " " << p.second << " with value " << grid[p.first][p.second] << "\n";

                if (!vis[p.first][p.second]) {
                    stk.push(p);
                    vis[p.first][p.second] = true;
                }
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
    stack<pair<int, int>> stk;

    ifstream file(argv[1]);

    string str;
    int row = 0;
    while (file >> str) {
        int col = 0;
        grid.push_back({});

        for (auto ch : str) {
            grid[row].push_back(ch - '0');

            if (ch == '0') {
                stk.emplace(row, col);
            }
            col++;
        }

        row++;
    }

    int m = grid.size();
    int n = grid[0].size();

    vector<vector<bool>> vis(m, vector<bool>(n, false));

    int sum = 0;
    
    while (!stk.empty()) {
        auto t = stk.top();
        vis[t.first][t.second] = true;
        stk.pop();
        updateNeighbors(stk, grid, vis, sum, t.first, t.second, m, n);
    }

    cout << "The trailheads sum to " << sum << " paths.\n";

    return 0;
}