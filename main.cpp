#include "src/csvParser.cpp"
#include "src/k-NearestNeighbor.cpp"
#include "src/LinearRegression.cpp"
using namespace std;

int main() {
    csvParser* parser = new csvParser();
    LR* lrAlgo = new LR();
    kNN* knnAlgo = new kNN();

    vector<vector<int>> data;

    // Recycled from Project 1
    int cmdsToRun = 0;
	cin >> cmdsToRun;

	for (int i = 0; i < cmdsToRun; i++) {
		string cmd;
		cin >> cmd;

		if (cmd == "printData") {  
            // Print data
            parser->printData(data);
        } else if (cmd == "load"){
            // Load data
            int count;
            cin >> count;

            parser->setFile("data/csvs/totaldata.csv");
            parser->parseRows(data, count);
        } else if (cmd == "lr") {
            // displays function info
            int dp;
            double x1, x2;
            cin >> dp >> x1 >> x2;
            
            cout << setprecision(2) << fixed;
            cout << "Predicted value for year " << x1 << " and square footage " << x2 << ": " << lrAlgo->getMultLinearRegression(data, dp, x1, x2) << endl;

            //lrAlgo->getLinearRegression(data);
        } else if (cmd == "kNN_debug") {
            /*
            int K = 2;
            vector<pair<double, vector<int>>> nearestPoints = knnAlgo->getNearestPoints(data[0], data[1], data, K);

            for (int i = 0; i < K; i++) {
                double distance = nearestPoints[i].first;
                vector<int>& point = nearestPoints[i].second;
                cout << setprecision(2) << fixed;

                cout << "K = " << i+1 << " {Distance: " << distance << "} | Nearest point: ";
                parser->printRow(point);
            }
            */
        } else if (cmd == "kNN") {
            int dp, x1, x2, K;
            cin >> dp >> x1 >> x2 >> K;

            cout << setprecision(2) << fixed;
            cout << "Predicted value for year " << x1 << " and square footage " << x2 << ": " << knnAlgo->predict(x1, x2, data, dp, K) << endl;
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

                //cout << "LR Prediction: " << lrPrediction << endl;
                //cout << "KNN Prediction: " << knnPrediction << endl;
                //cout << "Real value: " << y << endl; 

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
        }
        cin.clear();
	}

    delete(parser);
    delete(lrAlgo);
    delete(knnAlgo);

    return 0;
}