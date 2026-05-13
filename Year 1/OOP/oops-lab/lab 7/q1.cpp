#include<iostream>
using namespace std;
struct student{
    int rollNo;
    string name;
    float marks;
};
void inputStudentRecord(int totalStudents,student* arr){
    for(int i =0 ; i<totalStudents ; i++){
        cout<< "Roll no of Student "<<i+1<<":\n";
        cin>> arr[i].rollNo;
        cout<< "Name of Student "<<i+1<<":\n";
        cin>> arr[i].name;
        cout<< "Marks of Student "<<i+1<<":\n";
        cin>> arr[i].marks;
    }
}
void displayStudentRecord(int totalStudents, student* arr){
    for(int i =0 ; i<totalStudents ; i++){
        cout<< "Roll no of Student "<<i+1<<" : "<<arr[i].rollNo<<endl;
        cout<< "Name of Student "<<i+1<<" : "<<arr[i].name<<endl;
        cout<< "Marks of Student "<<i+1<<" : "<<arr[i].marks<<endl;
    } 
}
int main(){
    int totalStudents;
    cout<<"Enter number of students:\t";
    cin>>totalStudents;
    student *arr = new student[totalStudents]; 
    inputStudentRecord(totalStudents,arr);
    displayStudentRecord(totalStudents,arr);

}