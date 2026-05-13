// Aleena Zahra 23i-2514 DS-B OOP Assignment 3
#include <iostream>
using namespace std;

class Product
{
    int id;
    string name;
    float price;
    int quantity;

public:
    Product(int id = 0, string name = "\0", float price = 0, int quantity = 0) : id(id), name(name), price(price), quantity(quantity) {}
    int getID() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }
    float getPrice() const
    {
        return price;
    }
    int getQuantity() const
    {
        return quantity;
    }
    void setID(int newID)
    {
        id = newID;
    }
    void setName(char *ch)
    {
        name = ch;
    }
    void setPrice(float newPrice)
    {
        price = newPrice;
    }
    void setQuantity(int newQuantity)
    {
        quantity = newQuantity;
    }
};

class Inventory
{
    Product *products;
    int count, size;

public:
    Inventory(int max = 10) : products(new Product[max]), count(0), size(max) {}
    void add_product(int id, string name, float price, int quantity)
    {
        if (count < size)
        {
            Product pr(id, name, price, quantity);
            int i = 0;
            while (products[i].getName() != "\0")
                i++;
            products[i] = pr;
            count++;
            cout << "Product added to inventory.\n\n";
        }
        else
            cout << "Max limit reached!\n";
    }
    void add_product(Product *product)
    {
        if (count < size)
        {
            int i = 0;
            while (products[i].getName() != "\0")
                i++;
            products[i] = *product;
            count++;
            cout << "Product added to inventory.\n\n";
        }
        else
            cout << "Max limit reached!\n";
    }
    void update_quantity(int id, int quantity_change)
    {
        for (int i = 0; i < size; i++)
        {
            if (products[i].getID() == id)
            {
                products[i].setQuantity(products[i].getQuantity() + quantity_change);
                break;
            }
            else if (i == size - 1)
                cout << "Product ID " << id << " not found!\n";
        }
    }
    Product &get_product(int id)
    {
        for (int i = 0; i < size; i++)
        {
            if (products[i].getID() == id)
            {
                return products[i];
            }
            else if (i == size - 1)
                cout << "Product ID " << id << " not found!\n";
        }
    }
    float calculate_inventory_value()
    {
        float total = 0;
        for (int i = 0; i < size; i++)
        {
            total += products[i].getPrice() * products[i].getQuantity();
        }
        return total;
    }
    void display()
    {
        cout << "\t\t\tINVENTORY DETAILS\n";
        cout << "---------------------------------------------------------------------\n\n";

        for (int i = 0; i < size; i++)
        {
            cout << "Product ID: " << products[i].getID() << endl;
            cout << "Product Name: " << products[i].getName() << endl;
            cout << "Price: " << products[i].getPrice() << endl;
            cout << "Quantity: " << products[i].getQuantity() << endl;
            cout << "---------------------------------------------------------------------\n\n";
        }
        cout << "Total value: " << calculate_inventory_value() << endl
             << endl;
    }
    ~Inventory()
    {
        delete[] products;
    }
    void remove_product(string name)
    {
        for (int i = 0; i < size; i++)
        {
            if (products[i].getName() == name)
            {
                Product *pr = new Product;
                products[i] = *pr;
                cout << endl << name << " removed.";
                count--;
                break;
            }
            else if (i == size - 1)
                cout << endl << name << " not found.";
        }
    }
    void remove_product(int id)
    {
        for (int i = 0; i < size; i++)
        {
            if (products[i].getID() == id)
            {
                Product *pr = new Product;
                products[i] = *pr;
                cout << "\nProduct " << id << " removed.";
                count--;
                break;
            }
            else if (i == size - 1)
                cout << "\nProduct " << id << " not found.";
        }
    }
    void remove_product(int id, int count)
    {
        for (int i = 0; i < size; i++)
        {
            if (products[i].getID() == id)
            {
                if (count > products[i].getQuantity())
                    count = products[i].getQuantity();
                products[i].setQuantity(products[i].getQuantity() - count);
                cout << endl << count << "units of product " << id << " removed.";
                count--;
                break;
            }
            else if (i == size - 1)
                cout << "\nProduct " << id << " not found.";
        }
    }
};

int main()
{
    Inventory inv(3);
    string s1, s2, s3;
    int id1, id2, id3;
    float p1, p2, p3;

    cout << "Enter name of product 1: ";
    cin >> s1;
    cout << "Enter ID of product 1: ";
    cin >> id1;
    cout << "Enter price of product 1: ";
    cin >> p1;
    Product pr1(id1, s1, p1, 10);
    inv.add_product(&pr1);

    cout << "Enter name of product 2: ";
    cin >> s2;
    cout << "Enter ID of product 2: ";
    cin >> id2;
    cout << "Enter price of product 2: ";
    cin >> p2;
    inv.add_product(id2, s2, p2, 10);

    cout << "Enter name of product 3: ";
    cin >> s3;
    cout << "Enter ID of product 3: ";
    cin >> id3;
    cout << "Enter price of product 3: ";
    cin >> p3;
    inv.add_product(id3, s3, p3, 10);

    inv.display();

    cout << "Removing products....\n";
    inv.remove_product(id3);
    inv.remove_product(id2);
    inv.remove_product(s1);
    cout << endl;

    return 0;
}