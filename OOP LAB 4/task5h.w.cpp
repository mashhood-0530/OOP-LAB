#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
class MenuItem
{
    string itemname;
    string type;
    double price;
    public:
    string GetItemName()
    {
        return itemname;
    }
    double GetPrice()
    {
        return price;
    }
    string GetType()
    {
        return type;
    }
    MenuItem(string name,string type,double price)
    {
        itemname=name;
        this->price=price;
        this->type=type;
    }
};
class CoffeeShop
{
    string name;
    vector<MenuItem> items;
    vector<string> orders;
    public:
    CoffeeShop(string shopName) : name(shopName){
        items.push_back(MenuItem("Espresso", "drink", 2.50));
        items.push_back(MenuItem("Cappuccino", "drink", 3.00));
        items.push_back(MenuItem("Muffin", "food", 2.00));
        items.push_back(MenuItem("Croissant", "food", 2.50));
        items.push_back(MenuItem("Latte", "drink", 3.50));
    }
    void add_Order(string order)
    {
        bool found=false;
        for(int i=0;i<items.size();i++)
        {
            if (strcasecmp(order.c_str(), items[i].GetItemName().c_str()) == 0)
            {
                orders.push_back(order);
                cout<<order<<" added succesfully!"<<endl;
                found=true;
                break;   
            }
        }
        if(!found)
        cout<<"This item is currently unavailable"<<endl;      
    }
    void fulfill_order()
    {
        if(!orders.empty())
        {
            string item=orders.front();
            orders.erase(orders.begin());
            cout<<"The "+item+" is ready!"<<endl;
        }
        else
        {
            cout<<"All orders have been fulfilled"<<endl;
        }
    }
    vector<string> List_Items()
    {
        return orders;   
    }
    double dueAmount()
    {
        double due=0;
        if(!orders.empty())
        {
            for(int i=0;i<orders.size();i++)
            {
                for(int j=0;j<items.size();j++)
                {
                    if(strcasecmp(orders[i].c_str(),items[j].GetItemName().c_str())==0)
                    {
                        due+=items[j].GetPrice();
                    }
                }
            }
        }
        return due;
    }
    string cheapestItem()
    {
        double min=items[0].GetPrice();
        int index;
        for(int j=1;j<items.size();j++)
        {
            if(items[j].GetPrice()<min)
            {
                min=items[j].GetPrice();
                index=j;
            }
        }
        return items[index].GetItemName();
    }
    vector<string> drinksOnly()
    {
        vector<string> drinks;
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].GetType() == "drink")
            {
                drinks.push_back(items[i].GetItemName());
            }
        }
        return drinks;
    }
    vector<string> foodOnly()
    {
        vector<string> food;
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].GetType() == "food")
            {
                food.push_back(items[i].GetItemName());
            }
        }
        return food;
    }
};
int main()
{
    CoffeeShop shop("Cafe Java");
    int choice;

    while (true)
    {
        cout << "\nCoffee Shop Menu:" << endl;
        cout << "1. Add an Order" << endl;
        cout << "2. Fulfill an Order" << endl;
        cout << "3. List All Orders" << endl;
        cout << "4. Check Due Amount" << endl;
        cout << "5. Find Cheapest Item" << endl;
        cout << "6. Show Drinks Only" << endl;
        cout << "7. Show Food Only" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        string order;

        switch (choice)
        {
        case 1:
            cout << "Enter the item to order: ";
            getline(cin, order);
            shop.add_Order(order);
            break;

        case 2:
            shop.fulfill_order();
            break;

        case 3:
            {
                vector<string> orders = shop.List_Items();
                if (orders.empty())
                    cout << "No orders placed yet." << endl;
                else
                {
                    cout << "Current Orders: " << endl;
                    for (const string &o : orders)
                    {
                        cout << o << endl;
                    }
                }
            }
            break;

        case 4:
            cout << "Total Due Amount: $" << shop.dueAmount() << endl;
            break;

        case 5:
            cout << "Cheapest Item: " << shop.cheapestItem() << endl;
            break;

        case 6:
            {
                vector<string> drinks = shop.drinksOnly();
                if (drinks.empty())
                    cout << "No drinks available." << endl;
                else
                {
                    cout << "Drinks available: " << endl;
                    for (const string &drink : drinks)
                    {
                        cout << drink << endl;
                    }
                }
            }
            break;

        case 7:
            {
                vector<string> food = shop.foodOnly();
                if (food.empty())
                    cout << "No food available." << endl;
                else
                {
                    cout << "Food available: " << endl;
                    for (const string &item : food)
                    {
                        cout << item << endl;
                    }
                }
            }
            break;

        case 8:
            cout << "Exiting the system. Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice, please try again!" << endl;
        }
    }

    return 0;
}