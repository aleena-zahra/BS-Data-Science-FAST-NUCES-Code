#include<iostream>
using namespace std;
class complex{
    int real;
    int img;
    public:
    complex(int r,int i){
        real=r;
        img=i;
    }
    int getReal(){
        return real;
    }
    int getImg(){
        return img;
    }
    void display(){
        cout<<real<<" + "<<img<<" i"<<endl;
    }
    //for ++c
    complex operator --(){
        complex c3(0,0);
        c3.real=real-1;
        c3.img=img-1;
        return c3;
    }
    
    //for c++
    complex operator --(int){
        complex c4(0,0);
        c4.real = real-1;
        c4.img = img-1;
        return c4;
    }
    // void operator --(int){
    //     real = real-1;
    //     img = img-1;
    // }

};
// void operator --(complex c1){
//         c1.getReal()-=1;
//         c1.getImg()-=1;
//     }
int main(){
    complex c (3,3);
    --c;
    --c;
    c.display();
}