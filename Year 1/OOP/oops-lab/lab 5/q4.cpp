#include<iostream>
#include<string>
using namespace std;
int getLength(string str){
    int length=0;
    for (int i=0; str[i]!='\0'; i++){
        length++;
    }
    return length;
}
int consonantCount(string str,int index=0){
    if(index!= (getLength(str))){
        if(str[index]!='a' && str[index]!='e' && str[index]!='i' && str[index]!='o' && str[index]!='u'){
            return 1 + consonantCount(str,index+1);
        }
        else {
            return 0+consonantCount(str, index+1);
        }
    }
    else return 0;
}
