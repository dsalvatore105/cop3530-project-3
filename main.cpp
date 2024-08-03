#include "src/csvParser.cpp"
#include "src/k-NearestNeighbor.cpp"
#include "src/LinearRegression.cpp"
using namespace std;

int main() {
    csvParser* parser = new csvParser();
    LR* lrAlgo = new LR();
    kNN* knnAlgo = new kNN();

    vector<vector<int>> data;

    //parser->setFile("data/simple.csv");
    //parser->parseRows(data, 100000);

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
            parser->setFile("data/csvs/totaldata.csv");
            parser->parseRows(data, 50);
        } else if (cmd == "lr") {
            // displays function info
            int dp;
            double x1, x2;
            cin >> dp >> x1 >> x2;
            
            cout << setprecision(2) << fixed;
            cout << "Predicted value for year " << x1 << " and square footage " << x2 << ": "
            << lrAlgo->getMultLinearRegression(data, dp, x1, x2) << endl;

            //lrAlgo->getLinearRegression(data);
        } else if (cmd == "kNN") {
            int K = 2;
            vector<pair<double, vector<int>>> nearestPoints = knnAlgo->getNearestPoints(data[0], data, K);

            for (int i = 0; i < K; i++) {
                double distance = nearestPoints[i].first;
                vector<int>& point = nearestPoints[i].second;
                cout << setprecision(2) << fixed;

                cout << "K = " << i+1 << " {Distance: " << distance << "} | Nearest point: ";
                parser->printRow(point);
            }
        } else if (cmd == "predict_kNN") {
            int x;
            cout << "Find price for what square footage?: ";
            cin >> x;
            
            int K;
            cout << "K Value: ";
            cin >> K;

            cout << knnAlgo->predict(x, data, K) << endl; // just use one variable for now
        }
        cin.clear();
	}

    delete(parser);
    delete(lrAlgo);
    delete(knnAlgo);

    return 0;
}