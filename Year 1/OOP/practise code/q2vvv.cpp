// Aleena Zahra 23i-2514 BDS-B OOP Assignment 3
#include <iostream>
#include<string>
using namespace std;
class Student{
    int studentID;
    string name;
    string* courseCodes;
    int numOfCourses;
    int* courseGrades;
    float GPA;

public:
    Student(){
         studentID=0;
         name="";
         courseCodes=nullptr;
         numOfCourses=0; 
         courseGrades=nullptr; 
         GPA = 0.0;
         cout<<"default constructor called\n";
    }
    Student(int studentId, string studentName ){
        studentID = studentId;
        name = studentName;
    }
    Student(int studentId, string studentName, int totalSubjects,string *courseNames,int *marks ){
        studentID = studentId;
        name = studentName;
        numOfCourses = totalSubjects;
        courseGrades = new int [numOfCourses];
        courseCodes = new string [numOfCourses];
        cout<<"2 dma arrays of size "<<numOfCourses<<" made\n";
        for (int i = 0; i < numOfCourses; i++) {
        courseCodes[i] = courseNames[i];
        courseGrades[i]= marks[i];
    }
    }
    ~Student() {
        delete[] courseGrades;
        delete[] courseCodes;
    }
    int getStudentID()
    {
        return studentID;
    }
    string getName()
    {
        return name;
    }
    int getNumOfCourses()
    {
        return numOfCourses;
    }
    string getCourseCode(int i) {
        if (i >= 0 && i < numOfCourses && courseCodes != nullptr) {
            cout<<"Course code "<<i<<" is "<<courseCodes[i]<<endl;
        return courseCodes[i];
    } else {
        return ""; 
    }   
    }
    int getCourseGrade(int i) {
        return courseGrades[i];
    }
    float getGPA()
    {
        return GPA;
    }
    void setStudentID(int id)
    {
        studentID = id;
    }
    void setName(string firstName)
    {
        name = firstName;
    }
    void setCourseGrade(string courseCode, int grade) {
        for (int i = 0; i < numOfCourses; i++) {
            cout<<"i is "<<i<<endl;
            if (courseCodes[i] == "") {
                cout<<"CourseCode is "<<courseCode<<endl;
                cout<<"courseCodes[i] is "<<courseCodes[i]<<"|"<<endl;
                courseCodes[i] = courseCode; //segmentation fault here
                courseGrades[i] = grade;
                return;
            }
        }
    } 
    void addCourse(string courseCode, int grade) {
        string* tempCourseCodes = new string[numOfCourses];
    int* tempCourseGrades = new int[numOfCourses];
    //copying the dAtAz
    for (int i = 0; i < numOfCourses - 1; ++i) {
        tempCourseCodes[i] = courseCodes[i];
        tempCourseGrades[i] = courseGrades[i];
    }
    tempCourseCodes[numOfCourses - 1] = courseCode;
    tempCourseGrades[numOfCourses - 1] = grade;
    delete[] courseCodes;
    delete[] courseGrades;
    courseCodes = tempCourseCodes;
    courseGrades = tempCourseGrades;

    }
    void calcGPA()
    {
        // the sum of all course grades divided by the number of courses taken
        float sum = 0.0;
        for (int i = 0; i < numOfCourses; i++) {
            sum += courseGrades[i];
        }
        // 100 = 4
        // bla = x
        GPA = (sum /numOfCourses)*0.04;
    }
};

Student getStudentAt(Student students[], int index) {
    return students[index];
}
float calcClassGPA(Student students[], int numStudents) {
    float sumOfGpas=0;
    for ( int i =0 ; i<numStudents ; i++){
        sumOfGpas += students[i].getGPA();
    }
    return (sumOfGpas/numStudents);
}
float getMaxGPA(Student students[], int numStudents) {
    float maxGPA=0.0;
    for (int i =0 ; i<numStudents; i++){
        if(students[i].getGPA() > maxGPA){
            maxGPA = students[i].getGPA();
        }
    }
    return maxGPA;
}
int getMinGPA(Student students[], int numStudents) {
    float minGPA=4.0;
    for (int i =0 ; i<numStudents; i++){
        if(students[i].getGPA() <minGPA){
            minGPA = students[i].getGPA();
        }
    }
    return minGPA;
}
void printStudentRecord(Student student) {
    cout << "Student's ID: " << student.getStudentID() << endl;
    cout << "Student's Name: " << student.getName() << endl;
    
    for (int i = 0; i < student.getNumOfCourses(); ++i) {
        cout << "Course Code: "<<i<<" "<< student.getCourseCode(i) <<endl;
        cout << "Grades: "<< student.getCourseGrade(i)<<endl;
    }
    cout << "Student's GPA is : " << student.getGPA() << endl;
}

void printAllStudentRecords(Student students[], int numStudents) {
    for (int j = 0 ; j < numStudents ; j++){
        cout << "Student's ID: " << students[j].getStudentID() << endl;
        cout << "Student's Name: " << students[j].getName() << endl;
        
        for (int i = 0; i < students[j].getNumOfCourses(); ++i) {
            cout << "Course Code: "<<i<<" "<< students[j].getCourseCode(i) <<endl;
            cout << "Grade: "<< students[j].getCourseGrade(i)<<endl;
        }
        cout << "Student's GPA is : " << students[j].getGPA() << endl;
    }
}

int main()
{
    int numStudents = 0;
    cout << "Enter number of Students:\n";
    cin >> numStudents;
    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++) {
        int studentID;
        string studentName;
        cout << "Enter Student ID for student " << i + 1 << ": ";
        cin >> studentID;
        cin.ignore(); 
        cout << "Enter Student Name for student " << i + 1 << ": ";
        getline(cin, studentName);
        int numCourses;
        cout << "Enter number of courses for student " << i + 1 << ": ";
        cin >> numCourses;
        string *courseNames= new string [numCourses];
        int *marks= new int [numCourses];
        for (int j = 0; j < numCourses; j++) {
            cout << "Enter Course Code for course " << j + 1 << ": ";
            cin >> courseNames[j];
            cin.ignore(); 
            cout << "Enter Grade for course " << j + 1 << ": ";
            cin >> marks[j];
            cin.ignore();
        }
        students[i] = Student(studentID, studentName, numCourses,courseNames,marks);

        students[i].calcGPA();
    }

    printAllStudentRecords(students, numStudents);

    cout << "Class GPA: " << calcClassGPA(students, numStudents) << endl;
    cout << "Maximum GPA: " << getMaxGPA(students, numStudents) << endl;
    cout << "Minimum GPA: " << getMinGPA(students, numStudents) << endl;
    delete[] students;
    return 0;
}
