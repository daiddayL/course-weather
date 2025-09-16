//
//  main.cpp
//  file_reading_tryal
//
//  Created by DAiD on 6.05.24.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

vector<string> reading(int num, int n, const string& fields) {
    vector<string> data;
    ifstream file("list.txt");

    if (file.is_open()) {
        cout << "Reading from the file" << endl;
        string line;
        int lineCount = 0;
        while (getline(file, line)) {
            lineCount++;
            if (lineCount >= num && data.size() < n) {
                istringstream iss(line);
                string field;
                string output;
                int fieldIndex = 0;
                while (getline(iss, field, '/')) {
                    if (fieldIndex == stoi(fields)) {
                        output = field;
                        break;
                    } else if (fields.find(to_string(fieldIndex)) != string::npos) {
                        output += field + " ";
                    }
                    fieldIndex++;
                }
                data.push_back(output);
                cout << output << endl;
            }
            if (data.size() == n) {
                break;
            }
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    return data;
}

int main() {
    vector<string> lines = reading(1, 1, "012345");
    return 0;
}
