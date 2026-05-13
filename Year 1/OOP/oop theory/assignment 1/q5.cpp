/*Aleena Zahra 23i-2514 BDS-2B Assignment 1 OOP*/
#include<iostream>
using namespace std;
void allocateMemory(char *&arr,int length);
void deallocateMemory(char *arr);
int getLength(string str);
bool compare(const char* a, const char* b);
int len(const char* arr1);
char* convert(const string& str);
bool compare(const char* a, const char* b);
char* concat(const char* a,const char* b);
int main(){
    string patternStr = "", str = "";
    char *charArr;
    char *patternCharArr;
    cout<<"Enter a string:\t";
    cin>>str;
    charArr = convert(str);
    cout<<"\nEnter a pattern:\t";
    cin>>patternStr;
    patternCharArr = convert(patternStr);
    int lengthOfCharArr= len(charArr);
    char *matchedArr;
    allocateMemory(matchedArr,lengthOfCharArr);
    int k=0,j=0,i=0;
    while(i<lengthOfCharArr-1){
        if(patternStr[j]!='*'){
            bool checkBool = compare(&charArr[i],&patternCharArr[j]);
            if(checkBool==true){
                matchedArr = concat(matchedArr, &charArr[i]);
            }
            j++;
        }
        else{
            matchedArr = concat(matchedArr, &charArr[i]);
            char c;
            c=charArr[i];
            while(charArr[i]==c){
                i++;
            }
            i--;
            j++;   
        }
        i++;
    }
    cout<<"Characters that match in both arrays are "<<matchedArr;
    //int l1= len(matchedArr);
    deallocateMemory(matchedArr);
    //int l2= len(charArr);
    deallocateMemory(charArr);
    //int l3= len(patternCharArr);
    deallocateMemory(patternCharArr);
    return 0;
}
void allocateMemory(char *&arr,int length){
    arr = new char[length];
}
void deallocateMemory(char *arr) {
    delete[] arr;
}
bool compare(const char* a, const char* b){
    if(*a == *b || *b =='#'){
        return true;
    }
    else return false;
}
char* convert(const string& str){
    int length=len(&str[0]);
    char *arr;
    arr = new char[length];
    //copy elements 
    for(int i = 0; i < length - 1; i++) {
        arr[i] = str[i];
    }
    arr[length - 1] = '\0';
    return arr;
}
int len(const char* arr1){
    int length=0;
    for(int i=0 ; arr1[i]!='\0';i++){
        length++;
    }
    return ++length;//for \0
}
char* concat(const char* a,const char* b){
    int length=len(a);
    char *resultArr;
    allocateMemory(resultArr,length+2);
    //copy elements 
    for (int j = 0; j < length-1; j++) {
        resultArr[j] = a[j];
    }
    resultArr[length-1] = *b;
    resultArr[length] = '\0';
//    cout<<"the result arr is "<<resultArr<<endl;
    return resultArr;

}
