#include <iostream>
using namespace std;
class Matrix
{
private:
    int rows, cols;
    int **matrix;

public:
    Matrix()
    {
        rows = 0, cols = 0;
        matrix = new int *;
    };
    Matrix(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        matrix = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new int[cols];
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    Matrix(const Matrix &copy)
    {
        this->rows = copy.rows;
        this->cols = copy.cols;
        matrix = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new int[cols];
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = copy.matrix[i][j];
            }
        }
    }
    void inputMatrix(){
        int count =0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                count++;
                cout<<"\nEnter element "<<count<<":\t";
                cin>>matrix[i][j];
            }
        }
    }

    void displayMatrix()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    Matrix operator*(Matrix &other)
    {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < other.cols; j++)
            {
                int sum = 0;
                for (int k = 0; k < cols; k++)
                {
                    sum += matrix[i][k] * other.matrix[k][j];
                }
                result.matrix[i][j] = sum;
            }
        }//rows other Matrix cols + ikkj
            return result;
        
    }
        ~Matrix()
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    };
    int main(){
        Matrix m1(2, 2);
        m1.inputMatrix();
        cout<<"Matrix 1:\n";
        m1.displayMatrix();
        Matrix m2(m1);
        cout<<"\nMatrix 2:\n";
        m2.displayMatrix();
        Matrix m3 = m1 * m2;
        cout<<"Matrix 3 = Matrix 1 x matric 2:\n";
        m3.displayMatrix();

        return 0;
    }