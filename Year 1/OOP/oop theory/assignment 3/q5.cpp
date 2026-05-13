// Aleena Zahra 23i-2514 BDS-B OOP Assignment 3
#include <iostream>
using namespace std;

class Library
{
    char *bookTitle;
    char *author;
    int bookID;
    int quantity;
    float price;
    static int totalBooks;

public:
    Library()
    {
        bookTitle = nullptr;
        author = nullptr;
        bookID = 0;
        quantity = 0;
        price = 0.0;
    }
    Library(char *title, char *Author, int ID, int Quantity, float Price)
    {
        bookTitle = title;
        author = Author;
        bookID = ID;
        quantity = Quantity;
        price = Price;
    }
    ~Library()
    {
        cout << "destructor called\n";
        // delete[] bookTitle;
        // delete[] author;
        totalBooks--;
    }
    char *getBookTitle()
    {
        return bookTitle;
    }
    char *getAuthor()
    {
        return author;
    }
    int getBookID()
    {
        return bookID;
    }
    int getQuantity()
    {
        return quantity;
    }
    float getPrice()
    {
        return price;
    }
    void setBookTitle(char *title)
    {

        bookTitle = title;
    }
    void setAuthor(char *authorName)
    {

        author = authorName;
    }
    void setBookID(int ID)
    {

        bookID = ID;
    }
    void setQuantity(int bookQuantity)
    {

        quantity = bookQuantity;
    }
    void setPrice(float bookPrice)
    {

        price = bookPrice;
    }
    static void setTotalBooks(int totalBooksStored)
    {
        totalBooks = totalBooksStored;
    }
    float calcTotalPrice()
    {
        return quantity * price;
    }
    static int getTotalBooks()
    {
        return totalBooks;
    }
    void displayRecords()
    {
        cout << "\t\t\tBOOK RECORD\n";
        cout << "---------------------------------------------------------------------\n\n";
        cout << "Book ID: " << getBookID() << endl;
        cout << "Book Name: " << getBookTitle() << endl;
        cout << "Author Name: " << getAuthor() << endl;
        cout << "Price: " << getPrice() << endl;
        cout << "Quantity: " << getQuantity() << endl;
        cout << "---------------------------------------------------------------------\n\n";
    
    }
};
int Library::totalBooks = 0;

int compareStrings(char *str1, char *str2)
{
    if (str1 == nullptr || str2 == nullptr)
    {
        return 0;
    }
    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
    {
        if (str1[i] > str2[i])
        {
            return 1;
        }
        else if (str1[i] < str2[i])
        {
            return -1;
        }
    }
    return 0;
}

Library getBook_at(Library *books, int index)
{
    return books[index];
}
void addBook(Library *books, Library newBook)
{
    for (int i = 0; i < 100; i++)
    {
        if (books[i].getBookTitle() == nullptr)
        {
            books[i] = newBook;
            return;
        }
    }
    cout << "Library is full!!! NO more books can be Added" << endl;
}

void removeBook(Library *books, int bookID)
{
    for (int i = 0; i < 100; i++)
    {
        if (books[i].getBookID() == bookID)
        {
            delete[] books[i].getBookTitle();
            delete[] books[i].getAuthor();
            books[i] = Library();
            cout << "Book with ID number: " << bookID << " has been removed from Library." << endl;
            return;
        }
    }
    cout << "Book with ID number: " << bookID << " was not found in Library." << endl;
}
void copyTheBook(Library &book1, Library &book2) {
    //temp book = book 1
    char *tempTitle = book1.getBookTitle();
    char *tempAuthor = book1.getAuthor();
    int tempID = book1.getBookID();
    int tempQuantity = book1.getQuantity();
    float tempPrice = book1.getPrice();

    //book 1 = book 2
    book1.setBookTitle(book2.getBookTitle());
    book1.setAuthor(book2.getAuthor());
    book1.setBookID(book2.getBookID());
    book1.setQuantity(book2.getQuantity());
    book1.setPrice(book2.getPrice());

    ///book 2  = temp book
    book2.setBookTitle(tempTitle);
    book2.setAuthor(tempAuthor);
    book2.setBookID(tempID);
    book2.setQuantity(tempQuantity);
    book2.setPrice(tempPrice);
}
void SortByTitle(Library *books, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            char *title1 = books[j].getBookTitle();
            char *title2 = books[j + 1].getBookTitle();

            if (books[j].getBookTitle() != nullptr && books[j + 1].getBookTitle() != nullptr && compareStrings(title1, title2) > 0)
            {
                copyTheBook(books[j],books[j+1]);
            }
        }
    }
}
void SortByAuthor(Library *books, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (books[j].getAuthor() != nullptr && books[j + 1].getAuthor() != nullptr && compareStrings(books[j].getAuthor(), books[j + 1].getAuthor()) > 0)
            {
                copyTheBook(books[j],books[j+1]);
            }
        }
    }
}
void SortByPrice(Library *books, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (books[j].getPrice() != 0.0 && books[j + 1].getPrice() != 0.0 && books[j].getPrice() > books[j + 1].getPrice())
            {
                copyTheBook(books[j],books[j+1]);
            }
        }
    }
}
bool searchByTitle(Library *books, char *titlename, int size)
{
    for (int i = 0; i < size; i++)
    {
        string title = books[i].getBookTitle();
        bool charMatches = true;
        for (int j = 0; titlename[j] != '\0'; j++)
        {
            if (titlename[j] != title[j])
            {
                charMatches = false;
            }
        }
        if (charMatches == true)
            return true;
    }
    return false;
}

Library mostExpensiveBook(Library *books, int size)
{
    Library mostExpensive;
    float maxPrice = 0.0;
    for (int i = 0; i < size; i++)
    {
        if (books[i].getBookID() != 0 && books[i].getPrice() > maxPrice)
        {
            mostExpensive = books[i];
            maxPrice = books[i].getPrice();
        }
    }
    return mostExpensive;
}
int main()
{
    int numOfBooks = 0;
    do
    {
        cout << "Enter number of books:\t";
        cin >> numOfBooks;
    } while (numOfBooks > 10 || numOfBooks < 1);
    Library *books = new Library[numOfBooks];
    for (int i = 0; i < numOfBooks; i++)
    {
        char title[100];
        char author[100];
        int ID, quantity;
        float price;
        cout << "Enter book title: ";
        cin.ignore();
        cin.getline(title, 100);
        books[i].setBookTitle(title);
        cout << "Enter author: ";
        cin.getline(author, 100);
        books[i].setAuthor(author);
        cout << "Enter book ID: ";
        cin >> ID;
        books[i].setBookID(ID);
        cout << "Enter quantity: ";
        cin >> quantity;
        books[i].setQuantity(quantity);
        cout << "Enter price: ";
        cin >> price;
        books[i].setPrice(price);
    }
    int userID;
    cout << "Sorting books by Title...\n";
    SortByTitle(books, numOfBooks);
    for (int i = 0; i < numOfBooks; i++) {
    books[i].displayRecords();
    }
    cout << "Sorting books by Author...\n";
    SortByAuthor(books, numOfBooks);
    for (int i = 0; i < numOfBooks; i++) {
    books[i].displayRecords();
    }
    cout << "Sorting books by Price...\n";
    SortByPrice(books, numOfBooks);
    for (int i = 0; i < numOfBooks; i++) {
    books[i].displayRecords();
    }
    char title1[100];
    // cout << "Enter book title to search: \t";
    // cin.ignore();
    // cin.getline(title1, 100);
    // if (searchByTitle(books, title1))
    //     cout << "Book found." << endl;
    // else
    //     cout << "Book not found." << endl;
    Library mostExpensive = mostExpensiveBook(books, numOfBooks);
    cout << "Most expensive book is :\n";
    cout << "Title: " << mostExpensive.getBookTitle() << endl;
    cout << "Author: " << mostExpensive.getAuthor() << endl;
    cout << "Price: $" << mostExpensive.getPrice() << endl;
    cout << "Enter book ID to remove: ";
    cin >> userID;
    removeBook(books, userID);
    delete[] books;
    return 0;
}