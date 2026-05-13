#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
    ofstream file("Dataset.csv");

    string positive[] = {"good","excellent","great","amazing","love"};
    string negative[] = {"bad","terrible","worst","awful","poor"};
    string product[]  = {"ai","model","algorithm","system","software"};
    string feature[]  = {"performance","accuracy","speed","memory","training"};

    int studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;

    srand(studentID);

    int datasetSize = 40000 + (studentID % 30000);

    for(int i = 0; i < datasetSize; i++)
    {
        int length = rand() % 10 + 5;
        for(int j = 0; j < length; j++)
        {
            int type = rand() % 4;
            if(type == 0) file << positive[rand() % 5] << " ";
            else if(type == 1) file << negative[rand() % 5] << " ";
            else if(type == 2) file << product[rand() % 5] << " ";
            else file << feature[rand() % 5] << " ";
        }
        file << "\n";
    }

    file.close();
    cout << "Dataset generated.\n";
}