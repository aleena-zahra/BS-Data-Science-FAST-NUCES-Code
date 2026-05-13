#include <iostream>
using namespace std;

class StudentRegistry
{
    int *students;
    int totalStudents;

public:
    StudentRegistry()
    {
        students = nullptr;
        totalStudents = 0;
    }
    StudentRegistry(int *students,  int size)
    {
        totalStudents = size;
        this->students = new int[totalStudents];
        for (int i = 0; i < size; i++)
        {
            this->students[i] = students[i];
        }
    }
    StudentRegistry(const StudentRegistry &copy)
    {
        this->totalStudents = copy.totalStudents;
        this->students = new int[totalStudents];
        for (int i = 0; i < this->totalStudents; i++)
        {
            this->students[i] = copy.students[i];
        }
    }
    ~StudentRegistry()
    {
        delete [] students;
    }
   
    void printList()
    {
        cout << "\n\t\t\tSTUDENT RECORD\n";
        cout << "---------------------------------------------------------------------";
        for (int i = 0 ; i<totalStudents ; i++)
        cout << "\nStudent ID: " << students[i];
        cout << "\n---------------------------------------------------------------------\n\n";
    
    }
    //Insert studentID into the List. Ensure
    //the list remains sorted.
    void addStudent(int studentID)
    {
        int tempSize = this->totalStudents+1;
        int *tempstudents = new int[tempSize];
        int i=0;
        for( i = 0 ; i<totalStudents ; i++){
            tempstudents[i] = students[i];
        }
        tempstudents[i] = studentID;
        delete [] students;
        students = tempstudents;
        this->totalStudents = tempSize;
        
    }
    void removeStudent(int studentID)
    {
        int tempSize = this->totalStudents-1;
        int *tempstudents = new int[tempSize];
        int index=0,i=0;
        while(students[i]!=studentID){
                tempstudents[i] = students[i];
                i++;
            }
        while(i<totalStudents){
            tempstudents[i] = students[i+1];
            i++;
        }
        delete [] students;
        students = tempstudents;
        this->totalStudents = tempSize;
        
    }

    //Linear Search
    int findstudent(int studentID) const
    {
        for(int i = 0 ;i<totalStudents ; i++){
            if(students[i]==studentID){
                return i;
            }
        }
        return -1; 
    }

};
int main()
{
    int size =5;
    int students[size] = {2100,2894,2352,2500,2543};
    StudentRegistry nerdyStudents(students,size);
    cout<<"Originally students are:\n";
    nerdyStudents.printList();
    nerdyStudents.addStudent(2033);
    cout<<"After adding student with ID 2033:\n";
    nerdyStudents.printList();
    int studentID = 0;
    cout<<"Enter a Student ID to search in the book nook library List:";
    cin>>studentID;
    if(nerdyStudents.findstudent(studentID) != -1){
        cout<<"\nThe list contains this Student ID\n";
        nerdyStudents.removeStudent(studentID);
       
    }
    else {
        cout<<"Student not avaliable\n";
        studentID = 2500;
        nerdyStudents.removeStudent(studentID);
        
        }
    cout<<"Student with ID "<<studentID<<" has been removed:";
    nerdyStudents.printList();
    
    return 0;
}