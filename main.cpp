#include "src/csvParser.cpp"
#include "src/k-NearestNeighbor.cpp"
#include "src/LinearRegression.cpp"
using namespace std;

int main() {
    csvParser* parser = new csvParser();
    LR* lrAlgo = new LR();
    kNN* knnAlgo = new kNN();

    vector<vector<int>> data;

	for (;;) {
		string cmd;
		cin >> cmd;

		if (cmd == "printData") {  
            // Print all stored data.
            parser->printData(data);
        } else if (cmd == "load"){
            // Load <x> data points.
            int count;
            cin >> count;

            parser->setFile("data/csvs/totaldata.csv");
            if (parser->fileToRead == "") continue;

            cout << "Attempting to load " << count << " data points from \"" << parser->fileToRead << "\"" << endl;
            parser->parseRows(data, count);

            if (data.size() < count) {
                cout << "The amount you tried to load exceeded the amount of data that could be loaded." 
                << "\nAs a result, only " << data.size() << " points were loaded." << endl;
            } else {
                cout << "Successfully loaded." << endl;
            }

            cout << endl;

        } else if (cmd == "lr") {
            int dp;
            double x1, x2;
            cin >> dp >> x1 >> x2;
            
            cout << "\n=============================== PREDICTION ===============================" << endl;
            cout << "Predicted value for year: " << setprecision(0) << fixed << x1 << " and square footage: " << x2 
            << " | $" << setprecision(2) << fixed << lrAlgo->getMultLinearRegression(data, dp, x1, x2) << endl;
            cout << "==========================================================================" << endl;

            //lrAlgo->getLinearRegression(data);

        } else if (cmd == "kNN") {
            int dp, x1, x2, K;
            cin >> dp >> x1 >> x2 >> K;

            vector<int> point = {x1, x2, 0};
            vector<pair<double, vector<int>>> nearestPoints = knnAlgo->getNearestPoints(point, dp, data, K);

            for (int i = 0; i < K; i++) {
                double distance = nearestPoints[i].first;
                vector<int>& point = nearestPoints[i].second;
                cout << setprecision(2) << fixed;

                cout << "K = " << i+1 << " {Distance: " << distance << "} | Nearest point: ";
                parser->printRow(point, i);
            }

            cout << setprecision(2) << fixed;
            cout << "\n=============================== PREDICTION ===============================" << endl;
            cout << "Predicted value for year: " << setprecision(0) << fixed << x1 << " and square footage: " << x2 
            << setprecision(2) << fixed << " | $" << knnAlgo->predict(x1, x2, data, dp, K) << endl;
            cout << "==========================================================================" << endl;
        } else if (cmd == "benchmark") {
            cout << endl;
            int dp;
            cin >> dp;

            int data_size = data.size();
            double lrAvgDifference = 0.0;
            double knnAvgDifference = 0.0;

            if (dp > data_size) {
                cout << "Tried to use more datapoints than were loaded in.\nOverriding datapoints to: " << data_size << endl << endl;
                dp = data_size;
            }

            int K = ceil(log(dp) + 1);
            cout << "Using K: " << K << " for kNN Algorithm." << endl;

            for (int i = 0; i < dp; i++) {
                int x1 = data[i][0];
                int x2 = data[i][1];
                int y = data[i][2];

                int knnPrediction = knnAlgo->predict(x1, x2, data, dp, K);
                int lrPrediction = lrAlgo->getMultLinearRegression(data, dp, x1, x2);

                knnAvgDifference += (y - knnPrediction);
                lrAvgDifference += (y - lrPrediction);
            }

            knnAvgDifference /= dp;
            lrAvgDifference /= dp;

            cout << setprecision(2) << fixed;
            cout << "Given " << dp << " points..." << endl << endl;
            cout << "The Multivariable Linear Regression algorithm ";

            if (lrAvgDifference > 0) cout << "overestimated ";
            else cout << "underestimated ";

            cout << "home prices by an average of $" << abs(lrAvgDifference) << "." << endl;

            cout << "The k-Nearest Neighbors algorithm ";

            if (knnAvgDifference > 0) cout << "overestimated ";
            else cout << "underestimated ";

            cout << "home prices by an average of $" << abs(knnAvgDifference) << "." << endl << endl;

            if (abs(knnAvgDifference) < abs(lrAvgDifference)) cout << "This means the k-NN algorithm made more reliable predictions than the Multivariable Linear Regression algorithm." << endl;
            else cout << "This means the Multivariable Linear Regression algorithm made more reliable predictions than the k-NN algorithm." << endl;

        } else if (cmd == "exit") break;

        cin.clear();
	}

    delete(parser);
    delete(lrAlgo);
    delete(knnAlgo);

    return 0;
}