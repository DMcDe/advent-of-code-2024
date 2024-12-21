using namespace std;

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>

bool achievable(const string &des, unordered_set<string> &yes_cache, unordered_set<string> &no_cache) {
    if (no_cache.count(des)) return false;
    else if (yes_cache.count(des)) return true;

    for (int i = 1; i < des.size(); i++) {
        // cout << des << " " << des.substr(0, i) << " " << des.substr(i) << "\n";
        if (yes_cache.count(des.substr(0, i))) {
            // cout << "Achievable: ";
            if (achievable(des.substr(i), yes_cache, no_cache)) {
                // cout << "Achieved " << des << " ending with " << des.substr(i) << "\n";
                yes_cache.insert(des.substr(i));
                yes_cache.insert(des);
                return true;
            }
        }
    }

    no_cache.insert(des);
    // cout << "INSERT: " << des << ", new size: " << no_cache.size() << "\n";
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./day19 [input file name]\n";
        exit(1);
    }

    ifstream file(argv[1]);

    // Read in header, containing viable patterns
    string header;
    getline(file, header, '\n');
    stringstream ss(header);

    // Parse patterns and store in set
    unordered_set<string> patterns;
    unordered_set<string> nos; // Create to store unachievable patterns

    string str;
    while (getline(ss, str, ',')) {
        if (str[0] == ' ') str = str.substr(1); // Remove leading whitespace
        // cout << str << "\n";
        patterns.insert(str);
    }

    // Test desired designs
    int doable_designs = 0;

    // Get blank line
    getline(file, str); 

    while (getline(file, str)) {
        if (achievable(str, patterns, nos)) {
            doable_designs++;
            //cout << "Achievable: " << str << "\n";
        } else {
            // cout << "FAILED " << str << "\n";
        }
    }

    // cout << "---No Cache Dump---\n";
    // for (auto it = nos.begin(); it != nos.end(); it++) {
    //     cout << *it << "\n";
    // }

    cout << doable_designs << " designs can be achieved.\n";

    return(0);
}