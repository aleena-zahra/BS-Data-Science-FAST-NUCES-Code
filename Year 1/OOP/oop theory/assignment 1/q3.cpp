/*Aleena Zahra 23i-2514 BDS-2B Assignment 1 OOP*/
#include<iostream>
#include<string>
using namespace std;
void LookAndSaySequence(string numString, int totalTerms,int numberOfTermsLeft);
int getLength(string str);
int main() {
    int startingNum;
    int numberOfTerms;
    int totalTerms;
    cout<<"This program generates a Look-and-Say sequence\n";
    do{
    cout << "Enter the (positive) starting number:\n";
    cin >> startingNum;
    }while(startingNum <= 0 );
    do{
    cout << "Enter the (positive) number of terms:\n";
    cin >> numberOfTerms;
    }while(numberOfTerms <= 0);
    string numString = to_string(startingNum);
    cout<<"Generating Look and Say Pattern..\n";
    LookAndSaySequence(numString, numberOfTerms,numberOfTerms);
    cout << "Look-and-Say sequence generation complete.\n";
    return 0;
}

void LookAndSaySequence(string numString, int totalTerms,int numberOfTermsLeft){
    if (numberOfTermsLeft==totalTerms){
        cout<<numString<<endl;
        LookAndSaySequence(numString, totalTerms,numberOfTermsLeft-1);
    }
    else if (numberOfTermsLeft>0){
        int countOccurences=1;
        string sequenceStr="";
        int numStringLenght=getLength(numString);
        for (int i = 0; i < numStringLenght; i++) {
            if (i + 1 < numStringLenght && numString[i] == numString[i + 1]) {
                countOccurences++;
            } else {
                sequenceStr += to_string(countOccurences) + numString[i];
                countOccurences = 1; // Reset count
            }
        }
        int maxLengthOfSequence=19;
        if (getLength(sequenceStr)>maxLengthOfSequence){
            cout<<"Overflow occured!!\n";
        }
        else{
            numString=sequenceStr;
            cout<<numString<<endl;
            LookAndSaySequence(numString, totalTerms,numberOfTermsLeft-1);
        }
    }
    
}

int getLength(string str){
    int length=0;
    for( int i=0 ; str[i] !='\0' ; i++){
        length++;
    }
    return length;
}