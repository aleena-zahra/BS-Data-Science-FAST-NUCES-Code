#include <iostream>
using namespace std;

class Shape{
    protected:
    string color;
    bool isFilled;
    public:
    Shape(){}
    Shape(string color , bool filled){
        this-> color = color;
        this-> isFilled = filled;
    }
    string getColor(){
        return color;
    }
    void setColor(string color){
        this->color = color;
    }
    bool getIsFilled(){
        return isFilled;
    }
    void setIsFilled(bool isFilled){
        this->isFilled = isFilled;
    }
    string toString(){
        if(isFilled)
        return "\nShape is filled and has the color " + color;
        else return "\nShape is not filled and has the color " + color;
    }
};
class Rectangle: public Shape{
    protected:
    double width;
    double length;
    public:
    Rectangle(){}
    Rectangle(double width , double length){
        this->width = width;
        this->length = length;
    }
    Rectangle(double width , double length ,string color , bool filled){
        this->width = width;
        this->length = length;
        color = color;
        filled = filled;
    }
    double getLength(){
        return length;
    }
    void setLength(double l){
        length = l;
    }
    double getWidth(){
        return width;
    }
    void setWidth(double w){
        width = w;
    }
     double getArea(){
        return length*width;
    }
    double getPerimeter(){
        return 2*length + 2*width;
    }
    string toString(){
        cout<<Shape::toString();
        return "\nRectangle has width " + to_string(width) + " and length " + to_string(length);
    }


};
class Circle: public Shape{
    private:
    double radius;
    public:
    Circle(){
        radius = 1.0;
    }
    Circle(double radius){
        this->radius = radius;
    }
    double getRadius(){
        return radius;
    }
    void setRadius(double r){
        radius = r;
    }
    double getArea(){
        return radius*radius*3.14159;
    }
    double getPerimeter(){
        return 2*radius*3.14159;
    }
    string toString(){
        cout<<Shape::toString();
        return "\nCircle has radius " + to_string(radius);
    }

};
class Square: public Rectangle{
    public:
    Square(){}
    Square(double side){
        width = side;
        length = side;

    }
    Square(double side ,string color , bool filled){
        width = side;
        length = side;
        color = color;
        filled = filled;
    }
    double getSide(){
        return length;
    }
    void setSide(double l){
        length = l;
    }
    void setWidth(double w){
        width = w;
    }
    void setLength(double l){
        length = l;
    }
    string toString(){
        cout<<Shape::toString();
        return "\nSquare has side " + to_string(length);
    }

};
int main(){
    Circle shape(5.0);
    Square shape2(5.0);
    Rectangle shape3(5.0,5.0);
    shape.setColor("yellow");
    shape2.setColor("red");
    shape3.setColor("orange");
    shape.setIsFilled(true);
    shape2.setIsFilled(false);
    shape3.setIsFilled(true);
    cout<<"\nFor SHAPE CIRCLE";
    cout<<"\nArea is "<<shape.getArea();
    cout<<"\nPerimeter is "<<shape.getPerimeter();
    cout<<"\nThe radius is "<<shape.getRadius();
    cout<<shape.toString();

    cout<<"\n\nFor SHAPE RECTANGLE";
    cout<<"\nArea is "<<shape3.getArea();
    cout<<"\nPerimeter is "<<shape3.getPerimeter();
    cout<<"\nThe length is "<<shape3.getLength();
    cout<<"\nThe width is "<<shape3.getWidth();
    cout<<shape3.toString();

    cout<<"\n\nFor SHAPE SQUARE";
    cout<<"\nArea is "<<shape2.getArea();
    cout<<"\nPerimeter is "<<shape2.getPerimeter();
    cout<<"\nThe length is "<<shape2.getSide();
    cout<<shape2.toString();
    return 0;
}