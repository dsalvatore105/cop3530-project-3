#include "k-NearestNeighbor.h"

double kNN::getDistanceTwoVariable(vector<int>& A, vector<int>& B) {return sqrt(pow(B[0] - A[0], 2) + pow(B[1] - A[1], 2));}
double kNN::getDistanceOneVariable(vector<int>&A, vector<int>&B) {return abs(A[0] - B[0]);}

vector<pair<double, vector<int>>> kNN::getNearestPoints(vector<int>& thisPoint, int maxPoints, vector<vector<int>>& data, unsigned int K) {
    int totalPoints = data.size();
    int pointsChecked = 0;
    vector<pair<double, vector<int>>> distancePointPairs;
    vector<pair<double, vector<int>>> K_distancePointPairs;

    // Get the distances for every point
    for (auto& anyPoint : data) {
        if (pointsChecked >= maxPoints) break;
        if (anyPoint == thisPoint) continue;
        double distance = getDistanceTwoVariable(thisPoint, anyPoint);
        distancePointPairs.push_back(make_pair(distance, anyPoint));
        pointsChecked++;
    }

    sort(distancePointPairs.begin(), distancePointPairs.end());

    // Reduce the vector to only be the first K elements. We don't need the rest.
    for (int i = 0; i < K; i++) K_distancePointPairs.push_back(distancePointPairs[i]);
    distancePointPairs.clear();

    return K_distancePointPairs;
}

double kNN::predict(int x1, int x2, vector<vector<int>>& data, int maxPoints, unsigned int K) {
    vector<int> point = {x1, x2, 0}; // Y (Price is unknown)
    vector<pair<double, vector<int>>> distancePointPairs = getNearestPoints(point, maxPoints, data, K);

    // Average the Y-values of the nearest points.
    double average = 0;

    for (auto& distancePointPair : distancePointPairs) average += distancePointPair.second[2];
    average = average / K;

    return average;
}