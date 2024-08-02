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
    // Parses a given amount of rows.
    void setFile(string fileName);
    // Sets the file to read.
    void printData(vector<vector<int>>& givenData);
    // Prints data.
    void printRow(vector<int>& row);
    // Prints a point;
    vector<int> splitToInts(string& rowString);
    // Internal function used to break up rows into ints.
};