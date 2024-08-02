#include "k-NearestNeighbor.h"

double kNN::getDistanceTwoVariable(vector<int>& A, vector<int>& B) {
    return sqrt(pow(B[0] - A[0], 2) + pow(B[1] - A[1], 2));
}

double kNN::getDistanceOneVariable(vector<int>&A, vector<int>&B) {
    return abs(A[0] - B[0]);
}

vector<pair<double, vector<int>>> kNN::getNearestPoints(vector<int>& thisPoint, vector<vector<int>>& data, unsigned int K) {
    int totalPoints = data.size();
    vector<pair<double, vector<int>>> distancePointPairs;
    vector<pair<double, vector<int>>> K_distancePointPairs;

    for (auto& anyPoint : data) {
        if (anyPoint == thisPoint) continue;
        double distance = getDistanceOneVariable(thisPoint, anyPoint);
        distancePointPairs.push_back(make_pair(distance, anyPoint));
    }

    sort(distancePointPairs.begin(), distancePointPairs.end());

    // Reduce the vector to only be the first K elements. We don't need the rest.
    for (int i = 0; i < K; i++) K_distancePointPairs.push_back(distancePointPairs[i]);
    distancePointPairs.clear();

    return K_distancePointPairs;
}

double kNN::predict(int input, vector<vector<int>>& data, unsigned int K) {
    vector<int> point = {input, 0}; // Given X, find Y
    vector<pair<double, vector<int>>> distancePointPairs = getNearestPoints(point, data, K);

    // Average the Y-values of the nearest points.
    double average = 0;

    // TODO: Implement distance weighting
    for (auto& distancePointPair : distancePointPairs) average += distancePointPair.second[1];
    average = average / K;

    return average;
}