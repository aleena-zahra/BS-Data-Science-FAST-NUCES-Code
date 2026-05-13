#include <iostream>
using namespace std;
void print(int starCount,int spaceCount){
    if (starCount <= 0 && spaceCount <= 0){
        return;
    }
    else if(starCount <= 0){
        cout << "  ";
        print( starCount,spaceCount-1);
    }
    else{
    cout << "* ";
    print(--starCount,spaceCount);
    }

}

void diamondShape(int num,int star,int space=1,int count=1){
    if ( count == num){
        return;
    }
    print(star,0);
    print(0,space);
    print(star,0);
    cout << endl;
    if(count<((num+1)/2)-1){
    diamondShape(num,--star, space+=2,++count);
    }
    else{
        diamondShape(num,++star,space-=2,++count);
    }
}

int main() {
    int userNum, topRows, bottomRows;
    cout << "enter odd num: ";
    cin >> userNum;
    if(userNum%2==0){
        userNum+=1;
        }
    //first line 
    print(userNum,0);
    cout << endl;
    diamondShape(userNum,((userNum+1)/2)-1);
    

    return 0;
}
