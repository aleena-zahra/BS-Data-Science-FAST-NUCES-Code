#include <iostream>
using namespace std;

class Vector {
private:
    int i;
    int j;
    int k;

public:
    Vector(int a = 0, int b = 0, int c = 0) {
        i = a;
        j = b;
        k = c;
    }

    Vector(const Vector& copy) {
        this->i = copy.i;
        this->j = copy.j;
        this->k = copy.k;
    }

    Vector operator+(Vector& val) {
        Vector newVector;
        newVector.i = this->i + val.i;
        newVector.j = this->j + val.j;
        newVector.k = this->k + val.k;
        return newVector;
    }


    Vector operator/(Vector& val) {
        Vector newVector;
        newVector.i = this->i / val.i;
        newVector.j = this->j / val.j;
        newVector.k = this->k / val.k;
        return newVector;
    }
    Vector operator*(Vector& val) {
        Vector newVector;
        newVector.i = this->i * val.i;
        newVector.j = this->j * val.j;
        newVector.k = this->k * val.k;
        return newVector;
    }

    Vector& operator+=(Vector& rhs) {
        this->i = this->i + rhs.i;
        this->j = this->j + rhs.j;
        this->k = this->k + rhs.k;
        return *this;
    }

    Vector& operator-=(Vector& rhs) {
        this->i = this->i - rhs.i;
        this->j = this->j - rhs.j;
        this->k = this->k - rhs.k;
        return *this;
    }

    bool operator==(Vector& val) {
        return val.i == this->i && val.j == this->j && val.k == this->k;
    }

    bool operator!=(Vector& val) {
        return val.i != i || val.j != j || val.k != k;
    }

    // Destructor removed

    friend ostream& operator<<(ostream& output, const Vector& val);
    friend istream& operator>>(istream& input,  Vector& val);
};

ostream& operator<<(ostream& output, const Vector& val) {
    cout << "i: " << val.i << "\nj: " << val.j << "\nk: " << val.k;
    return output;
}


istream& operator>>(istream& input, Vector& val) {
    cout << "Enter i: ";
    input >> val.i;
    cout << "Enter j: ";
    input >> val.j;
    cout << "Enter k: ";
    input >> val.k;
    return input;
}

int main() {
    Vector vector1(2, 20, 20); 
    Vector vector2(1, 1, 1);

    cin >> vector2;

    cout << "Vector 1 is:\n" << vector1 << endl;
    cout << "Vector 2 is:\n" << vector2 << endl;

    if (vector1 == vector2) {
        cout << "Vector 1 and vector 2 are equal\n";
    }
    if (vector1 != vector2) {
        cout << "Vector 1 and vector 2 are NOT equal\n";
    }

    cout << "Both vectors added together are\n" << (vector1 + vector2) << endl;
    cout << "Both vectors multiplied together are\n" << (vector1 * vector2) << endl;
    cout << "Vector 1 divided by vector 2 is\n" << (vector1 / vector2) << endl;

    cout << "Vector 2 added to vector 1 is\n";
    vector1 += vector2;
    cout << vector1 << endl;

    cout << "Vector 2 subtracted from vector 1 is\n";
    vector1 -= vector2;
    cout << vector1 << endl;

    return 0;
}
