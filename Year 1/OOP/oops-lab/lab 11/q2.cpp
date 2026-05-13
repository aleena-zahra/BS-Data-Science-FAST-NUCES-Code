#include<iostream>
using namespace std;
class counter{
    private:
    int count;
    
    public:
    counter(){
        count=0;
    }
    counter& operator++(int x){
        counter temp(*this);
        this->count++;
        return temp;
    }
    counter operator++(){
        ++count;
        return *this;
    }
    int getCount(){
        return this->count;
    }
    friend ostream& operator<<(ostream& out, counter other);
};
ostream& operator<<(ostream& out, counter other){
    out<<other.count;
    return out;
}
int main(){
    counter count;
    
    cout<<"After postincrement count is "<<count++;
    cout<<endl;
    cout<<"After preincrement count is "<<++count;
    cout<<endl;
    return 0;
}