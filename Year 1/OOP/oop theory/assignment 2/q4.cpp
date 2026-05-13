//Aleena Zahra 23i-2514 BDS-2B OOP ASSIGNMENT 2
#include<iostream>
using namespace std;

bool balancedBrackets(string str, int index, char chArr[], int arrIndex) {
    if (str[index] != '\0') {
        if (str[index] == '(' || str[index] == '{' || str[index] == '[') {
            // if the string index rn is an opening bracket then save that in char array 
            chArr[arrIndex] = str[index];
            //then check the next index of string and increase the index of char array
            return balancedBrackets(str, index + 1, chArr, arrIndex + 1);
            //if its the closing bracket then save that in a character 
        } 
        else if (str[index] == ')' || str[index] == '}' || str[index] == ']') {
            char ch = str[index];
            //if lets say theres a closing bracket at the very start then already we know that this isntt a balanced string
            if (arrIndex == 0) {
                return false;
            }
            //otherwise we check the char arr, at the index we last stored the value
            //if the answers 'match' then we check the later part of string otherwise we know its not balanced
            if ((ch == ')' && chArr[arrIndex - 1] == '(') || 
                (ch == ']' && chArr[arrIndex - 1] == '[') || 
                (ch == '}' && chArr[arrIndex - 1] == '{')) {
                return balancedBrackets(str, index + 1, chArr, arrIndex - 1);
            } 
            else {
                return false;
            }
        } 
        else {
            return balancedBrackets(str, index + 1, chArr, arrIndex);
        }
    }
    else {
        if (arrIndex == 0) {
            return true;
        }
        else return false;
    }
}

int main(){
    string str;
    cout << "Enter a string to check if its a balanced string, in terms of brackets\n";
    getline(cin, str);
    char chArr[70];
    
    if (balancedBrackets(str, 0, chArr, 0)) {
        cout << "The brackets are perfectly balanced\n";
    } else {
        cout << "The brackets ARE NOT properly balanced\n";
    }

    return 0;
}
