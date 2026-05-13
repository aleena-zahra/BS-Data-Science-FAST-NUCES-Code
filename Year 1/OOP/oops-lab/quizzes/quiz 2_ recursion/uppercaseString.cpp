#include<iostream>
using namespace std;
char upperCase(string str,int i=0);
int getLength(string str){
    int length=0;
    for(int i=0; str[i]!='\0';i++){
        length++;
    }
    return ++length;
}

char upperCase(string str,int i){
    int length=getLength(str);
    if(i!=length){
        if(str[i]>='A' && str[i]<='Z'){
            cout<<"the upper case letter in string is "<<str[i]<<" ";
            return &str[i];
        }
        else{
            i++;
            upperCase(str,i);
        }
    }
    return 0;

}
int main(){
    string sentence="";
    cout<<"enter sentence to check upperCase Letter\n";
    getline(cin,sentence);
    int i=0;
    cout<<"the upper case letter in string is "<<(upperCase(sentence,i));
}