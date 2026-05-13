#include <iostream>
using namespace std;

class Shape{
    protected:
    double area;
    public:
    Shape(){}
    virtual void findArea()=0;
    virtual ~Shape(){}
};
class Rectangle: public Shape{
    long int width;
    long int length;
    public:
    Rectangle(long int w , long int l){
        width = w;
        length = l;
        findArea();
    }
    void findArea(){
        area = length*width;
        cout<<"\nThe area of the Rectangle is "<<area;
    }
   
    ~Rectangle(){}
};
class Circle: public Shape{
    long int centreXCor;
    long int centreYCor;
    double radius;
    public:
    Circle(long int x , long int y,double r){
        centreXCor = x;
        centreYCor = y;
        radius = r;
        findArea();
    }
    void findArea(){
        area = 3.14159*radius*radius;
        cout<<"\nThe area of the Circle is "<<area;
    }

    ~Circle(){}
};
int main(){
    int size = 5;
    int x = 0,y=0;
    Shape *shapesPointerArray[size];
    for(int i = 0 ; i<size ; i++,x++,y++){
        if (i>2) shapesPointerArray[i] = new Rectangle(x,y);
        else shapesPointerArray[i] = new Circle(x,y,i+1);
    }
    return 0;
}