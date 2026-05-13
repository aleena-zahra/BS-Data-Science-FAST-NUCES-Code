#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    string filename = name + ".txt";
    ofstream userfile(filename);
    ifstream questionsFile("questions.txt");
    int questionNumber = 1;
    char ch;
    int score=0;
    string question, optionA, optionB, optionC, optionD, answer;
    while (questionsFile.get(ch)) {

        while (ch != ';') {
            question += ch;
            questionsFile.get(ch);
        }

        questionsFile.get(ch); 
        while (ch != ';') {
            optionA += ch;
            questionsFile.get(ch);
        }

        questionsFile.get(ch); 
        while (ch != ';') {
            optionB += ch;
            questionsFile.get(ch);
        }

        questionsFile.get(ch); 
        while (ch != ';') {
            optionC += ch;
            questionsFile.get(ch);
        }

        questionsFile.get(ch); 
        while (ch != ';' ) { 
            optionD += ch;
            questionsFile.get(ch);
        }

        questionsFile.get(ch); 
        answer = ch;

        // Display the question and options
        cout << "\nQuestion " << questionNumber++ << ": " << question << endl;
        cout << "a) " << optionA << endl;
        cout << "b) " << optionB << endl;
        cout << "c) " << optionC << endl;
        cout << "d) " << optionD << endl;
        char userAnswer;
        cout << "Your answer (a, b, c, or d): ";
        cin >> userAnswer;
        userfile << "Question " << questionNumber - 1 << ": " << userAnswer << endl;
        
        if(userAnswer==answer[0]){
            score++;
        }
        
        // Clear the strings for the next question
        question = "";
        optionA = "";
        optionB = "";
        optionC = "";
        optionD = "";
    }
    //calculate score
    cout<<"Your score is "<<score<<" out of "<<questionNumber-1;
    userfile.close();
    questionsFile.close();


    return 0;
}

