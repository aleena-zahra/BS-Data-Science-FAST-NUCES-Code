//Aleena Zahra 23i-2514 BDS-2B OOP ASSIGNMENT 2
#include<iostream>
using namespace std;
int countRoutes ( int street, int avenue){
    if(street>1 && avenue>1){
        return countRoutes(street-1,avenue) + countRoutes(street,avenue-1);
    }
    else if(avenue>1){
        return countRoutes(street,avenue-1);
    }
    else if(street>1){
        return countRoutes(street-1,avenue);

    }
    else if(avenue==1 && street==1){
        
        return 1;
    }
}
//avenue = j , street =i
int main(){
    int street,avenue;
    cout << "Enter street Karl is on right now:\t";
    cin >> street;
    cout << "Enter avenue Karl is on right now:\t";
    cin>> avenue; 
    cout<<"The total possible shortest routes to street 1 and avenue 1 that Karl can take are: "<<countRoutes(street,avenue);
    return 0;
}

	
	
