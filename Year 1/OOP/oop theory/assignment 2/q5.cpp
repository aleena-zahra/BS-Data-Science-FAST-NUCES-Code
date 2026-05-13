//Aleena Zahra 23i-2514 BDS-2B OOP ASSIGNMENT 2
#include<iostream>
using namespace std;
int countAllCombinations (int a, int b);
int countvalidCombinations (int count,int a, int b);
int main(){
    cout<<"This program finds the total possible combinations of votes of two candidates\n";
    cout<<"This program also finds the possible combinations for which A is in the lead\n";
    int totalVotesForA,totalVotesForB;
    cout<<"Enter total Votes A got:\t";
    cin>>totalVotesForA;
    cout<<"Enter total Votes B got:\t";
    cin>>totalVotesForB;
    int count=0;
    int validCombinations = countvalidCombinations(count,totalVotesForA, totalVotesForB);
    int totalCombinations = countAllCombinations(totalVotesForA, totalVotesForB);
    cout << "Total Possible Ways/Permutaions of Votes are:  " << totalCombinations << endl;
    cout << "Out of those, valid Combinations of Votes, for which A is ahead are: " << validCombinations << endl;
    return 0;
}
int countAllCombinations (int a, int b) {
    //iff both peoples Votes end
	if (a == 0 && b == 0){
        return 1;
    } 
    //if A's end and B's are left
    else if (a == 0){
        return countAllCombinations(a, b - 1);
    } 
    //if B's end but A's are left
    else if (b == 0){
        return countAllCombinations(a - 1, b);
    } 
    else{
        //both have some left
        return countAllCombinations(a - 1, b) + countAllCombinations(a, b - 1);
    }

}
int countvalidCombinations (int count,int a, int b) {
    //if someone's Votes end
	if (a == 0 || b == 0) {
        return 1;
    }
    // next vote for A
    else if (count <= 0) {
        return countvalidCombinations(++count, --a, b);
    } else {
        //next vote can be for A or not
        return countvalidCombinations(++count, --a, b) + countvalidCombinations(--count,a, --b);
    }

}
