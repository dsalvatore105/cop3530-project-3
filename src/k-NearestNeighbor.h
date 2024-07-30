#include "iostream"
#include "vector"
#include "string"
#include <cmath>
#include <iomanip>
#include <algorithm>
#pragma once
using namespace std;

class kNN {
public:
    double getDistanceTwoVariable(vector<int>& A, vector<int>& B);
    double getDistanceOneVariable(vector<int>&A, vector<int>&B);
    vector<pair<double, vector<int>>> getNearestPoints(vector<int>& point, vector<vector<int>>& data, unsigned int K);
    // Returns K nearest points and their respective distances.

    void printPoint(vector<int>& point);
    double predict(int input, vector<vector<int>>& data, unsigned int K);
};