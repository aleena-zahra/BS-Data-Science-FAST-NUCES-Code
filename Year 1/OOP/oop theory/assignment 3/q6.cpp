//Aleena Zahra 23i-2514 BDS-B OOP Assignment 3
#include<iostream>
using namespace std;

class String{
    private:
    char *data;
    int length;

    public:
    String(){}
    String(int size){
        length = size;
        data = new char[size];
    }
    String(char* str) {
        int len=1; //for null char
        for (int i =0 ; str[i]!='\0' ; i++){
            len++;
        }
        char * ptr = new char [len];
        length = len;
        data = ptr;
        int i=0;
        for(i=0 ; i<len ; i++){
            data[i]=str[i];
        }
        data[i]='\0';   
    }
    String(const String &str){
        length = str.length;
        char *info = new char [length];
        data = info;
    }
    ~String(){
        delete[] data;
    }
    int strLength(){
        int len=1;
        for (int i =0 ; data[i]!='\0' ;i++){
            len++;
        }
        return len;
    } 
    void clear(){
        for(int i =0 ; i<length ; i++){
            data[i]='\0';
        }
        length=0;
    } 
    bool empty(){
        return data[0]=='\0';
    } 
    int charAt(char c){
        for(int i =0 ; i<length ; i++){
            if(data[i]==c){
                return i;
            }
        }
        return -1;
    } 
    char* getdata(){
        return data;
    } 
    bool equals(char*str){
        for(int i =0 ; i<length ; i++){
            if(data[i]!=str[i]){
                return false;
            }
        }
        return true;
    }
    bool equalsIgnoreCase(char* str){
        for(int i =0 ; i<length ; i++){
            if(data[i]>=65 && data[i]<=90){
                if(data[i]!=str[i] && data[i]+32 !=str[i]){
                    return false;
                }
            }
            else if(data[i]>=97 &&data[i]<=122){
                if(data[i]!=str[i] && data[i]-32 !=str[i]){
                    return false;
                }
            }
        }
        return true;
    }
    char* substring(char* substr, int startIndex){
        int subStrLen=0;
        while(substr[subStrLen]!='\0'){
            subStrLen++;
        }
        subStrLen+=1;
        cout << "\nLength of string: " << length << endl;
        char * newString = new char[length];
        newString[0] = '\0';
        int index=0;
        for(int i =startIndex ; i<length ; i++){
            if(data[i]==substr[0]){
                cout<<"\nsame at index "<<i<<endl;
                index =i;
                break;
            }
        }
        int i=0;
        for( i=0 ; i<subStrLen  ; i++){
            if(data[i+index]!=substr[i]){
                break;
            }
            newString[i]=data[i+index];       
        }    
        while(i<length){
            newString[i]=data[i+index]; 
            i++;
        }
        if (newString[0] == '\0')return NULL;
        else return newString;
    } 
    char* substring(char* substr, int startIndex, int endIndex){
        char * str = new char [endIndex-startIndex+2];
        for(int i = 0; substr[i]!='\0' ; i++){
            if(substr[i]!=data[i+startIndex]){
                return NULL;
            }
        }
        for(int i = 0 ; i+startIndex<=endIndex ; i++){
            str[i]=data[i+startIndex];
        }
        return str;
    } 
    void print(){
        if(length == 0){
            cout<<"NUll";
        }
        else{
            for(int i =0 ; i<length ; i++){
                cout<<data[i];
            }
            cout<<endl;
        }
    }
    bool startsWith(char* substr) const {
        for(int i =0 ; substr[i]!='\0' ;i++){
            if(data[i]!=substr[i]){
                return false;
            }
        }
        return true;
    }
    void concatenate(char* str){
        int newlen=0;
        while(str[newlen]!='\0'){
            newlen++;
        }
        newlen++;//null char
        cout<<"\nstring length is "<<newlen<<endl;
        char* newDataArr = new char[newlen + length];
        int i =0;
        for ( i = 0; data[i]!='\0' ; i++) {
            newDataArr[i] = data[i];
        }
        cout<<"sentence length is "<<i<<endl;
        int j=0;
        for (j=0; str[j]!='\0'; j++) {
            newDataArr[j+i] = str[j];
        }
        cout<<"concat sentence length is "<<i+j<<endl;
        newDataArr[i+j+1] = '\0';
        delete[] data;
        data = newDataArr;
        length = i+j+1;
    }
    
    bool endsWith(char* substr) const{
        int len=0;
        for(int i =0 ; substr[i]!='\0' ;i++){
            len++;
        }
        
        for(int i = len ; substr[i]>=0 ;i--){
            if(data[i]!=substr[i]){
                return false;
            }
        }
        return true;
    } 
void insert(int index, char* str){
    int strLen = 0;
    while (str[strLen] != '\0') {
        strLen++;
    }
    strLen++; 
    char* newString = new char[length + strLen];

    for (int i = 0; i < index; i++) {
        newString[i] = data[i];
    }
    for (int i = 0; i < strLen; i++) {
        newString[index + i] = str[i];
    }
    for (int i = index; i < length; i++) {
        newString[i + strLen] = data[i];
    }

    newString[length + strLen - 1] = '\0';

    delete[] data;
    data = newString;

    length += strLen - 1; 

} 
void remove(char* substr){
        int subStrLen=0;
        while(substr[subStrLen]!='\0'){
            subStrLen++;
        }
        subStrLen+=1;
        ///////////////////
        char * newString = new char[length];
        newString[0] = '\0';
        int index=0;
        for(int i =0 ; i<length ; i++){
            if(data[i]==substr[0]){
                index =i;
                break;
            }
        }
        int i=0;
        for( i=0 ; data[i]!='\0'  ; i++){
            if(data[i+index]!=substr[i]){
                newString[i]=data[i+index];}
            else {
                index ++;
            }
        } 
        newString[i]='\0';
        delete[] data;
        length=i;
        data = newString;
        return;
}
    void trim(){
        int firstIndex=0;
        int lastIndex=length-1;
        while(data[firstIndex]==' ' || data[firstIndex]=='\t' || data[firstIndex]=='\n' || data[firstIndex]=='\f' || data[firstIndex]=='\r' ){
                firstIndex++;
            }
            while(data[lastIndex]==' ' || data[lastIndex]=='\t' || data[lastIndex]=='\n' || data[lastIndex]=='\f' || data[lastIndex]=='\r' ){
                lastIndex--;
            }
        length = lastIndex - firstIndex + 1;
        for (int i = 0; i < length; i++) {
            data[i] = data[firstIndex + i];
        }
    } 
    void toUpperCase(){
        for( int i = 0 ; i< length ; i++){
            if(data[i]>=97 &&data[i]<=122){//if less than equal to z and greater than equal to a
                data[i]=data[i]-32;
            }
        }
    } 
    void toLowerCase(){
        for( int i = 0 ; i< length ; i++){
            if(data[i]>=65 && data[i]<=90){ //if greater than equal to A and less than equal to Z
                data[i]=data[i]+32;
            }
        }
    } 
};

int main(){
    char * c = new char [30];
    c="Hello World";
    char * c2 = new char [30];
    c2="hello world";
    String sentence(c);
    cout<<"initially the sentence is ";
    sentence.print();
    cout<<"\n\nafter converting to lower case the sentence is ";
    sentence.toLowerCase();
    sentence.print();
    cout<<"\n\nafter converting to upper case the sentence is ";
    sentence.toUpperCase();
    sentence.print();
    cout<<"\nthe length of this sentence is "<<sentence.strLength();
    cout<<"\n\nI can check if two sentences are equal\n";
    String sentence2(c2);
    cout<<"\nthe other sentence is ";
    sentence2.print();
    if(sentence2.equals(c)){
        cout<<"yes both sentences are equal!\n";
    }
    else {
        cout<<"\nthese sentences arent the same\n";
        if(sentence2.equalsIgnoreCase(c)){
        cout<<"\nbut both sentences are equal when IGNORING CASES!\n";
    }
    else {
        cout<<"\nthese sentences are Not the same, even after IGNORING CASES\n";
    }
    }
    cout<<"\nfind a character in the second sentence\n";
    char ch;
    cout<<"enter the character:\t";
    cin>>ch;
    cout<<"\n"<<ch<<" found at index "<< sentence2.charAt(ch)<<" , -1 means not found\n";
    cout<<"\nconcatinating at the end of second sentence\n";
    char* substr = new char [4];
    substr=" <3";
    sentence2.concatenate(substr);
    sentence2.print();
    cout<<"trimming second sentence to remove whitespaces from the start and end..\n";
    sentence2.trim();
    cout<<"now the sentence is: \t";
    sentence2.print();
    while(!sentence.empty()){
    cout<<"\nright now the first sentence isnt empty\n";
    cout<<"\nnow clearing the sentence..\n";
    sentence.clear();
    }
    cout<<"\nsentence is ";
    sentence.print();
    
    //////////////////////////////////////////////////
    String str("awesome");
    char* firstSubStr = str.substring("es", 0);
    if (firstSubStr != NULL) cout << "Substring "<<firstSubStr<<" has been found"<< endl;
    else cout << "Substring not found." << endl;
    delete[] firstSubStr;
    ////////other substring thingy
    char* newSubStr = str.substring("es", 2, 5);
    if (newSubStr != NULL) cout << "Substring "<<newSubStr<<" has been found"<< endl;
    else cout << "Substring not found." << endl;
    char c4[4] = "awe";
    cout<<"\n After removing awe from awesome the string is:\t";
    str.remove(c4);
    str.print();
    char c5[3] = "aw";
    cout<<"\n After inserting aw at index 0 the string is:\t";
    str.insert(0,c5);
    str.print();
    delete[] newSubStr;
    return 0;
}