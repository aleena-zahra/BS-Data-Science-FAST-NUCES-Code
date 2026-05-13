#include <iostream>
#include <string>
using namespace std;

    int stringLength( string& a,int count,int i);
    bool checkSubstring(string sentence,int p,string find,int i);
    void replaceSubstring(string sentence,int sentenceIndex,string find,string replace, string resultant,int findLength);
    int main(){
        string find = "Pak";
        string sentence = "I am Pakistani so I support the Pakistan Cricket team in Pak-India Matches";
        string replace = "Afghan";
        cout<<"Sentence String: "<<sentence<<endl;
        cout<<"Find String: "<<find<<endl;
        cout<<"Replace String: "<<replace<<endl;
        string resultantString = "";
        int findLength = stringLength(find,0,0);
        replaceSubstring(sentence,0,find,replace,resultantString,findLength);
        
        return 0;
    }
    int stringLength(string &a,int count,int i){
        if(a[i]=='\0'){
            return count;
        }
        else {
            return stringLength(a,count+1,i+1);
        }
    }
    bool checkSubstring(string sentence, int sentenceIndex, string find, int findIndex) {
    // Base cases
    if (find[findIndex] == '\0')
        return true;
    if (sentence[findIndex + sentenceIndex] != find[findIndex])
        return false;
    return checkSubstring(sentence, sentenceIndex, find, findIndex + 1);
}

    void replaceSubstring(string sentence,int sentenceIndex,string find,string replace, string resultant,int findLength){
        if (sentence[sentenceIndex] == '\0') {
            cout << resultant << endl;
            return;
        }
        else if (checkSubstring(sentence, sentenceIndex, find,  0)) {
            resultant += replace;
            replaceSubstring(sentence, sentenceIndex + findLength,find, replace, resultant, findLength);
        } 
        else {
            resultant += sentence[sentenceIndex];
            replaceSubstring(sentence, sentenceIndex + 1,find, replace, resultant, findLength);
        }
    }