#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
int main() {
    ifstream inputFile("example.csv");

    if (!inputFile.is_open()) {
        cout << "Failed to open file!" << endl;
        return 1;
    }
    string line;
    //Max Rows
    const int ROWS = 1;
    int row = 0;
    while (getline(inputFile, line)) {
        if (row >= ROWS) {
            cout << "Maximum number of rows exceeded!" << endl;
            break;
        }

        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ',')) 
		{
        	cout<<" "<<cell;
        }
        cout<<endl;
    }
    inputFile.close();

    return 0;
}

