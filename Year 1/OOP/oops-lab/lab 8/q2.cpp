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
struct examroom {
    int numRows;
    int numCols;
    student *students;
    student** seatingArrangement;
    void inputStudentsRecord(int n) {
    students = new student[n];
        for (int i =0 ; i<n ; i++){
            cout<<"Enter info of student "<<i+1<<endl;
            cout<<"Enter name: \t";
            string name;
            getline(cin>>ws, name);
            cout<<"Enter roll no: \t";
            int rollno;
            cin>>rollno;
            cout<<"Enter street Address: \t";
            string streetAddress;
            getline(cin>>ws, streetAddress);
            cout<<"Enter zipcode: \t";
            int zipcode;
            cin>>zipcode;
            students[i].setStudentInfo(name,rollno,streetAddress,zipcode);
           // students->displayStudentInfo();
        }
    }
    void studentsRecordInAscending(student* studentsArr , int length, int i , int j){
        //base case for when we reach the end 
    if (i == length - 1) 
        return;
    if (j == length - i - 1) 
        return studentsRecordInAscending(studentsArr, length, i + 1, 0); 
    //swapping
    if (studentsArr[j].rollNo > studentsArr[j + 1].rollNo) {
        int temp = studentsArr[j].rollNo;
        studentsArr[j].rollNo = studentsArr[j + 1].rollNo;
        studentsArr[j + 1].rollNo = temp;
    }
    studentsRecordInAscending(studentsArr, length, i, j + 1); 
    }
    void displaySeatingPlan(){
        cout<<endl;
        for (int i = 0 ; i < numRows ; i++){
            for( int j =0 ; j < numCols ; j++){
                cout<<seatingArrangement[i][j].name<<"  ";
            }
            cout<<endl;
        }
    }
    void makeSeatingPlan(int rows, int cols) {
        numRows = rows;
        numCols = cols;
        studentsRecordInAscending(students, numRows+numCols,0,0);
        seatingArrangement = new student*[numRows];
        for (int i = 0; i < numRows; i++) {
            seatingArrangement[i] = new student[numCols];
        }
        int k =0 , temp =0;
        for (int j =0 ; j < numCols ; j++){
            for(int i = numRows-1 ; i >= 0 ; i--){
                seatingArrangement[i][j] = students[k]; 
                k++;
            }       
        }
    }
};
int main(){
    examroom CIEExamRoom;
    int numberOfStudents =4;
    int numberOfRows =2;
    int numberOfColumns =2;
    CIEExamRoom.inputStudentsRecord(numberOfStudents);   
    CIEExamRoom.makeSeatingPlan(numberOfRows,numberOfColumns);
    CIEExamRoom.displaySeatingPlan();

    return 0;
}