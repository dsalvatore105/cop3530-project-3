#include "csvParser.h"

vector<int> csvParser::splitToInts(string& rowString) {
    // Takes a string and splits it into ints
    vector<int> data = {};
    string to_int = "";
    int rowLength = rowString.length();    

    for (int i = 0; i <= rowLength; i++) {
        char character = rowString[i];

        if (i == rowLength || character == delimiter) {
            if (to_int == "" || to_int == "0") { 
                //cout << "There was a problem" << endl; // Malformed data, ignore the row
                return {};
            };

            data.push_back(stoi(to_int));
            to_int = "";
            continue;
        }

        to_int += character;
    }

    return data;
}

void csvParser::setFile(string fileName) {
    ifstream file(fileName);
    if (file.good()) fileToRead = fileName;
    else cout << "No file with name: " << fileName << " exists!" << endl;
}

void csvParser::printRow(vector<int>& row, int num) {
    cout << "[" << num << "]: " << "{";
    const int& size = row.size();

    for (int i = 0; i < size; i++) {
        cout << row[i];
        if (i != size - 1) cout << ", "; 
    }

    cout << "}" << endl;
}

void csvParser::printData(vector<vector<int>>& givenData) {
    for (int i = 0; i < givenData.size(); i++) printRow(givenData[i], i);
}

void csvParser::parseRows(vector<vector<int>>& data, int rows) {
    if (fileToRead == "") {cout << "Please use setFile() on a valid .csv file." << endl; return;} 

    int rowsParsed = 0;
    ifstream file(fileToRead);
    if (!file.is_open()) throw runtime_error("Could not open file.");

    string row;
    while (getline(file, row)) {
        vector<int> values = splitToInts(row);
        if (values.size() > 0) {
            data.push_back(values);
            rowsParsed++;
        }
        if (rowsParsed >= rows) break;
    }
}