#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Car
{
private:
    string name;
    int year;
    double sellingPrice;
    int kmDriven;
    string fuel;
    string sellerType;
    string transmission;
    int owner;
    double mileage;
    double engine;
    double maxPower;
    double torque;
    int seats;

public:
    // Constructor
    Car()
    {
        name = "";
        year = 0;
        sellingPrice = 0.0;
        kmDriven = 0;
        fuel = "";
        sellerType = "";
        transmission = "";
        owner = 0;
        mileage = 0.0;
        engine = 0.0;
        maxPower = 0.0;
        torque = 0.0;
        seats = 0;
    }
    Car(string n, int y, double sp, int km, string f, string st, string tr, int own, double ml, double eng, double mp, double tq, int s)
        : name(n), year(y), sellingPrice(sp), kmDriven(km), fuel(f), sellerType(st), transmission(tr), owner(own), mileage(ml), engine(eng), maxPower(mp), torque(tq), seats(s) {}

    // Overloading + operator to combine details of 2 cars i.e. Add their SellingPrice, Mileage, Engine, MaxPower, Torque, Assign name with your name Take the rest for 1st Car
    Car operator+(const Car &other) const
    {
        Car addedCar;
        addedCar.engine = this->engine + other.engine;
        addedCar.maxPower = this->maxPower + other.maxPower;
        addedCar.torque = this->torque + other.torque;
        addedCar.sellingPrice = this->sellingPrice + other.sellingPrice;
        addedCar.mileage = this->mileage + other.mileage;
        addedCar.seats = this->seats + other.seats;
        addedCar.kmDriven = this->kmDriven + other.kmDriven;
        addedCar.owner = this->owner + other.owner;
        addedCar.year = this->year + other.year;
        addedCar.name = "added car";
        addedCar.fuel = this->fuel;
        addedCar.sellerType = this->sellerType;
        addedCar.transmission = this->transmission;
        return addedCar;
    }

    // Overloading += operator to combine details of 2 cars i.e. Add their SellingPrice, Mileage, Engine, MaxPower, Torque
    Car &operator+=(const Car &other)
    {
        this->engine += other.engine;
        this->maxPower += other.maxPower;
        this->torque += other.torque;
        this->sellingPrice += other.sellingPrice;
        this->mileage += other.mileage;
        this->seats += other.seats;
        this->kmDriven += other.kmDriven;
        this->owner += other.owner;
        this->year += other.year;
        this->name += other.name;
        this->fuel += other.fuel;
        this->sellerType += other.sellerType;
        this->transmission += other.transmission;
        return *this;
    }

    // Overloading - operator to subtract selling prices of two cars
    double operator-(const Car &other) const
    {
        return this->sellingPrice - other.sellingPrice;
    }

    // Overloading -= operator to subtract details of 2 cars i.e. subtract their SellingPrice, Mileage, Engine, MaxPower, Torque
    Car &operator-=(const Car &other)
    {
        this->engine -= other.engine;
        this->maxPower -= other.maxPower;
        this->torque -= other.torque;
        this->sellingPrice -= other.sellingPrice;
        this->mileage -= other.mileage;
        this->seats -= other.seats;
        this->kmDriven -= other.kmDriven;
        this->owner -= other.owner;
        this->year -= other.year;
        return *this;
    }

    // Overloading == operator to compare details of two cars
    bool operator==(const Car &other) const {
        return this->year == other.year && this->sellingPrice == other.sellingPrice && this->kmDriven == other.kmDriven && this->owner == other.owner && this->mileage == other.mileage && this->engine == other.engine && this->maxPower == other.maxPower && this->torque == other.torque && this->seats == other.seats;
    }

    // Overloading > operator to compare details of (int, float and Double Datatype)
    bool operator>(const Car &other) const {
    if (this->owner != other.owner) return this->owner > other.owner;
    if (this->mileage != other.mileage) return this->mileage > other.mileage;
    if (this->kmDriven != other.kmDriven) return this->kmDriven > other.kmDriven;
    if (this->engine != other.engine) return this->engine > other.engine;
    if (this->maxPower != other.maxPower) return this->maxPower > other.maxPower;
    if (this->torque != other.torque) return this->torque > other.torque;
    if (this->year != other.year) return this->year > other.year; 
    return this->seats > other.seats;
    }

    // Overloading < operator to compare details of (int, float and Double Datatype)
    bool operator<(const Car &other) const
    {
        if (this->year != other.year) return this->year < other.year;
        if (this->kmDriven != other.kmDriven) return this->kmDriven < other.kmDriven;
        if (this->engine != other.engine) return this->engine < other.engine;
        if (this->maxPower != other.maxPower) return this->maxPower < other.maxPower;
        if (this->torque != other.torque) return this->torque < other.torque;
        if (this->owner != other.owner) return this->owner < other.owner;
        if (this->mileage != other.mileage) return this->mileage < other.mileage;   
        return this->seats < other.seats;
    }

    // Overloading >= operator to compare details of (int, float and Double Datatype)
    bool operator>=(const Car &other) const {
        return !(*this < other);
    }

    // Overloading <= operator to compare details of (int, float and Double Datatype)
    bool operator<=(const Car &other) const {
        return !(*this > other);
    }

    // Overloading != operator to compare details of (int, float and Double Datatype)
    bool operator!=(const Car &other) const {}
    string getname() const {
         return name; 
        }
    int getyear() const {
         return year; 
        }
    double getsellingprice() const {
         return sellingPrice; 
        }
    int getkmdriven() const {
         return kmDriven; 
        }
    string getfuel() const {
         return fuel; 
        }
    string getsellertype() const {
         return sellerType; 
        }
    string gettransmission() const {
         return transmission; 
        }
    int getowner() const {
         return owner; 
        }
    double getmileage() const {
         return mileage; 
        }
    double getengine() const {
         return engine; 
        }
    double getmaxpower() const {
         return maxPower; 
        }
    double gettorque() const {
         return torque; 
        }
    int getseats() const {
         return seats; 
        }
    // Display car details
    friend ostream &operator<<(ostream &output, const Car &car);
    void setname(const string& n) {
        name = n; 
        }
    void setyear(int y) {
        year = y; 
        }
    void setsellingprice(double sp) {
        sellingPrice = sp; 
        }
    void setkmdriven(int km) {
        kmDriven = km; 
        }
    void setfuel(const string& f) {
        fuel = f; 
        }
    void setsellertype(const string& st) {
        sellerType = st; 
        }
    void settransmission(const string& tr) {
        transmission = tr; 
        }
    void setowner(int own) {
        owner = own; 
        }
    void setmileage(double ml) {
        mileage = ml; 
        }
    void setengine(double eng) {
        engine = eng; 
        }
    void setmaxpower(double mp) {
        maxPower = mp; 
        }
    void settorque(double tq) {
        torque = tq; 
        }
    void setseats(int s) {
        seats = s; 
        }
    // Input Car Details
    friend istream &operator>>(istream &input, const Car &car) {}
};
ostream &operator<<(ostream &output, const Car &car){
    output << "\nName of car is " << car.getname();
    output << "\nYear of car is " << car.getyear();
    output << "\nSelling Price of car is" << car.getsellingprice();
    output << "\nKm Driven of car is" << car.getkmdriven();
    output << "\nFuel of car is" << car.getfuel();
    output << "\nSeller Type of car is" << car.getsellertype();
    output << "\nTransmission of car is" << car.gettransmission();
    output << "\nOwner of car is" << car.getowner();
    output << "\nMileage of car is" << car.getmileage();
    output << "\nEngine of car is" << car.getengine();
    output << "\nMax Power of car is" << car.getmaxpower();
    output << "\nTorque of car is" << car.gettorque();
    output << "\nSeats of car is" << car.getseats();
}
istream &operator>>(istream &input, Car &car){
    cout << "\nName of car is ";
    string name;
    input >> name;
    car.setname(name);
    cout << "\nYear of car is ";
    int year;
    input >> year;
    car.setyear(year);
    cout << "\nSelling Price of car is ";
    double sellingPrice;
    input >> sellingPrice;
    car.setsellingprice(sellingPrice);
    cout << "\nKm Driven of car is ";
    int kmDriven;
    input >> kmDriven;
    car.setkmdriven(kmDriven);
    cout << "\nFuel of car is ";
    string fuel;
    input >> fuel;
    car.setfuel(fuel);
    cout << "\nSeller Type of car is ";
    string sellerType;
    input >> sellerType;
    car.setsellertype(sellerType);
    cout << "\nTransmission of car is ";
    string transmission;
    input >> transmission;
    car.settransmission(transmission);
    cout << "\nOwner of car is ";
    int owner;
    input >> owner;
    car.setowner(owner);
    cout << "\nMileage of car is ";
    double mileage;
    input >> mileage;
    car.setmileage(mileage);
    cout << "\nEngine of car is ";
    double engine;
    input >> engine;
    car.setengine(engine);
    cout << "\nMax Power of car is ";
    double maxPower;
    input >> maxPower;
    car.setmaxpower(maxPower);
    cout << "\nTorque of car is ";
    double torque;
    input >> torque;
    car.settorque(torque);
    cout << "\nSeats of car is ";
    int seats;
    input >> seats;
    car.setseats(seats);
    return input;
}


class Garage
{
private:
    Car *cars;
    int numOfCars;

public:
    // Constructor to make cars null
    Garage()
    {
        cars = nullptr;
        numOfCars = 0;
    }
    Garage(int size = 1)
    {
        numOfCars = size;
        cars = new Car[numOfCars];
    }
    ~Garage(){
        delete[] cars;
    }
    Car &operator[](int index)
    {
        if (index < 0 || index >= numOfCars)
        {
            return cars[0];
        }
        return cars[index];
    }
    // Overloading + operator to Add car using user input use the operator overloading as done in Car Class
    Garage operator+(const Car &other) const {}

    // Overloading += operator to Add car of another garage
    Garage &operator+=(const Car &other) {}

    // Overloading - operator to remove car using index
    Garage operator-(int index) const {}

    // Overloading -= operator to remove car using name
    Garage &operator-=(const Car &other) {}

    // Overloading == operator to compare details of two Garage for each car
    bool operator==(const  Car &other) const {}

    // Overloading > operator to compare Avg price of 2 garage
    bool operator>(const Garage &other) const {
       
    }

    // Overloading < operator to average maxPower of cars of 2 garage
    bool operator<(const Car &other) const {}

    // Overloading >= operator to compare Average Mileage of 2 Garage
    bool operator>=(const Garage &other) const {
        double averageFirstMileage = 0.0, averageSecondMileage2 = 0.0;
        for (int i = 0; i < numOfCars; ++i) {
            averageFirstMileage += cars[i].getmileage();
        }
        averageFirstMileage /= numOfCars;
        for (int i = 0; i < other.numOfCars; ++i) {
            averageSecondMileage2 += other.cars[i].getmileage();
        }
        averageSecondMileage2 /= other.numOfCars;
        return averageFirstMileage >= averageSecondMileage2;
    }

    // Overloading <= operator to compare Average torque of 2 garage
    bool operator<=(const Garage &other) const {
        double averageFirstTorque = 0.0, averageSecondTorque2 = 0.0;
        for (int i = 0; i < numOfCars; ++i) {
            averageFirstTorque += cars[i].gettorque();
        }
        averageFirstTorque /= numOfCars;
        for (int i = 0; i < other.numOfCars; ++i) {
            averageSecondTorque2 += other.cars[i].gettorque();
        }
        averageSecondTorque2 /= other.numOfCars;
        return averageFirstTorque >= averageSecondTorque2;
    }

    // Overloading != operator to compare No of Cars of 2 garage
    bool operator!=(const Garage &other) const {
        return numOfCars!=other.numOfCars;
    }
    Car* getcars() const {
        return cars; 
        }
    int getnumofcars() const {
        return numOfCars; 
        }
    void setcars(Car* c) {
        cars = c; 
        }
    void setnumofcars(int n) {
        numOfCars = n; 
        }
    friend ostream &operator<<(ostream &output, const Garage &garage);
    
        // Display details of all cars in the garage
    
};
ostream& operator<<(ostream& output, const Garage& garage) {
        for (int i = 0; i < garage.getnumofcars(); ++i) {
            output << "Car " << i + 1 << ":\n";
            output << garage.getcars()+i;
        }
        return output;
    }

int main()
{
    int totalCars = 2;
    Garage cars(totalCars);
    ifstream inputFile("car.csv");

    if (!inputFile.is_open())
    {
        cout << "\nFailed to open file!\n";
        return 1;
    }
    string line;
    int row = 0;
    while (getline(inputFile, line))
    {
        if (row >= totalCars)
        {
            cout << "Maximum number of rows exceeded!\n";
            break;
        }
        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ','))
        {
            cout << cell << ", ";
        }
        cout << endl;
        row++;
    }
    inputFile.close();

    for (int i = 0; i < totalCars; ++i)
    {
        // cout << "\nName of car is " << cars[i].name;
        // cout << "\nYear of car is " << cars[i].year;
        // cout << "\nSelling Price of car is" << cars[i].sellingPrice;
        // cout << "\nKm Driven of car is" << cars[i].kmDriven;
        // cout << "\nFuel of car is" << cars[i].fuel;
        // cout << "\nSeller Type of car is" << cars[i].sellerType;
        // cout << "\nTransmission of car is" << cars[i].transmission;
        // cout << "\nOwner of car is" << cars[i].owner;
        // cout << "\nMileage of car is" << cars[i].mileage;
        // cout << "\nEngine of car is" << cars[i].engine;
        // cout << "\nMax Power of car is" << cars[i].maxPower;
        // cout << "\nTorque of car is" << cars[i].torque;
        // cout << "\nSeats of car is" << cars[i].seats;
    }

    return 0;
}
