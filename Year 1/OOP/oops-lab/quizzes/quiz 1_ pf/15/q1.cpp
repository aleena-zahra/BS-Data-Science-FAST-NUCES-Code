#include<iostream>
#include<fstream>
using namespace std;
void vowelWords();
int main(){
    
    vowelWords();
    return 0;
}
void vowelWords(){
    ifstream infile("first.txt");
    ofstream outfile("second.txt");
    string word;
    while(infile>>word){
        if(word[0]=='a'||word[0]=='e'||word[0]=='i'||word[0]=='o'||word[0]=='u'){
            outfile<<word<<" ";
        }
    }
    infile.close();
    outfile.close();
    
}