#include<iostream>
using namespace std;
struct address {
    string street;
    int zipCode;
};
struct student{
    string name;
    int rollNo;
    address addressOfStudent;

    void setStudentInfo( const string& nameOfStudent , int rollNumber , const string& streetOfResidency, int zipCodeOfStudent){
        name = nameOfStudent;
        rollNo = rollNumber;
        addressOfStudent.street = streetOfResidency;
        addressOfStudent.zipCode = zipCodeOfStudent; 
    }
    void displayStudentInfo(){
        cout<<"The name of the student is "<<name<<endl;
        cout<<"The roll number of the student is "<<rollNo<<endl;
        cout<<"The address of the student is: "<<endl;
        cout<<"Street Address: "<<addressOfStudent.street<<endl;
        cout<<"Zip Code: "<<addressOfStudent.zipCode<<endl;
    }
};
int main(){
    student john;
    john.setStudentInfo("john",231514,"123 Main Street", 4562);
    john.displayStudentInfo();

}
