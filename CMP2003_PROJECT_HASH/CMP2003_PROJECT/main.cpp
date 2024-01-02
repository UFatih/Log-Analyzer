#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "hash_table.h"
using namespace std;
int main() {
    hashtable ht;

    ifstream file("/Users/onurcan/Downloads/CMP2003_PROJECT 7/access_log.txt"); // user must implement own directory

    string line;
    while (getline(file, line)) {
        size_t file_name = line.find("GET ");
        size_t hash_value = line.find(" HTTP");
        if (file_name != string::npos && hash_value != string::npos) {
            size_t start = file_name + 4;
            string filename = line.substr(start, hash_value - start);
            ht.insertElement(filename);
        }
    }

    auto start_time = std::chrono::steady_clock ::now();

    vector<pair<string, int>> top10 = ht.getTop10();

    auto end_time = std::chrono::steady_clock ::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    cout << "Top 10 visits :\n";
    int rank = 1;
    for (const auto& entry : top10) {
        cout << "#" << rank << " Filename " << entry.first << " used " << entry.second << " times\n";
        rank++;
    }
    cout << "Exec time: " << elapsed_seconds.count() << " seconds\n";

    return 0;
}