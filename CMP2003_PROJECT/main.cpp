#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unordered_map<string, int> fileCount;
    ifstream inputFile("/Users/ayberkkarataban/CLionProjects/CMP2003_PROJECT/access_log.txt"); // users must define own file path


    string line;
    while (getline(inputFile, line)) {
        size_t name = line.find("GET ");
        if (name != string::npos) {
            size_t value = line.find(" HTTP");
            string fileName = line.substr(name + 4, value - (name + 4));
            fileCount[fileName]++;
        }
    }

    inputFile.close();

    vector<pair<string, int>> sortedlines(fileCount.begin(), fileCount.end());
    sort(sortedlines.begin(), sortedlines.end(), [](const pair<string, int>& x, const pair<string, int>& y) {
        return x.second > y.second;
    });

    cout << "Top 10 Visits\n";


    auto start = chrono::high_resolution_clock ::now();

    int count = 0;
    for (const auto& pair : sortedlines) {
        cout << "#" << count + 1 << " Filename " << pair.first << " used " << pair.second << " times\n";
        count++;
        if (count >= 10) {
            break;
        }
    }

    auto end = chrono::high_resolution_clock ::now();
    chrono::duration<double> elapsedSeconds = end - start;
    cout << "Exec Time: " << elapsedSeconds.count() << " seconds\n";

    return 0;
}
