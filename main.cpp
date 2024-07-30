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
            for (auto& row : data) {
                for (int& point : row) cout << point;
                cout << endl;
            }
        } else if (cmd == "kNN") {
            knnAlgo->printPoint(data[0]);
            knnAlgo->getNearestPoints(data[0], data, 2);
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

    return 0;
}