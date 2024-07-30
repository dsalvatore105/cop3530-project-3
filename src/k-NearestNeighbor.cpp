#include "k-NearestNeighbor.h"

double kNN::getDistanceTwoVariable(vector<int>& A, vector<int>& B) {
    return sqrt(pow(B[0] - A[0], 2) + pow(B[1] - A[1], 2));
}

double kNN::getDistanceOneVariable(vector<int>&A, vector<int>&B) {
    return abs(A[0] - B[0]);
}

// This could be moved outside of kNN since it's not really exclusive to it.
void kNN::printPoint(vector<int>& point) {
    cout << setprecision(2) << fixed;

    cout << "{";
    for (int i = 0; i < point.size(); i++) {
        cout << point[i];
        if (i != point.size() - 1) std::cout << ", ";
    }
    cout << "}" << endl;
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

    for (int i = 0; i < K; i++) {
        double distance = K_distancePointPairs[i].first;
        vector<int>& point = K_distancePointPairs[i].second;
        cout << setprecision(2) << fixed;

        cout << "K = " << i+1 << " {Distance: " << distance << "} | Nearest point: ";
        printPoint(point);
    }

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