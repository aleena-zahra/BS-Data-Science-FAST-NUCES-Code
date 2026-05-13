#include<iostream>
#include<string>
using namespace std;

void removeWord(string str,string wordToRemove);

int main(){
    string sentence;
    string wordToRemove;
    cout<<"enter sentence\n";
    getline(cin, sentence);
    cout<<"Enter word to remove";
    cin>>wordToRemove;
    cout<<"\nOutput\n";
    removeWord(sentence,wordToRemove);
    
    return 0;
}
void removeWord(string str, string wordToRemove){
    string word,newSentence;
    for(char c: str){ if(c ==' '){ if( word == wordToRemove) word="";
        else newSentence = newSentence + " " + word;
        word="";}
        else word +=c;
    }
    newSentence = newSentence+ " " + word;
    cout<<newSentence;
}