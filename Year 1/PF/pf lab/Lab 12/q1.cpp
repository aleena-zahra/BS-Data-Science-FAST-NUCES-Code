#include<iostream>
using namespace std;
    void showChoice();  
    int sumFunction(int *n1, int *n2, int *n3, int *n4, int *n5);  
    void swapfunction(int *num1, int *num2);  
    void tableofTwo();  
    int LargestNumber(int *a, int size);  

    int main(){
    int choice;
    showChoice();
    cin>>choice;
    
    
            if (choice ==2){
            int n[5];

            for (int i = 0; i < 5; i++) {
            cout << "Enter number " << i + 1 <<endl;
            cin >> n[i];
            }

            int TotalSum;
            TotalSum = sumFunction(&n[0], &n[1], &n[2], &n[3], &n[4]);

            cout<<"The sum of these five numbers is "<<TotalSum;
            } 
    
    
             else if (choice ==3){
             
             int num1;
             int num2;
             cout<<"Enter Number 1\n";
             cin>>num1;
             cout<<"Enter Number 2\n";
             cin>>num2;
    
            swapfunction(&num1,&num2);
            cout<<"swapped values are "<<num1<<" and "<<num2;
             
             } 
             else if (choice ==4){
             
           tableofTwo();
           }
             
              
             else if (choice ==5){
              int size = 7;
              int a[size];

             cout << "Enter 7 numbers:" << endl;
             for (int i = 0; i < size; i++) {
             cout << "Enter number " << i + 1 << ": ";
             cin >> a[i];
             }       

             int largestNumber = LargestNumber(a, size);

            cout << "The largest number from all 7 is " << largestNumber;

             } 
    
    return 0;
    
    }
    
    void showChoice(){
    cout<<"Press 2 for Task 2 \n";
    cout<<"Press 3 for Task 3 \n";
    cout<<"Press 4 for Task 4 \n";
    cout<<"Press 5 for Task 5 \n";
   
    }
    
    int sumFunction(int *n1, int *n2, int *n3, int *n4, int *n5) {
    int sum;
    sum = *n1 + *n2 + *n3 + *n4 + *n5;
    return sum;
}
    //task 3
    void swapfunction(int *num1,int *num2){
    int newNumber;
    newNumber = *num1;
    *num1 = *num2;
    *num2 = newNumber; 
    }
    //task4
    void tableofTwo() {
    int tableOfTwo[12];
    int *pntr = tableOfTwo;
    for(int i=0 ; i < 12 ; i++){
    tableOfTwo[i]= 2* (i+1);
    }
    for(int i=0 ; i < 12 ; i++){
    cout<<*(pntr+i)<<" ";
    }
}
        
    //task5
    int LargestNumber( int *a, int size){
    int biggestNum = *a;

    for (int i = 1; i < size; i++) {
        if (*(a + i) > biggestNum) {
            biggestNum = *(a + i);
        }
    }

    return biggestNum;
}
