#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
class hashtable {
private:
    static const int TABLE_SIZE = 100000; // table size
    vector<pair<string, int>> table[TABLE_SIZE];

    int hashFunc(const string& key) {
        unsigned long hash = 5381;// used for efficiency
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % TABLE_SIZE;
    }

public:
    void insertElement(const string& filename) {// definiton of the insertion
        int index = hashFunc(filename);
        for (auto& entry : table[index]) {
            if (entry.first == filename) {
                entry.second++;
                return;
            }
        }
        table[index].emplace_back(filename, 1);
    }

    vector<pair<string, int>> getTop10() {
        vector<pair<string, int>> result;

        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                result.push_back(entry);
            }
        }

        sort(result.begin(), result.end(),
                  [](const pair<string, int>& a, const pair<string, int>& b) {
                      return a.second > b.second;
                  });

        return vector<pair<string, int>>(result.begin(), result.begin() + min(10, static_cast<int>(result.size())));
    }
};

