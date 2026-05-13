#include<iostream>
using namespace std;
struct fraction{
    int numerator;
    int denominator;
};
    void inputFrac(fraction &a){
        cout<<"Enter numerator\n";
        cin>>a.numerator;
        cout<<"Enter denominator\n";
        cin>>a.denominator;
    }
    void displayFrac(fraction &a){
        cout<<a.numerator<<"";
        cout<<"/";
        cout<<a.denominator<<"\n";
    }
    fraction addition(fraction a, fraction b){
        fraction ans;
        ans.numerator =  a.numerator * b.denominator + a.denominator*b.numerator;
        ans.denominator = a.denominator*b.denominator;
        return ans;

    }
    fraction subtraction(fraction a, fraction b){
        fraction ans;
        ans.numerator =  a.numerator * b.denominator - a.denominator*b.numerator;
        ans.denominator = a.denominator*b.denominator;
        return ans;
    }
    fraction multiplication(fraction a, fraction b){
        fraction ans;
        ans.numerator =  a.numerator*b.numerator;
        ans.denominator = a.denominator*b.denominator;
        return ans;
    }
    fraction division(fraction a, fraction b){
        fraction ans;
        ans.numerator =  a.numerator * b.denominator;
        ans.denominator = a.denominator*b.numerator;
        return ans;
    }
int main(){
    fraction a,b,c;
    inputFrac(a);
    inputFrac(b);
    displayFrac(a);
    displayFrac(b);
    c=addition(a,b);
    displayFrac(c);
    c=subtraction(a,b);
    displayFrac(c);
    c=multiplication(a,b);
    displayFrac(c);
    c=division(a,b);
    displayFrac(c);

    return 0;
}