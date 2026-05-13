
#include <iostream>
#include <string>
using namespace std;
bool checkFind(string sentence, int p, string find){
    for(int i = 0 ; find[i]!='\0' ; i++){
        if(find[i]!=sentence[i+p]){
            return false;
        }
    }
    return true;
}
int stringLength( string& a);
void replaceSubstring(string sentence,string find, string replace){
    string replaceString="";
    int len= stringLength(find);
    for(int i=0; sentence[i]!='\0' ; i++){
        if(find[0]==sentence[i]){
            if(checkFind(sentence,i,find)){
                replaceString+=replace;
                i+=len;
            }
            else{
                replaceString+=sentence[i];
            }
        }
        else{
            replaceString+=sentence[i];
        }
    }
    cout<<replaceString<<endl;
}
      
  int main()
   {
    string find = "Pak";
    string sentence = "I am Pakistani so I support the Pakistan Cricket team in Pak-India Matches";
    string replace = "Afghan";
    cout<<"Sentence String: "<<sentence<<endl;
    cout<<"Find String: "<<find<<endl;
    cout<<"Replace String: "<<replace<<endl;
    replaceSubstring(sentence,find,replace);
    
    return 0;
    }
    int stringLength(string &a){
        int i=0;
        int count=0;
        while( a[i] != '\0'){
           i ++;
        }
        return i;
    }
    