#include <iostream>
using namespace std;

struct Carriage
{
    int carriageID;
    int capacity;
    Carriage *next;
    Carriage *prev;

    Carriage(int carriageID, int capacity)
    {
        this->carriageID = carriageID;
        this->capacity = capacity;
        this->next = NULL;
        this->prev = NULL;
    }
    ~Carriage()
    {
        cout << "\ndestroyed Carriage: " << this->carriageID;
    }
};
class Train
{
private:
    Carriage *head;
    Carriage *tail;

public:
    Train()
    {
        head = NULL;
        tail = NULL;
    }
    ~Train()
    {
        // traverse Train and delete each Carriage until reach null
        Carriage *current = head;
        while (current != NULL)
        {
            Carriage *nextCarriage = current->next;
            delete current;
            current = nextCarriage;
        }
        head = NULL;
    }

    void insertAtHead(int carriageID, int capacity)
    {
        // create new Carriage and set its values
        Carriage *newCarriage = new Carriage(carriageID, capacity);

        if (isEmpty())
        {
            head = newCarriage;
            tail = newCarriage;
        }
        else
        {

            newCarriage->next = head;
            head = newCarriage;
        }
    }
    void insertAtEnd(int carriageID, int capacity)
    {
        // make the Carriagee
        Carriage *newCarriage = new Carriage(carriageID, capacity);
        // if empty Train
        if (head==NULL)
        {
            head = newCarriage;
            tail= newCarriage;
        }
        else
        {
            Carriage *curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newCarriage;
        
            newCarriage->prev = curr;
            tail = newCarriage;
        }
    }

        // delete functions
        void deleteStartCarriage()
        {
            if (!isEmpty())
            {
                Carriage *temp = head; // store old head/first Carriage
                head = head->next;     // new head is next Carriage
                delete temp;           // delete old head/first Carriage
                head->prev = NULL;
            }
        }
        void deleteLastCarriage()
        {
            if (!isEmpty())
            {
                Carriage *temp = tail; // store old tail/last Carriage
                tail = tail->prev;     // new tail is prev Carriage
                delete temp;           // delete old tail/last Carriage
                tail->next = NULL;
            }
           
        }

        bool isEmpty()
        {
            return head == NULL;
        }
        void printTrain()
        {
            cout << endl;
            Carriage *temp = head;
            while (temp != NULL)
            {
                cout << temp->carriageID << " -> ";

                temp = temp->next;
            }
            cout << "NULL\n";
        }
        // finds if value exists in next, returns index
        int findValueInTrain(int carriageID)
        {
            Carriage *temp = head;
            int index = -1;
            while (temp != NULL)
            {
                index++;
                if (temp->carriageID == carriageID)
                {
                    break;
                }
                temp = temp->next;
            }
            if (temp != NULL)
                cout<<"Found at index: "<<index;
            else cout<<"Not found";
        }
    };
    int main()
    {
        Train Train;
        Train.insertAtEnd(1, 10);
        Train.printTrain();
        Train.insertAtEnd(2, 20);
        Train.printTrain();
        Train.insertAtHead(3,10);
        Train.printTrain();
        Train.insertAtEnd(4, 30);
        Train.printTrain();
        Train.deleteLastCarriage();
        Train.printTrain();
        Train.deleteStartCarriage();
        Train.printTrain();
        Train.findValueInTrain(2);
        
        return 0;
    }
