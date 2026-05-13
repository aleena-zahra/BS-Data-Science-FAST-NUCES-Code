//Aleena Zahra 23i-2514 BDS-2B OOP ASSIGNMENT 2
#include<iostream>
using namespace std;
void convertToCaps(string &word,int i);
void convertToCode(string &word,int i);
void removeDuplicates(string &code,string &word,int i);
void removeZeros(string &code,string &word, int i);
void addZeros(string &code, int i);
void sontexCode(string word){
    string code="";
    string removeZero="";
    string finalstr="";
    
    convertToCaps(word,0);
    convertToCode(word,0);
    removeDuplicates(code,word,0);
    removeZeros(removeZero,code,0);
    addZeros(removeZero,0);
    cout<<"The code for your name is "<<removeZero;
}
int main(){
    string word="";
    cout<<"Enter a word:\t";
    cin>>word;
    sontexCode(word);
}
    void convertToCaps(string &word,int i){
        if(word[i] != '\0'){
            if(word[i]>=97){
            word[i]=word[i]-32;
        }
            convertToCaps(word,i+1);
        }
        else return;
        
    }
    void convertToCode(string &word,int i){
        if(word[i] != '\0'){
            if(i == 0){
                word[i]= word[i];
            }
            else if(word[i] == 'A' || word[i] == 'E' || word[i] == 'I'|| word[i] == 'O'|| word[i] == 'U'|| word[i]=='H'|| word[i]=='Y'){
                word[i] ='0';
            }
            else if(word[i] == 'B' || word[i] == 'F' || word[i] == 'P'|| word[i] == 'V'){
                word[i] ='1';
            }
            else if(word[i] == 'C' || word[i] == 'G' || word[i] == 'J'|| word[i] == 'K'|| word[i] == 'Q'|| word[i]=='S'|| word[i]=='X'|| word[i]=='Z'){
                word[i] ='0';
            }
            else if(word[i]=='D' || word[i]=='T'){
                word[i] ='3';
            }
            else if(word[i]=='M' || word[i]=='N'){
                word[i] ='4';
            }
            else if(word[i]=='L'){
                word[i] ='5';
            }
            if(word[i]=='r'){
                word[i] ='6';
            }
            convertToCode(word,i+1);
        }
        else return;
            
    }
    void removeDuplicates(string &code,string &word,int i){
        if(word[i] != '\0'){
            while( word[i] == word[i+1]){
                i++;
            }
            code+=word[i];

            
            removeDuplicates(code,word,i+1);
        }
        else return;
    }
    void removeZeros(string &code,string &word, int i){
        if(word[i] != '\0'){
            //cout<<word[i];
            if( word[i] != '0'){
            
                code+=word[i];
                
            }
            
            removeZeros(code,word,i+1);
        }
        else return;
    }
    void addZeros(string &code, int i){
    if(code.length() < 4){
        code += '0';
        addZeros(code, i+1);
    }
}
        
    
