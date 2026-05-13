// Aleena Zahra 23i-2514 BDS-B OOP Assignment 3
#include <iostream>
using namespace std;

class Icecream
{
private:
    char *flavour;
    char *topping;
    char *servingType;
    bool isReady=false;
    double price=0;

public:
    Icecream() {}
    Icecream(char *flavour, char *topping, char *servingType, double price){
        this->flavour = flavour;
        this->topping = topping;
        this->servingType = servingType;
        this->price = price;
    }
    Icecream(char *topping, double price){
        this->topping = topping;
        this->price = price;
    }
    Icecream(const Icecream &icecream){
        this->flavour = flavour;
        this->topping = topping;
        this->servingType = servingType;
        this->price = price;
    }
    ~Icecream(){
    }
    void setFlavour(char *flavour1){
        flavour = flavour1;
        
    }
    void setTopping(char *topping1){
        topping = topping1;
    }
    void setServingType(char *servingType1){
        servingType = servingType1;
    }
    void setPrice(double price1){
        price+=price1;
    }
    char *getFlavour(){
        return flavour;
    }
    char *getTopping() const{
        return topping;
    }
    char *getServingType() const{
        return servingType;
    }
    double getPrice() const{
        return price;
    }

    void makeIcecream()
    {
        if (*(getTopping()) != '\0'){
            isReady = true;
        }
    }
    bool checkStatus()
    {
        if (isReady){
            return true;
        }
        else
            return false;
    }
};

int main()
{
    string flavour;
    char *p = &flavour[0];
    string topping="";
    char *t = &topping[0];
    string serveType="";
    char *s = &serveType[0];
    bool wantsIcecream;
    cout << "Welcome to Soft Swirl Icecreams!\n";
    cout << "We have all the classic options and much more\n";
    cout<<"Would you like an icecream?(Press 1 for Yes and 0 for No)\t";
    cin>>wantsIcecream;
    Icecream icecream(p,t,s,0.0);
    
    while(wantsIcecream){
        cout << "1. Select Icecream Flavour            2. Select Icecream Serve\n";
        cout << "3. Select Icecream Topping            4. Check Status\n";
        cout << "5. Exit Program                       6.Order Complete\n";
        int userChoice;
        cin >> userChoice;
        if(userChoice == 1){
            cout << "Select a number to pick which icecream you would like\n";
            cout << "1. Chocolate-40           2. Vanilla-40\n3. Mango -40              4. Chocolate Chilli-60\n";
            cout << "5. Peanut Butter-80       6. Pizza-120\n";
            int userFlavourChoice;
            cin >> userFlavourChoice;
            switch (userFlavourChoice){
            case 1:
                flavour = "Chocolate";
                icecream.setPrice(40.0);
                icecream.setFlavour(p);
                break;
            case 2:
                flavour = "Vanilla";
                icecream.setPrice(40.0);
                icecream.setFlavour(p);
                break;
            case 3:
                flavour = "Mango";
                icecream.setPrice(40.0);
                icecream.setFlavour(p);
                break;
            case 4:
                flavour = "Chocolate Chilli";
                icecream.setPrice(60.0);
                icecream.setFlavour(p);
                break;
            case 5:
                flavour = "Peanut Butter";
                icecream.setPrice(80.0);
                icecream.setFlavour(p);
                break;
            case 6:
                flavour = "Pizza";
                icecream.setPrice(120.0);
                icecream.setFlavour(p);
                break;

            default:
                cout << "Sorry this flavour doesnt exist. But we recommend trying our iconic Pizza flavour by pressing 6\n";
                break;
            }
        }
        if(userChoice==2){
            cout << "What Type of Serve would you like?\n";
            cout << "1. Soft Serve-100      2.Cone-50\n3.Sandwich-100         4. Stick-10\n5.Rolled(in a cup)-200\n";
            int userServeChoice;
            cin >> userServeChoice;
            switch (userServeChoice){
            case 1:
                serveType = "Soft Serve";
                icecream.setPrice(100.0);
                icecream.setServingType(s);
                break;
            case 2:
                serveType = "Cone";
                icecream.setPrice(50.0);
                icecream.setServingType(s);
                break;
            case 3:
                serveType = "Sandwich";
                icecream.setPrice(100.0);
                icecream.setServingType(s);
                break;
            case 4:
                serveType = "Stick";
                icecream.setPrice(10.0);
                icecream.setServingType(s);
                break;
            case 5:
                serveType = "Rolled";
                icecream.setPrice(200.0);
                icecream.setServingType(s);
                break;

            default:
                cout << "Option doesnt exist";
                break;
            }    
        }
        if(userChoice==3){
            cout << "Select a number to pick which flavour you would like\n";
            cout << "1. Chocolate Chips-100         2. Oreos-50\n3. Gummy Bears-100            4. Sprinkles-70\n5. Salted Chips-50            6. Fruit-200\n";
            int userToppingChoice;
            cin >> userToppingChoice;
            switch (userToppingChoice){
            case 1:
                icecream.setPrice(100.0);
                topping = "Chocolate Chips";
                icecream.setTopping(t);
                break;
            case 2:
                topping = "Oreos";
                icecream.setPrice(50.0);
                icecream.setTopping(t);
                break;
            case 3:
                topping = "GummyBears";
                icecream.setPrice(100.0);
                icecream.setTopping(t);
                break;
            case 4:
                topping = "Sprinkles";
                icecream.setPrice(70.0);
                icecream.setTopping(t);
                break;
            case 5:
                topping = "Salted Chips";
                icecream.setPrice(50.0);
                icecream.setTopping(t);
                break;
            case 6:
                topping = "Fruit";
                icecream.setPrice(200.0);
                icecream.setTopping(t);
                break;

            default:
                cout << "Sorry this topping doesnt exist. But you can try the classic Sprinkles by pressing 4\n";
                break;
            }
        }
        if(userChoice==4){
            if (icecream.checkStatus())
        {
            cout << "Your icecream order is ready!ENJOY\n";
            cout<<"ICECREAM FLAVOUR: "<<icecream.getFlavour()<<endl;
            cout<<"ICECREAM SERVE TYPE: "<<icecream.getServingType()<<endl;
            cout<<"ICECREAM TOPPING: "<<icecream.getTopping()<<endl;
            cout<<"TOTAL PRICE: "<<icecream.getPrice()<<endl;
            cout<<"Would you like another icecream?Press 1 for Yes , 0 for No";
            cin>>wantsIcecream;
        }
        else {
            cout<<"Your order is still being processed. Please make sure to Enter toppings\n";
        }
        }
        if(userChoice==5){
            wantsIcecream=false;

        }
        if(userChoice==6){
            icecream.makeIcecream();
            cout<<"Your order is now being processed\n";
        }
}
    
    return 0;
}