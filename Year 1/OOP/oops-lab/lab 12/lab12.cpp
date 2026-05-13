#include <iostream>
using namespace std;

class Vector
{
private:
int i;
int j;
int k;
public:
Vector(int a = 0, int b = 0, int c = 0){
    i = a;
    j = b;
    k = c;
}
Vector(const Vector& copy){
    this->i = copy.i;
    this->j = copy.j;
    this->k = copy.k;
}

Vector operator+(Vector& val){
    Vector newVector;
    newVector.i = this->i + val.i;
    newVector.j = this->j + val.j;
    newVector.k = this->k + val.k;
    return newVector;
}
Vector operator/(Vector& val){
    Vector newVector;
    newVector.i = this->i / val.i;
    newVector.j = this->j / val.j;
    newVector.k = this->k / val.k;
    return newVector;
}
Vector operator*(Vector& val){
    Vector newVector;
    newVector.i = this->i * val.i;
    newVector.j = this->j * val.j;
    newVector.k = this->k * val.k;
    return newVector;
}

Vector& operator+=(Vector& rhs){
    this->i = this->i + rhs.i;
    this->j = this->j+ rhs.j;
    this->k = this->k + rhs.k;
    return *this;
}
Vector& operator-=(Vector& rhs){
    this->i = this->i - rhs.i;
    this->j = this->j- rhs.j;
    this->k = this->k - rhs.k;
    return *this;
}
bool operator==(Vector& val){
    return val.i==this->i && val.j==this->j && val.k ==this->k;
}
bool operator!=(Vector& val){
    return val.i != i || val.j != j || val.k != k;
}
~Vector(){};
friend ostream& operator<<(ostream& output, const Vector& val); 
friend istream& operator>>(istream& input,  Vector& val); 

};
ostream& operator<<(ostream& output, const Vector& val){
    cout<<"i: ";
    output<< val.i;
    cout<<"\nj: ";
    output<< val.j;
    cout<<"\nk:";
    output<< val.k;
    return output;
} 
istream& operator>>(istream& input,  Vector& val){
    cout<<"Enter i:\t ";
    input >> val.i;
    cout<<"Enter j:\t ";
    input >> val.j;
    cout<<"Enter k:\t";
    input >> val.k;
    return input;
} 
int main(){
    Vector vector1(2,3,1); 
    //could put values in the constructor or do cin
    Vector vector2(0,0,0);
    cin>>vector2;
    cout<<"vector 1 is:\n";
    cout<<vector1;
    cout<<"\nvector 2 is:\n";
    cout<<vector2;
    if(vector1==vector2){
        cout<<"\nvector 1 and vector 2 are equal\n";
    }
    if(vector1!=vector2){
        cout<<"\nvector 1 and vector 2 are NOT equal\n";
    }
    cout<<"\nboth vectors added together are\n";
    cout<<(vector1+vector2);
    cout<<"\nboth vectors multiplied together are\n";
    cout<<(vector1*vector2);
    cout<<"\nvector 1 divided from vector 2 is\n";
    cout<<(vector1/vector2);
    cout<<"\nvector 2 added to vector 1 is\n";
    vector1+=vector2;
    cout<<vector1;
    cout<<"\nvector 2 subtracted from vector 1 is\n";
    vector1-=vector2;
    cout<<vector1;
    return 0;
}