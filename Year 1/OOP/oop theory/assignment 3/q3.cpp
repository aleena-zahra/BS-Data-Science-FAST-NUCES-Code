// Aleena Zahra 23i-2514 BDS-B OOP Assignment 3
#include <iostream>
#include <string>
using namespace std;

class HotelBooking
{
    string bookingID;
    string customerName;
    string hotelName;
    string roomType;
    string checkInDate;
    string checkOutDate;
    int stayDuration;
    double roomRate;

public:
    HotelBooking(string bookingID, string customerName, string hotelName, string roomType,
                 string checkIn, string checkOut)
    {
        this->bookingID = bookingID;
        this->customerName = customerName;
        this->hotelName = hotelName;
        this->roomType = roomType;
        checkInDate = checkIn;
        checkOutDate = checkOut;
    }
    void setID(string ID)
    {
        bookingID = ID;
    }
    string getID()
    {
        return bookingID;
    }
    bool validateBookingID() const
    {
        if (bookingID.length() != 14)
            return false;
        for (int i = 0; i < 8; i++)
        {
            if (!isalpha(bookingID[i]))
                return false;
        }
        for (int i = 8; i < 10; i++)
        {
            if (!ispunct(bookingID[i]))
                return false;
        }
        int sum = 0;
        for (int i = 10; i < 14; i++)
        {
            if (!isdigit(bookingID[i]))
                return false;
            sum += bookingID[i] - '0'; // sum += static_cast<int>(bookingID[i]);
        }
        if (sum > 18)
            return false;

        return true;
    }

    void setRoomRate(int price)
    {
        roomRate = price;
    }

    double calculateRoomRate()
    {
        if (roomType == "Suite")
        {
            setRoomRate(120);
        }
        else if (roomType == "Bunk")
        {
            setRoomRate(50);
        }
        else if (roomType == "Apartment")
        {
            setRoomRate(60);
        }
        else if (roomType == "Standard")
        {
            setRoomRate(100);
        }
        else if (roomType == "Studio")
        {
            setRoomRate(40);
        }
        else setRoomRate(0);
        return roomRate;
    }
    void calculateStayDuration()
    {
        if (checkInDate == checkOutDate)
        {
            stayDuration = 1;
        }
        else
        {
            int checkInDay = static_cast<int>(checkInDate[0] - '0') * 10 + static_cast<int>(checkInDate[1] - '0');
            int checkInMonth = static_cast<int>(checkInDate[3] - '0') * 10 + static_cast<int>(checkInDate[4] - '0');
            int checkInYear = static_cast<int>(checkInDate[6] - '0') * 1000 + static_cast<int>(checkInDate[7] - '0') * 100 + static_cast<int>(checkInDate[8] - '0') * 10 + static_cast<int>(checkInDate[9] - '0');
            int checkInDays = checkInYear * 365 + checkInMonth * 30 + checkInDay;
            int checkOutDay = static_cast<int>(checkOutDate[0] - '0') * 10 + static_cast<int>(checkOutDate[1] - '0');
            int checkOutMonth = static_cast<int>(checkOutDate[3] - '0') * 10 + static_cast<int>(checkOutDate[4] - '0');
            int checkOutYear = static_cast<int>(checkOutDate[6] - '0') * 1000 + static_cast<int>(checkOutDate[7] - '0') * 100 + static_cast<int>(checkOutDate[8] - '0') * 10 + static_cast<int>(checkOutDate[9] - '0');
            int checkOutDays = checkOutYear * 365 + checkOutMonth * 30 + checkOutDay;
            stayDuration = checkOutDays - checkInDays;
        }
    }

    double calculateTotalCost() const
    {
        return roomRate * stayDuration;
    }

    void getBookingDetails() const
    {
        int userInput;
        do
        {
            cout << "ENTER A NUM FOR THE BOOKING DETAILS YOUD LIKE\n";
            cout << "1. bookingID 2.customerName 3. hotelName 4.roomType \n5.checkInDate 6.checkOutDate 7.stayDuration 8.RoomRate\n";
        cin>>userInput;
        } while (userInput > 8 || userInput < 1);
        switch (userInput)
        {
        case 1:
            cout << "YOUR bookingID IS " << bookingID << endl;
            break;
        case 2:
            cout << "YOUR customerName IS " << customerName << endl;
            break;
        case 3:
             cout << "YOUR hotelName IS " << hotelName << endl;
            break;
        case 4:
            cout << "YOUR roomType IS " << roomType << endl;
            break;
        case 5:
            cout << "YOUR checkInDate IS " << checkInDate << endl;
            break;
        case 6:
            cout << "YOUR checkOutDate IS " << checkOutDate << endl;
            break;
        case 7:
            cout << "YOUR stayDuration IS " << stayDuration << endl;
            break;
        case 8:
            cout << "YOUR roomRate IS " << roomRate << endl;
            break;
        
        default:
            break;
        }
    }

// a const member function to return details of the hotel booking including booking ID,
// customer name, hotel, room type,checkin and checkout dates, stay duration, room rate,total cost
void
updateBookingInfo()
{
    int userChoice;
    do
    {
        cout << "To update information pick the appropriate number\n";
        cout << "1. Check-in Date   2. Room Type\n";
        cout << "3. Check-out Date  4. Hotel\n";
        cin >> userChoice;
    } while (userChoice > 4 && userChoice < 1);
    switch (userChoice)
    {
    case 1:
        cout << "Enter check in date\n";
        cin >> checkInDate;
        calculateTotalCost();
        break;
    case 2:
        cout << "Enter the room type you'd like to stay\n";
        cin >> roomType;
        break;
    case 3:
        cout << "Enter check out date\n";
        cin >> checkOutDate;
        break;
    case 4:
        cout << "Enter hotel you'd like to stay\n";
        cin >> hotelName;
        break;

    default:
        break;
    }
}
void showBookingInfo()
{
    calculateRoomRate();
    cout << "YOUR bookingID IS " << bookingID << endl;
    cout << "YOUR customerName IS " << customerName << endl;
    cout << "YOUR hotelName IS " << hotelName << endl;
    cout << "YOUR roomType IS " << roomType << endl;
    cout << "YOUR checkInDate IS " << checkInDate << endl;
    cout << "YOUR checkOutDate IS " << checkOutDate << endl;
    cout << "YOUR stayDuration IS " << stayDuration << endl;
    cout << "YOUR roomRate IS " << roomRate << endl;
}
}
;
bool validateDateFormat(const string &date)
{
    if (date.length() != 10)
        return false;
    if ((date[0] >= '3' && date[1] > '1') || date[3] >= '1' && date[4] > '2')
    {
        return false;
    }
    if (date[2] != '/' || date[5] != '/')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;
        if (date[i] < '0' || date[i] > '9')
            return false;
    }
    return true;
}

int main()
{
    string *ID = new string[50];
    string *userName = new string[50];
    string *roomType = new string[50];
    string *checkIn = new string[50];
    string *checkOut = new string[50];
    string *hotelName = new string[50];
    cout << "WELCOME TO OUR HOTEL\n";
    cout << "Please Enter your name\n";
    getline(cin, *userName);
    cout<<"Enter hotel youd like to stay\n";
    getline(cin, *hotelName); 
    do
    {
        cout << "Enter the room Type you prefer\n";
        cout << "1. Suite 2. Bunk 3. Standard 4. Apartment 5. Studio\n";
        cin >> *roomType;
        cin.ignore();
    } while (*roomType != "Suite" && *roomType != "Bunk" && *roomType != "Standard" && *roomType != "Studio" && *roomType != "Apartment");
    cout << "Please Enter your checkIn Date in the format (dd/mm/yyyy)\n";
    getline(cin, *checkIn);
    while (!validateDateFormat(*checkIn))
    {
        cout << "Invalid format. Please enter the check in date in the format (dd/mm/yyyy): ";
        getline(cin, *checkIn);
    }
    cout << "Please Enter your check out Date in the format (dd/mm/yyyy)\n";
    getline(cin, *checkOut);
    while (!validateDateFormat(*checkOut))
    {
        cout << "Invalid format. Please enter the check out date in the format (dd/mm/yyyy): ";
        getline(cin, *checkOut);
    }
    cout << "Please enter your unique ID that is 14 digits long,\n the first 8 digits must be letters \nthe next 2 special characteres \nand the last 4 digits with a sum not exceeding 18\n";
    getline(cin, *ID);
    cout << "ID IS " << *ID << endl;
    HotelBooking room1(*ID, *userName, *hotelName, *roomType, *checkIn, *checkOut);
    while (!room1.validateBookingID())
    {
        cout << "Please enter your unique ID that is 14 digits long,\n the first 8 digits must be letteres \nthe next 2 special characteres \nand the last 4 digits with a sum not exceeding 18\n";
        getline(cin, *ID);
        room1.setID(*ID);
        cout << room1.getID();
    }
    room1.setID(*ID);
    room1.calculateStayDuration();
    room1.calculateRoomRate();
    room1.calculateTotalCost();
    room1.getBookingDetails();
    room1.updateBookingInfo();
    room1.showBookingInfo();
    delete[] ID;
    delete[] userName;
    delete[] roomType;
    delete[] checkIn;
    delete[] checkOut;
    delete[] hotelName;
    return 0;
}