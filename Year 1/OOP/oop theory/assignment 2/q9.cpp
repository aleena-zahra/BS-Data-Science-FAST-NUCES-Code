#include<iostream>
using namespace std;
void hollowDiamondPattern(int num, int i, int j){
    if(i>=1){
        if(j>=1){
            if(j==num || i == num || i==1 || j==1 ){
                cout<<"*";
                hollowDiamondPattern(num,i,j-1);
            }
            else if(i+j > (((num + 1)/2)+num -1) ){
                cout<<"*";
                hollowDiamondPattern(num,i,j-1);
            }
            else if(i+j < ((num + 1)/2 +2) ){
                cout<<"*";
                hollowDiamondPattern(num,i,j-1);
            }
            else if(i>=(2*j) && i>=((num + 1)/2)){
                cout<<"*";
                hollowDiamondPattern(num,i,j-1);
            }
            else if(j>=(2*i) && i<=((num + 1)/2) && j>=((num + 1)/2)){
                cout<<"*";
                hollowDiamondPattern(num,i,j-1);
            }
            else {
                cout<<" ";   
                hollowDiamondPattern(num,i,j-1);
            }
        }
        else {
            cout<<endl;
            hollowDiamondPattern(num,i-1,num);
        }
    }
    else return;
    
}
int main(){
    int num=21;
   // cout<<"enter a number:\t";
   //cin>>num;
   if(num%2==0){
    num+=1;
   }
   
   hollowDiamondPattern(num,num,num);
   return 0;
}