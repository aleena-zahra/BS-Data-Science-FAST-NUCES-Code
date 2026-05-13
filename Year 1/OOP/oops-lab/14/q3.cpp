#include<iostream>
#include<string>
using namespace std;

void reverseString(string str);
int getLength(string str);

int main() {
    string sentence;
    cout << "INPUT\n";
    getline(cin, sentence);
    cout << "\nOutput\n";
    reverseString(sentence);
    
    return 0;
}

void reverseString(string str) {
    string word,newSentence;
    for (char c : str) {
        if (c == ' ') {if ((getLength(word)) % 2 == 1) {
                string reversedWord;
                for (int i = (getLength(word)) - 1; i >= 0; i--){reversedWord += word[i];}
                newSentence += " " + reversedWord;
            } else newSentence += " " + word;
            word = ""; 
        } else word += c; }
    // Process the last word
    if ((getLength(word)) % 2 == 1) {string reversedWord;
        for (int i = (getLength(word)) - 1; i >= 0; i--) {reversedWord += word[i];}
        newSentence += " " + reversedWord;
    } else newSentence += " " + word;
    cout << newSentence << endl;
}

int getLength(string str) {
    int length = 0;
    for (char c : str) {
        length++;
    }
    return length;
}
