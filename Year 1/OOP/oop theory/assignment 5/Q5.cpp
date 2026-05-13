#include <iostream>
using namespace std;

class Time
{
private:
// You will need three integer data members to store the hours, minutes, and seconds.
int hours;
int minutes;
int seconds;
public:
Time(int hours = 0, int minutes = 0, int seconds = 0): hours(hours), minutes(minutes), seconds(seconds) {};
Time(const Time& copy){
    this->hours = copy.hours;
    this->minutes = copy.minutes;
    this->seconds = copy.seconds;
    
}
int calculateTotalTime()const {
    //converts time to seconds
    return this-> hours * 3600 + this-> minutes * 60 + this-> seconds;
}
void fixTime(){
    //takes time in seconds and assigns to hours,mins, all dat
    int totalSeconds = calculateTotalTime();
    this-> hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    this-> minutes = totalSeconds / 60;
    this-> seconds = totalSeconds % 60;
}
Time operator+(const Time& val) const{
    Time addedTime;
    addedTime.hours = this->hours + val.hours;
    addedTime.minutes = this->minutes + val.minutes;
    addedTime.seconds = this->seconds + val.seconds;
    addedTime.fixTime();
    return addedTime;
}
Time operator-(const Time& val) const{
    Time addedTime;
    addedTime.hours = this->hours - val.hours;
    addedTime.minutes = this->minutes - val.minutes;
    addedTime.seconds = this->seconds - val.seconds;
    addedTime.fixTime();
    return addedTime;
}
// Compound Assignment Operators
Time& operator+=(const Time& rhs){
    this->hours = this->hours + rhs.hours;
    this->minutes = this->minutes+ rhs.minutes;
    this->seconds = this->seconds + rhs.seconds;
    fixTime();
    return *this;
}
Time& operator-=(const Time& rhs){
    this->hours = this->hours - rhs.hours;
    this->minutes = this->minutes- rhs.minutes;
    this->seconds = this->seconds - rhs.seconds;
    fixTime();
    return *this;
}
bool operator==(const Time& val) const{
    return val.hours==hours && val.minutes==minutes && val.seconds == seconds;
}
bool operator!=(const Time& val) const{
    return val.hours != hours || val.minutes != minutes || val.seconds != seconds;
}
bool operator<(const Time& val) const{
    int totalTime = calculateTotalTime(),totalTime2 = val.calculateTotalTime();
    return totalTime <totalTime2;
}
bool operator<=(const Time& val) const{
    int totalTime = calculateTotalTime(),totalTime2 = val.calculateTotalTime();
    return totalTime <=totalTime2;
}
bool operator>(const Time& val) const{
    int totalTime = calculateTotalTime(),totalTime2 = val.calculateTotalTime();
    return totalTime >totalTime2;
}
bool operator>=(const Time& val) const{
    int totalTime = calculateTotalTime(),totalTime2 = val.calculateTotalTime();
    return totalTime >=totalTime2;
}
Time elapsedTime() const{ // Calculate elapsed time
     //current device time
    time_t now = time(0);
    // Convert to local time
    struct tm *local_time = localtime(&now);
    // Extract hours, minutes, and seconds
    int hours = local_time->tm_hour;
    int minutes = local_time->tm_min;
    int seconds = local_time->tm_sec;
    Time currentDeviceTime(hours,minutes,seconds);
    currentDeviceTime.fixTime();
    cout<<"The currentDeviceTime is";
    cout<<currentDeviceTime;
    Time result = *this - currentDeviceTime;
    result.fixTime();
    return result;
}
~Time(){}
friend ostream& operator<<(ostream& output, const Time& val); // outputs the Time
friend istream& operator>>(istream& input, Time& val); // inputs the Time
};
ostream& operator<<(ostream& output, const Time& val){
    cout<<"\nHours: ";
    output<< val.hours;
    cout<<"\nMinutes: ";
    output<< val.minutes;
    cout<<"\nSeconds:";
    output<< val.seconds;
    return output;
} 
istream& operator>>(istream& input, Time& val){
    cout<<"Enter Hours:\t ";
    input >> val.hours;
    cout<<"Enter Minutes:\t ";
    input >> val.minutes;
    cout<<"Enter Seconds:\t";
    input >> val.seconds;
    return input;
} 
int main(){
    Time adventureTime; 
    Time deadline(12,59,59);
    cout<<"Enter Adventure Time\n";
    cin>>adventureTime;
    cout << "\nAdventure Time is:\n " << adventureTime;
    cout << "\nDeadline Time is:\n " << deadline;
    Time sum = adventureTime + deadline;
    cout << "\nAdventure Time added to Deadline Time is:\n" << sum << endl;
    Time diff = adventureTime - deadline;
    adventureTime +=deadline;
    cout << "\nCompound + assignment to Adventure Time with Deadline Time is:\n";
    cout<<adventureTime;
    adventureTime -= deadline;
    cout << "\nCompound - assignment to Adventure Time with Deadline Time is:\n";
    cout<<adventureTime;
    cout << "\nAdventure Time subtracted from Deadline Time is:\n" << diff;
    if(adventureTime == deadline) cout << "\nAdventure Time =  Deadline Time\n";
    if(adventureTime != deadline) cout << "\nAdventure Time !=  Deadline Time\n";
    if(adventureTime > deadline) cout << "\nAdventure Time > Deadline Time\n";
    if(adventureTime >= deadline) cout << "\nAdventure Time >=  Deadline Time\n";
    if(adventureTime < deadline) cout << "\nAdventure Time < Deadline Time\n";
    if(adventureTime <= deadline) cout << "\nAdventure Time <=  Deadline Time\n";
    cout<<"The elapsed time between current time and deadline time is \n";
    cout<< deadline.elapsedTime();
    return 0;

}
