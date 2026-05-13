// Aleena Zahra 23i-2514 BDS-B OOP Assignment 3
#include <iostream>
using namespace std;

class Product
{
    int ID;
    char *name;
    float price;
    int quantity;

public:
    Product(int productID, char *productName, float productPrice, int productQuantity)
    {
        ID = productID;
        name = productName;
        price = productPrice;
        quantity = productQuantity;
    }
    void setName(char *productName)
    {
        name = productName;
    }
    void setID(int productID)
    {
        ID = productID;
    }
    void setPrice(float productPrice)
    {
        price = productPrice;
    }
    void setQuantity(int productQuantity)
    {
        quantity = productQuantity;
    }
    char *getName()
    {
        return name;
    }
    int getID()
    {
        return ID;
    }
    float getPrice()
    {
        return price;
    }
    int getQuantity()
    {
        return quantity;
    }
};
class Inventory
{
private:
    Product *products;
    int count;
    int size;
    void add_product(int productID, char *productName, float productPrice, int productQuantity)
    {
        
        products[productID].setName(productName);
        products[productID].setPrice(productPrice);
        products[productID].setQuantity(productQuantity);
    }

    // a function to remove a product from the inventory based on its unique identifier.
    void remove_product(int id) {}
    // a function to remove one or more products from the inventory based on the name.
    void remove_product(char *name) {}

    // a function to remove a specified quantity of products based on their ID from the inventory.
    void remove_product(int id, int count) {}
    // a function to update the quantity of a product in the inventory based on its ID.
    // Quantity_change can be positive or negative to add or subtract from the existing quantity.
    void update_quantity(int id, int quantity_change)
    {
        products[id].setQuantity(quantity_change);
    }
    Product get_product(int id) {
        return products[id];
    }
    // a function to retrieve (ID, name, price, quantity) based on the specified ID.
    float calculate_inventory_value()
    {
        int sum = 0.0;
        for (int i = 0; i < count; i++)
        {
            sum += products[i].getPrice();
        }
        return sum;
    }
    void display() {
        for (int i = 0; i < count; i++)
        {
            cout<<"PRODUCT NUMBER "<<products[i].getID();
            cout<<"THE NAME OF PRODUCT IS "<<products[i].getName()<<endl;
            cout<<"THE PRICE IS "<<products[i].getPrice()<<endl;
            cout<<"THE QUANTITY IS "<<products[i].getQuantity()<<endl;
        }
    }
    // name, price, and quantity.
};
static int ID = 0;
int main()
{
    

    return 0;
}