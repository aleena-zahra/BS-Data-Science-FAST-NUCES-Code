#include<iostream>
using namespace std;
class MathOperations{
    private:
    int num1=0,num2=0,num3=0;
    public:
    int add(int num1, int num2) {
        return num1 + num2;
    }
    double add(double num1, double num2, double num3) {
        return num1+num2+num3;
    }
};
int main(){
    MathOperations math;
    int result = math.add(5, 3);
    cout << "Result of adding two integers: " << result << endl;
    double result2 = math.add(2.5, 3.7, 1.2);
    cout << "Result of adding three doubles: " << result2 << endl;

    return 0;
}
