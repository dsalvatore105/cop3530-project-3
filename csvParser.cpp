#include "iostream"
#include "vector"
#include "string"
#include "fstream"
#include "sstream"
#pragma once
using namespace std;

class csvParser {
    vector<vector<int>> data;
    char lineBreak = '\n';
    char delimiter = ',';
    string fileToRead = "";

public:

    void parseRows(vector<vector<int>>& data, int rows);
    void setFile(string fileName);
    vector<int> splitToInts(string& rowString);
};

vector<int> csvParser::splitToInts(string& rowString) {
    // Takes a string and splits it into ints
    vector<int> data = {};
    string to_int = "";
    int rowLength = rowString.length();    

    for (int i = 0; i <= rowLength; i++) {
        char character = rowString[i];
        if (i == rowLength || character == delimiter) {
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

void csvParser::parseRows(vector<vector<int>>& data, int rows) {
    if (fileToRead == "") {cout << "Please use setFile() on a valid .csv file." << endl; return;} 

    int rowsParsed = 0;
    ifstream file(fileToRead);
    if (!file.is_open()) throw runtime_error("Could not open file.");

    string row;
    while (getline(file, row)) {
        vector<int> values = splitToInts(row);
        data.push_back(values);
        rowsParsed++;
        if (rowsParsed >= rows) break;
    }
}