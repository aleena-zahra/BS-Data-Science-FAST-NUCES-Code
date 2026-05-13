#include<iostream>
using namespace std;
struct employee{
    string code;
    string name;
    float salary;
};

void inputEmployee(employee *emp){
        cout<< "Roll no of employee :\n";
        cin>> (*emp).code;
        cout<< "Name of employee :\n";
        cin>> (*emp).name;
        cout<< "salary of employee :\n";
        cin>> (*emp).salary;
    
}
void displayEmployee( employee *emp){
        cout<< "Roll no of employee  : "<<(*emp).code<<endl;
        cout<< "Name of employee  : "<<(*emp).name<<endl;
        cout<< "salary of employee  : "<<(*emp).salary<<endl;
    
}
void swapEmployee(employee *emp1,employee *emp2){
    string temp;
    (*emp1).code = temp;
    temp= (*emp2).code;
    (*emp2).code= (*emp1).code;
    (*emp1).name = temp;
    temp= (*emp2).name;
    (*emp2).name= (*emp1).name;
    float temp2;
    (*emp1).salary = temp2;
    temp2= (*emp2).salary;
    (*emp2).salary = (*emp1).salary;
}
int main(){
    employee emp1,emp2; 
    inputEmployee(&emp1);
    displayEmployee(&emp1);
    // inputEmployee(emp2);
    // displayEmployee(emp2);
    // swapEmployee(emp1,emp2);
    // displayEmployee(emp1);
    // displayEmployee(emp2);

}