#include "src/csvParser.cpp"
#include "src/k-NearestNeighbor.cpp"
using namespace std;

int main() {
    csvParser* parser = new csvParser();
    kNN* knnAlgo = new kNN();

    vector<vector<int>> data;

    parser->setFile("data/simple.csv");
    parser->parseRows(data, 100000);

    // Recycled from Project 1
    int cmdsToRun = 0;
	cin >> cmdsToRun;

	for (int i = 0; i < cmdsToRun; i++) {
		string cmd;
		cin >> cmd;

		if (cmd == "printData") {  
            // Print data

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
	}

    delete(parser);
    delete(knnAlgo);

    return 0;
}