#include<iostream>
using namespace std;

void pattern(int waveLength , int waveHeight){
    for(int i = 0 ; i<waveHeight ; i++){
        for(int j =0 ; j<waveLength ; j++){
            for(int k=0 ; k<waveHeight ; k++){
                if(i+k==waveHeight-1 || i==k){
                    cout<<"*";
                }
                else cout<<" ";
            }
        }
        cout<<endl;
    }
}
int main(){
    for(int i=3,j=3 ; i<=8 ; i++, j+=2){
        cout<<"pattern for "<<i<<" and "<<j <<" is:\n";
        pattern(i,j);
        cout<<endl<<endl;
    }
    return 0;
}


