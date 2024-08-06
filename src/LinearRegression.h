#include "iostream"
#include "vector"
#include "string"
#include <cmath>
#include <iomanip>
#include <algorithm>
#pragma once
using namespace std;

class LR {
public:
    double getLinearRegression(vector<vector<int>> data, int dp, double X);
    double getMultLinearRegression(vector<vector<int>> data, int dp, double X1, double X2);
};