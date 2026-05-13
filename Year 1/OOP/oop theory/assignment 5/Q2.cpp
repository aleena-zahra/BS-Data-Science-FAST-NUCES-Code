#include <iostream>
#include <string>
#include<cmath>
using namespace std;

class Binary {
private:
    string binaryString;
    int base;

public:
	
    // Constructor (If base is greater than 2 first convert into base 10 using that base and then convert back into binary and change the base to 2)
    Binary(string binaryStr, int base = 2){
        if(base>2){
            string result;
            int totalNum=0;
            int numOfDigits=getStrLength(binaryStr);
            for(int i =0 ; i<numOfDigits ; i++){
                int digit;
                if (binaryStr[i] >= '0' && binaryStr[i] <= '9')
                    digit = binaryStr[i] - '0';
                else if (binaryStr[i] >= 'a' && binaryStr[i] <= 'z')
                    digit = binaryStr[i] - 'a' + 10;
                else if (binaryStr[i] >= 'A' && binaryStr[i] <= 'Z')
                    digit = binaryStr[i] - 'A' + 10;
                totalNum+=digit;
            }
            while (totalNum > 0) {
                
                result = to_string(totalNum % 2) + result;
                totalNum /= 2;
            }
            this->binaryString = result;
            this->base=2;
            cout<<"binary string is "<<this->binaryString<<endl;
            
        }
        else{
        binaryString = binaryStr;
        this->base=2;
        }
    }
    int convertBinaryToDecimal(string binaryNumber)const{
        int totalLength = binaryNumber.length();
        int decimalNumber=0;
        for(int i =0 ; i<totalLength ; i++){
            if(binaryNumber[i]=='1'){
                decimalNumber+= pow(2, totalLength - 1 - i);
            }
        }
        return decimalNumber;
    }
    string convertDecimalToBinary(int decimalNumber)const{
        string binaryNumber = "";
        if (decimalNumber == 0) {
            binaryNumber = "0";
        } 
        else {
            while (decimalNumber > 0) {
                binaryNumber = to_string(decimalNumber % 2) + binaryNumber;
                decimalNumber /= 2;
            }
        }
        return binaryNumber;
    }
    // Overloading + operator for addition
    Binary operator+(const Binary& other) const{
        //first store both in two strings and then convert both numbers to int
        //then add it then convert that number to binary
        string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3 = decimalNumber1 + decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}

    //Overloading - operator for subtraction
   Binary operator-(const Binary& other) const{
	string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3 = decimalNumber1 - decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}
    
    // Overloading += operator for addition
    Binary& operator+=(const Binary& other) {
	    int decimalNumber1 = convertBinaryToDecimal(binaryString);
        int decimalNumber2 = convertBinaryToDecimal(other.binaryString);
        decimalNumber1 = decimalNumber1 - decimalNumber2;
        string binaryNumber = convertDecimalToBinary(decimalNumber1);
        this->binaryString = binaryNumber;
        return *this;
	}

    // Overloading -= operator for subtraction
    Binary& operator-=(const Binary& other) {
        int decimalNumber1 = convertBinaryToDecimal(binaryString);
        int decimalNumber2 = convertBinaryToDecimal(other.binaryString);
        decimalNumber1 = decimalNumber1 - decimalNumber2;
        string binaryNumber = convertDecimalToBinary(decimalNumber1);
        this->binaryString = binaryNumber;
        return *this;
	}

    //Overloading * operator for multiplication (Convert to base 10 multiply and convert back into base 2)
   Binary operator*(const Binary& other) const{
	string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3 = decimalNumber1 * decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}

    //Overloading / operator for division  (Convert to base 10 divide and convert back into base 2)
   Binary operator/(const Binary& other) const{
	    string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3=0;
        if(decimalNumber1==decimalNumber2) decimalNumber3 =1;
        else decimalNumber3 = decimalNumber1 / decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}

    //Overloading % operator for modulus  (Convert to base 10 modulus and convert back into base 2)
    Binary operator%(const Binary& other) const{
	    string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3 = decimalNumber1 % decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}
    
    //Overloading | operator for or
    Binary operator|(const Binary& other) const{
        string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3 = decimalNumber1 | decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}
    
    // Overloading ^ operator for xor
    Binary operator^(const Binary& other) const{
        string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3 = decimalNumber1 ^ decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}

    // Overloading & operator for and
    Binary operator&(const Binary& other) const{
        string binaryNumber1 = binaryString;
        string binaryNumber2 = other.binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        int decimalNumber2 = convertBinaryToDecimal(binaryNumber2);
        int decimalNumber3 = decimalNumber1 & decimalNumber2;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber3);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}

    //Overloading ! operator for 2's Compliment
    Binary operator!() const{
        string binaryNumber1 = this->binaryString;
        Binary oneComplimenetBinary(binaryNumber1);
        Binary resultantBinary = ~oneComplimenetBinary + Binary("1"); //  1 compilent and add a 1 to it
        return resultantBinary;
	}
    
    // Overloading ~ operator for 1's Compliment
    Binary operator ~() const{
        string binaryNumber1 = this->binaryString;
        for (char &c : binaryNumber1) {
            if (c == '0') {
                c = '1';
            } else {
                c = '0';
            }
        }
        Binary resultantBinary(binaryNumber1);
        return resultantBinary;
	}
    
    // Overloading left shift operator
    Binary operator<<(int shiftAmount) const{
        string binaryNumber1 = this->binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        decimalNumber1 = decimalNumber1 << shiftAmount;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber1);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}

    // Overloading right shift operator
    Binary operator>>(int shiftAmount) const{
        string binaryNumber1 = this->binaryString;
        int decimalNumber1 = convertBinaryToDecimal(binaryNumber1);
        decimalNumber1 = decimalNumber1 >> shiftAmount;
        string binaryNumber3 = convertDecimalToBinary(decimalNumber1);
        Binary resultantBinary(binaryNumber3);
        return resultantBinary;
	}

    // Overloading input operator
    friend istream& operator>>(istream& input, Binary& other);
    // Overloading output operator (Display Both Binary as well as Integer value)
    friend ostream& operator<<(ostream& output, const Binary& other);
    int getStrLength(string &str){
    int len=0;
    for(int i =0; str[i]!='\0';i++){
        len++;
    }
    return len;
}
};
    // Overloading input operator
istream& operator>>(istream& input, Binary& other){
	cout<<"Enter number:\t ";
    input >> other.binaryString;
    cout<<"\nEnter base:\t ";
    input >> other.base;
    cout<<endl;
    return input;
}

// Overloading output operator (Display Both Binary as well as Integer value)
ostream& operator<<(ostream& output, const Binary& other){
    cout<<"Binary number is:\t ";
    output << other.binaryString;
    string binaryNumber = other.binaryString;
    int decimalNumber = other.convertBinaryToDecimal(binaryNumber);
    cout<<"\nDecimal Number is:\t ";
    cout << decimalNumber<<endl;
    return output;
}

int main(){
    string number,number2;
    cout<<"\nEnter a number:\t";
    cin>>number;
    Binary num1(number);
    cout<<"\nEnter another number:\t";
    cin>>number2;
    Binary num2(number2);
    cout << "\nThe Addition of both numbers is: "; 
    cout << (num1 + num2);
    cout << "\nThe Subtraction of both numbers is: "; 
    cout << (num1 - num2);
    cout << "\nThe Multiplication of both numbers is: "; 
    cout << (num1 * num2);
    cout << "\nThe Division of both numbers is: "; 
    cout << (num1 / num2);
    cout << "\nThe Modulus of both numbers is: "; 
    cout << (num1 % num2);
    cout << "\nThe OR of both numbers is: " ;
    cout << (num1 | num2);
    cout << "\nThe XOR of both numbers is: " ;
    cout << (num1 ^ num2);
    cout << "\nThe AND of both numbers is: " ;
    cout << (num1 & num2);
    cout << "\nThe 1's Complement of number 1 is: " << ~num1;
    cout << "\nThe 2's Complement of number 1 is: " << !num1;
    cout << "\nThe Left Shift of number 1 is: " ;
    cout << (num1 << 1);
    cout << "\nThe Right Shift of number 1 is: " ;
    cout << (num1 >> 1);
    return 0;
}
