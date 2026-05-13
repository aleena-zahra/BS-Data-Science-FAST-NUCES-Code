#include <iostream>
using namespace std;

class communityMember{
    public:
    communityMember(){
        cout<<"communityMember Constructor Called\n";
    }
    ~communityMember(){
        cout<<"communityMember Destructor Called\n";
    }

};
class employee: public communityMember{
    public:
    employee(){
        cout<<"employee Constructor Called\n";
    }
    ~employee(){
        cout<<"employee Destructor Called\n";
    }

};
class student: public communityMember{
    public:
    student(){
        cout<<"student Constructor Called\n";
    }
    ~student(){
        cout<<"student Destructor Called\n";
    }

};
class alumni: public communityMember{
    public:
    alumni(){
        cout<<"alumni Constructor Called\n";
    }
    ~alumni(){
        cout<<"alumni Destructor Called\n";
    }

};
class staff: public employee{
    public:
    staff(){
        cout<<"staff Constructor Called\n";
    }
    ~staff(){
        cout<<"staff Destructor Called\n";
    }

};
class faculty: public employee{
    public:
    faculty(){
        cout<<"faculty Constructor Called\n";
    }
    void display(){
    cout<<"Class is faculty\n";
    }
    ~faculty(){
        cout<<"faculty Destructor Called\n";
    }

};
class administrator: public faculty{
    public:
    administrator(){
        cout<<"administrator Constructor Called\n";
    }
    void display(){
    cout<<"Class is administrator \n";
    }
    ~administrator(){
        cout<<"administrator Destructor Called\n";
    }

};
class teacher: public faculty{
    public:
    teacher(){
        cout<<"teacher Constructor Called\n";
    }
    void display(){
    cout<<"Class is teacher \n";
    }
    ~teacher(){
        cout<<"teacher Destructor Called\n";
    }

};
class administrativeTeacher: public teacher, public administrator{
    public:
    administrativeTeacher(){
        cout<<"administrativeTeacher Constructor Called\n";
    }
    // void display(){
    // cout<<"Class is administrativeTeacher\n";
    // }
    ~administrativeTeacher(){
        cout<<"administrativeTeacher Destructor Called\n";
    }

};
void display(){
    cout<<"Class is \n";
}

int main(){
    administrativeTeacher firstObject;
    firstObject.teacher::display();
}