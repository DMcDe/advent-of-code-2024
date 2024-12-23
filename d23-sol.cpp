using namespace std;

#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>

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
        if (it->first[0] == 't') {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                if ((*i)[0] == 't' && (*i) < it->first) continue;
                for (auto j = i; j != it->second.end(); j++) {
                    if (mp[*i].count(*j)) {
                        if ((*j)[0] == 't' && (*j) < it->first) continue;
                        cout << "Adding triplet: " << it->first << ", " << *i << ", " << *j << "\n";
                        tTriples++;
                    }
                }
            }
        }
    }

    cout << "The number of triplets with T computers is: " << tTriples << "\n";


    return 0;
}