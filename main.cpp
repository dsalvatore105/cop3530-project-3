#include "src/csvParser.cpp"
using namespace std;

int main() {
    csvParser* parser = new csvParser();
    vector<vector<int>> data;

    // Recycled from Project 1
    int cmdsToRun = 0;
	cin >> cmdsToRun;

	for (int i = 0; i < cmdsToRun; i++) {
		string cmd;
		cin >> cmd;

		if (cmd == "printData") {  
            parser->setFile("data/simple.csv");
            parser->parseRows(data, 100000);

            // Print data
            for (auto& row : data) {
                for (int& point : row) cout << point;
                cout << endl;
            }
        }
	}

    return 0;
}