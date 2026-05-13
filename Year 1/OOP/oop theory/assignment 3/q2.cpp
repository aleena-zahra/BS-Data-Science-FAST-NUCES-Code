//	Aleena Zahra 23i-2514 BDS-B	OOP Assignment 3
#include <iostream>
using namespace std;

class Student
{
    int stdID;
    string name;
    string *courseCodes;
    int numCourses;
    int *courseGrades;
    float gpa;

public:
    Student(int id, string name, int numCourses = 5) : stdID(id), name(name), numCourses(numCourses), courseCodes(new string[numCourses]), courseGrades(new int[numCourses])
    {
        string code;
        int grade;
        cout << "For student " << stdID << ":\n";
        for (int i = 0; i < numCourses; i++)
        {
            cout << "Enter course code " << (i + 1) << ": ";
            cin >> code;
            cout << "Enter grade for " << code << ": ";
            cin >> grade;
            addCourse(code, grade);
        }
        calcGPA();
        cout << endl;
    }
    int getID()
    {
        return stdID;
    }
    string getName()
    {
        return name;
    }
    string getCode(int i)
    {
        return courseCodes[i];
    }
    int getNumOfCourses()
    {
        return numCourses;
    }
    int getGrade(int i)
    {
        return courseGrades[i];
    }
    float getGPA()
    {
        return gpa;
    }
    void calcGPA()
    {
        for (int i = 0; i < numCourses; i++)
        {
            gpa += courseGrades[i];
        }
        gpa /= static_cast<float>(numCourses);
    }
    void addCourse(string courseCode, int grade)
    {
        for (int i = 0; i < numCourses; i++)
        {
            if (courseCodes[i] == "\0")
            {
                courseCodes[i] = courseCode;
                courseGrades[i] = grade;
                cout << courseCode << " added with grade " << grade << endl;
                break;
            }
            else if (i == numCourses - 1)
                cout << "Max course limit reached!\n";
        }
    }
    void setCourseGrade(string courseCode, int grade)
    {
        for (int i = 0; i < numCourses; i++)
        {
            if (courseCodes[i] == courseCode)
            {
                courseGrades[i] = grade;
                cout << courseCode << " grade updated to " << grade << endl;
                break;
            }
            else if (i == numCourses - 1)
                cout << courseCode << " not found!\n";
        }
    }
    void setID(int id) { stdID = id; }
    void setName(string name) { this->name = name; }
};

Student getStudentAt(Student students[], int index) { return students[index]; }

float calcClassGPA(Student students[], int numStudents)
{
    float total = 0;
    for (int i = 0; i < numStudents; i++)
    {
        total += getStudentAt(students, i).getGPA();
    }
    return total / numStudents;
}

float getMaxGPA(Student students[], int numStudents)
{
    float max = getStudentAt(students, 0).getGPA();
    for (int i = 1; i < numStudents; i++)
    {
        if (getStudentAt(students, i).getGPA() > max)
            max = getStudentAt(students, i).getGPA();
    }
    return max;
}

float getMinGPA(Student students[], int numStudents)
{
    float min = getStudentAt(students, 0).getGPA();
    for (int i = 1; i < numStudents; i++)
    {
        if (getStudentAt(students, i).getGPA() < min)
            min = getStudentAt(students, i).getGPA();
    }
    return min;
}

void printStudentRecord(Student student)
{
    cout << "\n------------------------------------------------\n\n";
    cout << "Student ID: " << student.getID() << endl;
    cout << "Name: " << student.getName() << endl;
    cout << "GPA: " << student.getGPA() << endl
         << endl;

    for (int i = 0; i < student.getNumOfCourses(); i++)
    {
        cout << student.getCode(i) << " - " << student.getGrade(i) << endl;
    }
}

void printAllStudentRecords(Student students[], int numStudents)
{
    for (int i = 0; i < numStudents; i++)
    {
        printStudentRecord(getStudentAt(students, i));
    }
}

int main()
{

    Student s1(232014, "Fatima"), s2(232514, "Aleena");
    Student arr[2] = {s1, s2};
    printAllStudentRecords(arr, 2);

    return 0;
}