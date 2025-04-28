#include <iostream>
#include <fstream>
using namespace std;

struct User {
    string user_id, first_name, last_name, address, email;
};

struct Product {
    string product_id, product_name, description;
    int price;
};

struct Order {
    string order_id, user_id, product_id;
    int total_paid;
};

// Limits (static array sizes)
const int MAX_USERS = 100;
const int MAX_PRODUCTS = 100;
const int MAX_ORDERS = 100;

// Function to split line manually
void splitLine(const string& line, string parts[], int expectedParts) {
    int pos = 0, next, idx = 0;
    while (idx < expectedParts - 1) {
        next = line.find(' ', pos);
        parts[idx++] = line.substr(pos, next - pos);
        pos = next + 1;
    }
    parts[idx] = line.substr(pos); // last part
}

int readUsers(const string& filename, User* users) {
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line) && count < MAX_USERS) {
        string parts[5];
        splitLine(line, parts, 5);
        users[count] = { parts[0], parts[1], parts[2], parts[3], parts[4] };
        count++;
    }
    file.close();
    return count;
}

int readProducts(const string& filename, Product* products) {
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line) && count < MAX_PRODUCTS) {
        string parts[4];
        splitLine(line, parts, 4);
        products[count] = { parts[0], parts[1], parts[2], stoi(parts[3]) };
        count++;
    }
    file.close();
    return count;
}

int readOrders(const string& filename, Order* orders) {
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line) && count < MAX_ORDERS) {
        string parts[4];
        splitLine(line, parts, 4);
        orders[count] = { parts[0], parts[1], parts[2], stoi(parts[3]) };
        count++;
    }
    file.close();
    return count;
}

void dummyData() {
    ofstream u("users.txt"), p("products.txt"), o("orders.txt");

    u << "U1 Linus Torvalds Finland linus@linux.org\n";
    u << "U2 Ada Lovelace UK ada@computers.com\n";
    u.close();

    p << "P1 Laptop High-end_Laptop 1500\n";
    p << "P2 Smartphone Flagship_Phone 1200\n";
    p.close();

    o << "O1 U1 P1 1500\n";
    o << "O2 U2 P2 1200\n";
    o.close();
}

void findProductsByUser(const string& username) {
    User users[MAX_USERS];
    Product products[MAX_PRODUCTS];
    Order orders[MAX_ORDERS];

    int userCount = readUsers("users.txt", users);
    int productCount = readProducts("products.txt", products);
    int orderCount = readOrders("orders.txt", orders);

    string target_user_id = "";

    // Find user_id for given username
    for (User* u = users; u < users + userCount; u++) {
        if (u->first_name == username) {
            target_user_id = u->user_id;
            break;
        }
    }

    if (target_user_id == "") {
        cout << "User not found.\n";
        return;
    }

    cout << "Products ordered by " << username << ":\n";

    // Find orders
    for (Order* o = orders; o < orders + orderCount; o++) {
        if (o->user_id == target_user_id) {
            // Find product by ID
            for (Product* p = products; p < products + productCount; p++) {
                if (p->product_id == o->product_id) {
                    cout << "- " << p->product_name << endl;
                    break;
                }
            }
        }
    }
}

int main() {
    dummyData(); // Step 1: Write dummy data
    findProductsByUser("Linus"); // Step 2: Query products for Linus
    return 0;
}
