#include<iostream>
using namespace std;
class matrix{
    private:
    int rows,cols;
    int ** mat;
    public:
    matrix(int r, int c){
        rows = r;
        cols = c;
        mat = new int*[rows];
        //allocate memory
        for (int i =0 ; i<rows ; i++){
            mat[i] = new int[cols];
        }
        //initialize
        for(int i =0 ; i< rows ; i++){
            for (int j=0 ; j<cols ; j++){
                mat[i][j]=0;
            }
        }
    }
    matrix operator + (matrix other){
        int newRows, newCols=0;
            newRows = rows;
            newCols = cols;
        matrix newMat(newRows,newCols);
        for(int i =0 ; i< rows ; i++){
            for (int j=0 ; j<cols ; j++){
                newMat.mat[i][j] = mat[i][j] + other.mat[i][j];
            }
        }
        return newMat;
    }
    matrix operator - (matrix other){
        int newRows, newCols=0;
        
            newRows = rows;
            newCols = cols;
        matrix newMat(newRows,newCols);
        for(int i =0 ; i< rows ; i++){
            for (int j=0 ; j<cols ; j++){
                newMat.mat[i][j] = mat[i][j] - other.mat[i][j];
            }
        }
        return newMat;
    }
    friend ostream& operator<<(ostream& output, const matrix & val);
    friend istream& operator>>(istream& input, const matrix& val); 
};
istream& operator>>(istream& input, const matrix& val){
        int count =0;
        for(int i =0 ; i< val.rows ; i++){
            for (int j=0 ; j<val.cols ; j++){
                cout<<"\nEnter Element "<<++count;
                input>>val.mat[i][j];
            }
        }
        return input;
    }
   ostream& operator<<(ostream& output, const matrix & val){
        for(int i =0 ; i< val.rows ; i++){
            for (int j=0 ; j<val.cols ; j++){
                output<<val.mat[i][j]<<"  ";
            }
            cout<<endl;
        }
        return output;
    }
int main(){
    int row,col;
    cout<<"Enter number of rows for matrix 1:\t";
    cin>>row;
    cout<<"Enter number of cols for matrix :\t";
    cin>>col;
    matrix m1(row,col),m2(row,col);
    cout<<"input elements of matrix 1\n";
    cin>>m1;
    cout<<"input elements of matrix 2\n";
    cin>>m2;
    cout<<"\nMatrix 1 is \n";
    cout<<m1;
    cout<<"\nMatrix 2 is \n";
    cout<<m2;
    cout<<"Both matrix added together are:\n";
    cout<<(m1+m2);
    cout<<endl;
    cout<<"Matrix 1 subtracted from Matrix 2 is:\n";
    cout<<(m1-m2);
    return 0;
}
