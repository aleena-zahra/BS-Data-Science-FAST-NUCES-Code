#include<iostream>
using namespace std;
struct car{
    int petrolAmount;
    void setPetrol(int petrol){
        petrolAmount = petrol;
    }
    void setPetrolLevel(int petrol){
        if(petrol<45 && petrol>0){
            petrolAmount = petrol;
        }
        else cout<<"wrong petrol\n";

    }
    int getPetrolLevel(){
        return petrolAmount;
    }
    bool MoveCar(int distance) {
        if(petrolAmount<distance){
            cout<<"too less petrol\n";
            return false;
        }
        else {
            petrolAmount-=distance;
            return true;
        }
    }
    void Refill(){
        petrolAmount=45;
    } 
    bool isEmpty(){
        if (petrolAmount==0){
            return true;
        }
        else return false;
    }
};
int main(){
    car myCar;
    myCar.setPetrol(45);
    myCar.MoveCar(1);
    int integer = myCar.getPetrolLevel();
    cout<<integer<<endl;
    return 0;
}