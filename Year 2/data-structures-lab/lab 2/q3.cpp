#include <iostream>
using namespace std;

class LibraryCatalog
{
    int *books;
    int totalBooks;

public:
    LibraryCatalog()
    {
        books = nullptr;
        totalBooks = 0;
    }
    LibraryCatalog(int *books,  int size)
    {
        totalBooks = size;
        this->books = new int[totalBooks];
        for (int i = 0; i < size; i++)
        {
            this->books[i] = books[i];
        }
    }
    LibraryCatalog(const LibraryCatalog &copy)
    {
        this->totalBooks = copy.totalBooks;
        this->books = new int[totalBooks];
        for (int i = 0; i < this->totalBooks; i++)
        {
            this->books[i] = copy.books[i];
        }
    }
    ~LibraryCatalog()
    {
        delete [] books;
    }
   
    void printCatalog()
    {
        cout << "\n\t\t\tBOOK RECORD\n";
        cout << "---------------------------------------------------------------------\n\n";
        for (int i = 0 ; i<totalBooks ; i++)
        cout << "Book ID: " << books[i] << "  ";
        cout << "\n---------------------------------------------------------------------\n\n";
    
    }
    //Insert bookId into the catalog. Ensure
    //the list remains sorted.
    void addBook(int bookID)
    {
        int tempSize = this->totalBooks+1;
        int *tempBooks = new int[tempSize];
        int i=0;
        for( i = 0 ; i<totalBooks && books[i]<=bookID; i++){
            tempBooks[i] = books[i];
        }
        tempBooks[i] = bookID;
        for(int k = i+1 ; k<totalBooks ; k++){
            tempBooks[k] = books[k-1];
        }
        delete [] books;
        books = tempBooks;
        this->totalBooks = this->totalBooks +1;
        
    }

    //Binary Search
    int findBookID(int bookID) const
    {
        int left = 0, right = totalBooks - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (books[mid] == bookID)
                return mid; 
            else if (books[mid] < bookID)
                left = mid + 1; 
            else
                right = mid - 1;
        }
        return -1; 
    }

};
int main()
{
    int size =5;
    int libraryBooks[size] = {1,20,45,67,99};
    LibraryCatalog bookNookLibrary(libraryBooks,size);
    cout<<"Original library has:\n";
    bookNookLibrary.printCatalog();
    bookNookLibrary.addBook(33);
    cout<<"After adding book 33:\n";
    bookNookLibrary.printCatalog();
    int bookID = 0;
    cout<<"Enter a book ID to search in the book nook library catalog:";
    cin>>bookID;
    if(bookNookLibrary.findBookID(67) != -1){
        cout<<"\nThe library contains this Book ID\n";
    }
    else cout<<"Book not avaliable\n";
    
    return 0;
}