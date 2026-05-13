#include<iostream>
#include<fstream>
#include <string>
using namespace std;

  bool isPasswordStrong(char *);
  void RegisterUser();
  void LoginUser();
  int DisplayMenu();
  bool CheckCapitalLetters( char*,int password);
  bool CheckSmallLetters(char*,int password);
  bool CheckSpecialChars(char*,int password);
  bool CheckNum(char*, int password);
  int StringLength(char*);
  int main(){
    int userInput;
    userInput = DisplayMenu();
    if (userInput != 3){
      DisplayMenu();
    }
    return 0;
    }
  int DisplayMenu(){
    cout<<"Press 1 to Register\n";
    cout<<"Press 2 to Login\n";
    cout<<"Press 3 to Exit\n";
    int userNum;
    cin>>userNum;
    if (userNum ==1){
      RegisterUser();
    }
    if (userNum ==2){
      LoginUser();
    }
    if (userNum ==3){
      return 3;
    }
    return 3;
  }
  void RegisterUser(){

    string name,email,username,age;
    char password[15];
    cout<<"Enter your name";
    cin>>name;
    cout<<"\nEnter your email";
    cin>>email;
    cout<<"\nEnter your username";
    cin>>username;
    cout<<"\nEnter your password";
    cin>>password;
    bool validPassword = isPasswordStrong(password);
    while (!validPassword){
      cout<<"\nInvalid Password. Enter your password";
      cin>>password;
    }
    cout<<"\nEnter your age";
    cin>>age;
    
    //after getting valid Password store info in file
    string fileName=name+".txt";
    ofstream file;
    file.open(fileName);
    file << "name: "<< name<<endl;
    file<<"age: "<< age << endl;
    file<<"email: "<<email<< endl;
    file<<"username: "<< username<<endl;
    file<<"password: "<< password <<endl;
        
 }
  bool isPasswordStrong(char *password){
   int passwordLength = StringLength(password);
   if (passwordLength<4){
      return false;
   }
   if( CheckSpecialChars(password,passwordLength) &&  CheckNum(password,passwordLength) 
   && CheckCapitalLetters(password,passwordLength) &&  CheckSmallLetters(password,passwordLength))
   return true;
   else return false;
  }
  
  bool CheckCapitalLetters(char *password, int passwordLength ){
    bool capLetter=false;
    for (int i =0 ; i< passwordLength ; i++){
      if(password[i] >= 'A' && password[i] <= 'Z') 
      capLetter=true;
    }
    return capLetter;
  }
  bool CheckSmallLetters(char *password, int passwordLength){
    bool smallLetter = false;
    for (int i =0 ; i< passwordLength ; i++){
      if(password[i] >= 'a' && password[i] <= 'z') 
      smallLetter=true;
    }
    return smallLetter;
  }
  bool CheckSpecialChars(char *password, int passwordLength){
    bool specialChar=false;
    for (int i =0 ; i< passwordLength ; i++){
      if(password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%' || password[i] == '(' || password[i] == ')'
         || password[i] == '+' || password[i] == '='  || password[i] == '-' || password[i] == '!' || password[i] == '&' || password[i] == '*') 
        specialChar=true;
    }
    return specialChar;
  }
  bool CheckNum(char *password, int passwordLength){
    bool number=false;
    for (int i =0 ; i< passwordLength ;i++){
      if(password[i] >= '0' && password[i] <= '9') 
      number=true;
    }
    return number;
  }
   
  int StringLength(char* a){
    int i=0;
    int count=0;
    while( a[i] != '\0'){
      i ++;
      count++;
    }
    return count;
  }

  void LoginUser(){

    string loginUsername,loginPassword,loginName;

    cout<<"Enter your login credentials\n";
    cout<<"Enter your name:\t";
    cin>>loginName;
    cout<<"Enter your username:\t";
    cin>>loginUsername;
    cout<<"Enter your password:\t";
    cin>>loginPassword;

    string fileName=loginName+".txt";
    fstream file;
    file.open(fileName,ios::out | ios::in);
    
    //read contents of file line by line
    
    if(file.is_open()){
  
      string name,age,email,username,password,temp;
      (getline(file, name ));
      (getline(file, age ));
      (getline(file, email ));
      // cant get line anymore as that would include "username: ", and not just the username
      file >> temp;
			file >> username;
			file >> temp;
			file >> password;
       
      //check if username and password trying to login with are the same as in the file
      if(username==loginUsername && password==loginPassword)
      {
        //display file information
        cout<<"LOGIN SUCCESSFUL\n\n";
        cout << name<<endl;
        cout << age << endl;
        cout << email<< endl;
        cout << username<<endl;
        cout << password <<endl;

      }
      else
        cout << "Login Failed\n";
    }
    //if file doesnt exist
    else if (!file){
      cout<<"Unable to Login. No such file found";
    }
  }

