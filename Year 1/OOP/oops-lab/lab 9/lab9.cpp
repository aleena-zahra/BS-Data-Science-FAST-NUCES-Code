#include <iostream>
using namespace std;
class Matrix
{
private:
  int **p;
  int row = 0;
  int col = 0;

public:
  Matrix() {}
  Matrix(int n1, int n2, int n3, int n4, int rows = 2, int cols = 2)
  {
    row = rows;
    col = cols;
    p = new int *[row];
    for (int i = 0; i < row; i++)
    {
      p[i] = new int[col];
    }

    p[0][0] = n1;
    p[0][1] = n2;
    p[1][0] = n3;
    p[1][1] = n4;
  }
  Matrix(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int rows = 3, int cols = 3)
  {
    row = rows;
    col = cols;
    p = new int *[row];
    for (int i = 0; i < row; i++)
    {
      p[i] = new int[col];
    }

    p[0][0] = n1;
    p[0][1] = n2;
    p[0][2] = n3;
    p[1][0] = n4;
    p[1][1] = n5;
    p[1][2] = n6;
    p[2][0] = n7;
    p[2][1] = n8;
    p[2][2] = n9;
  }
  Matrix(const Matrix &m)
  {
    row = m.row;
    col = m.col;
    int **a;
    a = new int *[m.row];
    for (int i = 0; i < m.row; i++)
    {
      a[i] = new int[m.col];
    }
    p = a;
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        p[i][j] = m.p[i][j];
      }
    }
  }
  int getRows(){
    return row;
  }
  int getCols(){
    return col;
  }
  void displayMatrix()
  {
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        cout << p[i][j] << " ";
      }
      cout << endl;
    }
    cout<<endl<<endl;
  }
  int getValue(int row, int col)
  {
    return p[row][col];
  }
  int RightDiagonalTotal()
  {
    int sum = 0;
    // for(int i = 0 ; (rowNum - i >= 0) && (colNum + i < col) ; i++){
    //   sum += p[rowNum-i][colNum +i];
    // }
    // for(int i = 0 ; (rowNum + i < row) && (colNum - i >= 0) ; i++){
    //   sum += p[rowNum+i][colNum -i];
    // }
    // sum -= p[rowNum][colNum];
    for (int i = 0; i < row; i++)
    {
      sum += p[i][i];
    }
    return sum;
  }
  int HighestInRow(int rowNum)
  {
    int n = 0, max = 0;
    while (n < col)
    {
      if (p[rowNum][n] > max)
      {
        max = p[rowNum][n];
      }
      n++;
    }
    return max;
  }
  int **MatrixMultiply(Matrix m)
  {
    Matrix multiplyMatx(0, 0, 0, 0, row, m.col);
    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < m.col; ++j)
      {
        int sum = 0;
        for (int k = 0; k < col; ++k)
        {
          sum += p[i][k] * m.p[k][j];
        }
        multiplyMatx.p[i][j] = sum;
      }
    }
    multiplyMatx.displayMatrix();
    return p;
  }

  int findSmallestk(int k)
  {
    int arr[row * col];
    int index = 0;
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        arr[index] = p[i][j];
        index++;
      }
    }
    for (int i = 0; i < row * col; i++)
    {
      for (int j = i + 1; j < row * col; j++)
      {
        if (arr[i] > arr[j])
        {
          int temp = arr[i];
          arr[i] = arr[j];
          arr[j] = temp;
        }
      }
    }
    return arr[k - 1];
  }

  Matrix Transpose()
  {
    Matrix transMatx(0, 0, 0, 0, col, row);
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        transMatx.p[j][i] = p[i][j];
      }
    }
    return transMatx;
  }
  ~Matrix()
  {
    cout<<"\nDestructor called\n";
    for (int i = 0; i < row; i++)
    {
      delete[] p[i];
    }
    delete[] p;
  }
};
int main()
{
  
  Matrix mat(1, 2, 3, 4);
  int rows=mat.getRows(),cols=mat.getCols();
  int totalElements=rows+cols;
  cout << "The highest value in mat for row 1 is " << mat.HighestInRow(1) << endl;
  cout << "the sum of right diagonal is " << mat.RightDiagonalTotal() << endl;
  mat.displayMatrix();
  cout<<"Transposed matrix is \n";
  mat.Transpose().displayMatrix();
  Matrix mat1(mat);
  cout<<"Mat 1 is a copy of mat"<<endl;
  mat1.displayMatrix();
  int k=0;
  do{
    cout<<"Find the kth smallest value. Enter k: \t";
    cin>>k;
  }
  while(k<0 || k>totalElements);
  cout<<"The "<<k<<"th smallest value is "<<mat1.findSmallestk(k)<<endl;
  cout<<"Both matrix multiplied together are:\n";
  int **arr = mat.MatrixMultiply(mat1);
  for (int i =0 ; i<rows ; i++){
    for(int j =0 ; j<cols ; j++){
      cout<<arr[i][j];
    }
    cout<<endl;
  }
  return 0;
  
}
