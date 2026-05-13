#include<iostream>
using namespace std;
int getLength(string str){
    int length=0;
    for(int i=0; str[i]!='\0';i++){
        length++;
    }
    return length;
}
bool palindromeCheck(string str, int i){
    int length= getLength(str);
    // cout<<"len is "<<length<<endl;
    if (length<=1){
            return true;
        }
    if(i==length/2){
        return true;
    }
    // cout<<str[i]<<endl;
    // cout<<str[length-i-1]<<endl;
    return str[i] == str[length-i-1] && palindromeCheck(str,i+1);
        
} 
int main(){
    string sentence="";
    cout<<"enter sentence to check if its a palindrome\n";
    getline(cin,sentence);
    if(palindromeCheck(sentence,0)==true){
        cout<<"is a palindrome :))\n";
    }
    else 
        cout<<"not a palindome :(\n";
}