#include "csvParser.cpp"
using namespace std;

int main() {
    csvParser* parser = new csvParser();
    vector<vector<int>> data;

    parser->setFile("simple.csv");
    parser->parseRows(data, 4);

    //Print data
    for (auto& row : data) {
        for (int& point : row) cout << point;
        cout << endl;
    }

    return 0;
}