using namespace std;

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./day23 [input file name]\n";
        exit(1);
    }

    unordered_map<string, set<string>> mp;

    ifstream file(argv[1]);

    string ln;
    while (getline(file, ln)) {
        string n1 = ln.substr(0, 2);
        string n2 = ln.substr(3, 2);
        mp[n1].insert(n2);
        mp[n2].insert(n1);
    }

    int tTriples = 0;

    for (auto it = mp.begin(); it != mp.end(); it++) {
        // Loop through nodes starting w/ 'T'
        if (it->first[0] == 't') {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                if ((*i)[0] == 't' && (*i) < it->first) continue; // Prevent double counting w/ multiple Ts
                for (auto j = i; j != it->second.end(); j++) {
                    if (mp[*i].count(*j)) {
                        if ((*j)[0] == 't' && (*j) < it->first) continue; // Prevent double counting w/ multiple Ts
                        cout << "Adding triplet: " << it->first << ", " << *i << ", " << *j << "\n";
                        tTriples++;
                    }
                }
            }
        }
    }

    cout << "The number of triplets with T computers is: " << tTriples << "\n";

    // Track which nodes have been seen
    unordered_set<string> seen;

    // Keep a list of all groups
    vector<unordered_set<string>> groups;

    for (auto it = mp.begin(); it != mp.end(); it++) {
        if (!seen.count(it->first)) {
            // If haven't visited already, investigate

            // Track members of current network
            unordered_set<string> group;

            // Store connected nodes in a queue
            deque<string> neighbors(it->second.begin(), it->second.end());

            while (!neighbors.empty()) {
                string n = neighbors.front();
                neighbors.pop_front();

                // Skip over if already visited
                if (!seen.count(n)) {
                    seen.insert(n);
                    group.insert(n);

                    // Add neighbors of neighbor to queue
                    for (auto i = mp[n].begin(); i != mp[n].end(); i++) neighbors.push_back(*i);
                }
            }

            groups.push_back(group);
        }
    }

    int bestSize = groups[0].size();
    int bestI = 0;

    for (int i = 1; i < groups.size(); i++) {
        if (groups[i].size() > bestSize) {
            bestSize = groups[i].size();
            bestI = i;
        }
    }

    sort(groups[bestI].begin(), groups[bestI].end());

    cout << "Best group:\n";

    for (string m : groups[bestI]) cout << m << ",";
    
    return 0;
}