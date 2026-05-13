#include<iostream>
#include<string>
using namespace std;

void reverseString(string str);
int getLength(string str);
int main(){
    string sentence;
    cout<<"INPUT\n";
    getline(cin, sentence);
    cout<<"\nOutput\n";
    reverseString(sentence);
    
    return 0;
}
void reverseString(string str){
    string word="" ,revSen = "";
    for(char c: str) if(c==' '){
        revSen = word + " " +revSen;
        word = "";
    }else word +=c;
    revSen= word + " " +revSen;
    cout<<revSen<<endl;

}

