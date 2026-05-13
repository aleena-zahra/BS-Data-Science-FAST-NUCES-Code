#include <iostream>
#include <string>

using namespace std;

class BigFloat
{
int precision;
string integerPart;
string fracPart;
bool isPositive; 
public:
BigFloat(double val = 0.0, int precision = 2){
    this-> precision = precision;
    this-> isPositive = (val >= 0);
    val = abs(val);
    string str = to_string(val);
    size_t dotPosition = str.find('.');
    this-> integerPart = str.substr(0, dotPosition);
    this-> fracPart = str.substr(dotPosition + 1);
}
BigFloat(const string& text, int precision = 2){
    this-> precision = precision;
    this-> isPositive = (text[0] != '-');
    size_t dotPosition = text.find('.');
    if(isPositive) this-> integerPart = text.substr(0, dotPosition);
    else this-> integerPart = text.substr(1, dotPosition);
    this-> fracPart = text.substr(dotPosition + 1);
}
BigFloat(const BigFloat& copy){ // copy constructor //
    precision = copy.precision;
    integerPart = copy.integerPart;
    fracPart =  copy.fracPart;
    isPositive = copy.isPositive;
}
long double bigFloatToLongDouble() const {
    long double result = stold( this-> integerPart + "." +  this-> fracPart);
    return  this-> isPositive ? result : -result;
}
BigFloat operator=(const BigFloat& val){ 
    precision = val.precision;
    integerPart = val.integerPart;
    fracPart =  val.fracPart;
    isPositive = val.isPositive;
    return *this;
}
BigFloat operator+(const BigFloat& val) const{
    long double num1 = bigFloatToLongDouble();
    long double num2 = val.bigFloatToLongDouble();
    long double result  = num1 + num2;
    int newPrecision;
    if(precision > val.precision) newPrecision= precision;
    else newPrecision = val.precision;
    BigFloat resultBigFloat(result,newPrecision);
    return resultBigFloat;
}
BigFloat operator-(const BigFloat& val) const{
    long double num1 = bigFloatToLongDouble();
    long double num2 = val.bigFloatToLongDouble();
    long double result  = num1 - num2;
    int newPrecision;
    if(precision > val.precision) newPrecision= precision;
    else newPrecision = val.precision;
    BigFloat resultBigFloat(result,newPrecision);
    return resultBigFloat;
}
BigFloat operator*(const BigFloat& val) const{
    long double num1 = bigFloatToLongDouble();
    long double num2 = val.bigFloatToLongDouble();
    long double result  = num1 * num2;
    int newPrecision;
    if(precision > val.precision) newPrecision= precision;
    else newPrecision = val.precision;
    BigFloat resultBigFloat(result,newPrecision);
    return resultBigFloat;
}
BigFloat operator/(const BigFloat& val) const{
    long double num1 = bigFloatToLongDouble();
    long double num2 = val.bigFloatToLongDouble();
    long double result  = num1 / num2;
    int newPrecision;
    if(precision > val.precision) newPrecision= precision;
    else newPrecision = val.precision;
    BigFloat resultBigFloat(result,newPrecision);
    return resultBigFloat;
}
BigFloat operator%(const BigFloat& val) const{
    long double num1 = bigFloatToLongDouble();
    long double num2 = val.bigFloatToLongDouble();
    long double result  = num1 + num2;
    int newPrecision;
    if(precision > val.precision) newPrecision= precision;
    else newPrecision = val.precision;
    BigFloat resultBigFloat(result,newPrecision);
    return resultBigFloat;
}
// Compound Assignment Operators
BigFloat operator+=(const BigFloat& rhs){
    *this = *this + rhs;
    return *this;
}
BigFloat operator-=(const BigFloat& rhs){
    *this = *this - rhs;
    return *this;
}
BigFloat operator*=(const BigFloat& rhs){
    *this = *this * rhs;
    return *this;
}
BigFloat operator/=(const BigFloat& rhs){
    *this = *this / rhs;
    return *this;
}
BigFloat operator%=(const BigFloat& rhs) {
    *this = *this % rhs;
    return *this;
}
// Logical Operators
bool operator==(const BigFloat& val) const{
    return (isPositive == val.isPositive && integerPart == val.integerPart && fracPart == val.fracPart);
}
bool operator!=(const BigFloat& val) const{
    return !(*this==val);
}
bool operator<(const BigFloat& val) const{
    if(this->isPositive!=val.isPositive) return !this->isPositive;
    long double num1 = bigFloatToLongDouble();
    long double num2 = val.bigFloatToLongDouble();
    return num1 < num2;
}
bool operator<=(const BigFloat& val) const{
    return ((*this==val)||(*this<val));
}
bool operator>(const BigFloat& val) const{
    if(this->isPositive!=val.isPositive) return this->isPositive;
    long double num1 = bigFloatToLongDouble();
    long double num2 = val.bigFloatToLongDouble();
    return num1 > num2;
    
}
bool operator>=(const BigFloat& val) const{
    return ((*this==val)||(*this>val));
}
// Unary Operators
BigFloat operator+() const{// Unary Plus Operator
    long int num1 = addDigits(); 
    BigFloat result(num1,precision);
    num1 = num1* precision;
    if(num1*precision>100){
        if (isPositive) result.isPositive = false;
    }
    return result;

}
BigFloat operator-() const{ 
    long int num1 = addDigits(); 
    BigFloat result(num1,precision);
    num1 = num1* precision;
    if(num1*precision>100){
        if (!isPositive) result.isPositive = true;
    }
    return result;
}

long int addDigits() const {
    long int num1 = stold( this-> integerPart);
    long int  num2 = stold( this-> fracPart);
    return num1+num2;
}

// Conversion Operator
operator string() const{ // return value of the BigFloat as string
    string s = "";
    if(!isPositive){
        s = "-" + integerPart + "." + fracPart;
    }
    else{
        s = integerPart + "." + fracPart;
    }
    return s;
}

~BigFloat(){} // destructor
friend ostream& operator<<(ostream& output, const BigFloat& val);
// outputs the BigFloat
friend istream& operator>>(istream& input, BigFloat& val); // inputs the BigFloat

};
ostream& operator<<(ostream& output, const BigFloat& val){
    if (!val.isPositive) cout<<"-";
    output<<val.integerPart<<" . ";
    output<<val.fracPart;
    //precision??
    return output;
}
istream& operator>>(istream& input, BigFloat& val){
    cout<<"\nEnter precision:\t";
    input>>val.precision;
    cout<<"\nEnter integer part:\t";
    input>>val.integerPart;
    cout<<"\nEnter fractional part:\t";
    input>>val.fracPart;
    cout<<"\nEnter 1 if number is positive, 0 if negative:\t";
    input>>val.isPositive; 
    return input;
}
int main(){
    BigFloat num1("110.12");
    cout<<num1<<endl;
    BigFloat num2(80.24);
    cout<<num2<<endl;
    cout << "\nThe Addition of num 1 and num 2 is: "; 
    cout << (num1 + num2);
    cout << "\nThe Subtraction of num 1 and num 2 is: "; 
    cout << (num1 - num2);
    cout << "\nThe Multiplication of num 1 and num 2 is: "; 
    cout << (num1 * num2);
    cout << "\nThe Division of num 1 and num 2 is: "; 
    cout << (num1 / num2);
    cout << "\nThe MOD of num 1 and num 2 is: "; 
    cout << (num1 % num2);
    ///////////////////////////////
    num1 += num2;
    cout << "\nCompound Addition of num 1 with num 2 is: " << num1;
    num1 -= num2;
    cout << "\nCompound Subtraction of num 1 with num 2 is: " << num1;
    num1 *= num2;
    cout << "\nCompound Multiplication of num 1 with num 2 is: " << num1;
    num1 /= num2;
    cout << "\nCompound Division of num 1 with num 2 is: " << num1;
    // num1 %= num2;
    // cout << "\nCompound MOD of num 1 with num 2 is: " << num1;
    cout << "\nUnary Plus on num 1: " << +num1;
    cout << "\nUnar Minus on num 2: " << -num2;
    if(num1 == num2)  cout << "\nnum 1 == num 2 ";
    if(num1 != num2)  cout << "\nnum 1 != num 2 ";
    if(num1 >= num2)  cout << "\nnum 1 >= num 2 ";
    if(num1 >  num2)  cout << "\nnum 1 > num 2 ";
    if(num1 <= num2)  cout << "\nnum 1 <= num 2 ";
    if(num1 <  num2)  cout << "\nnum 1 < num 2 ";
    return 0;

}