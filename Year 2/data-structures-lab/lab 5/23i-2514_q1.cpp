#include <iostream>
using namespace std;

struct Patient
{
    int age;
    string name;
    int severity;
    Patient *link;

    Patient(int age = 0, string name = "", int severity = 0)
    {
        this->age = age;
        this->name = name;
        this->severity = severity;
        this->link = NULL;
    }
    ~Patient()
    {
        cout << "\ndestroyed: " << this->name;
    }
};
class Queue
{
private:
    Patient *head;

public:
    Queue()
    {
        head = NULL;
    }
    ~Queue()
    {
        // traverse Queue and delete each Patient until reach null
        Patient *current = head;
        while (current != NULL)
        {
            Patient *nextPatient = current->link;
            delete current;
            current = nextPatient;
        }
        head = NULL;
    }

    void insertAtHead(int age, string name, int severity)
    {
        // create new Patient and set its values
        Patient *newPatient = new Patient(age, name, severity);

        if (isEmpty())
        {
            head = newPatient;
        }
        else
        {
            // when head isnt null store its address in new Patient
            newPatient->link = head;
            head = newPatient;
        }
    }
    void enqueue(int age, string name, int severity)
    {
        // make the Patiente
        Patient *temp = new Patient(age, name, severity);
        // if empty Queue
        if (isEmpty())
        {
            head = temp;
        }
        else
        {
            // check if priority
            if (severity >= 9)
            {
                insertAtHead(age, name, severity);
                return;
            }
            Patient *current = head;
            while (current->link != NULL)
            {
                current = current->link;
            }
            current->link = temp;
        }
        // traverse until current->next ==NULL
    }

    // delete functions
    void dequeue()
    {
        if (!isEmpty())
        {
            Patient *temp = head; // store old head/first Patient
            head = head->link; // new head is next Patient
            delete temp;       // delete old head/first Patient
        }
    }
    void peek()
    {
        if (!isEmpty())
        {
            cout << "Name: " << head->name << " Age: " << head->age << " Severity: " << head->severity << "\n";
        }
    }
    bool isEmpty()
    {
        return head == NULL;
    }
    void printQueue()
    {
        cout << endl;
        Patient *temp = head;
        while (temp != NULL)
        {
            cout <<" Name: "<< temp->name << " Age: "<<temp->age <<" Severity: "<< temp->severity << "\n";

            temp = temp->link;
        }
        cout << "NULL\n";
    }
};
int main()
{
    Queue queue;
    queue.enqueue(1,"yousuf",3);
    queue.printQueue();
    queue.enqueue(10,"ayesha",5);
    queue.printQueue();
    queue.enqueue(15,"ahmed",7);
    queue.printQueue();
    queue.enqueue(20,"ali",9);
    cout<<"Ali had priority so he was inserted at head:\n";
    cout<<"peeking top of queue: \n";
    queue.peek();

    return 0;
}