#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

// Function to return category name based on choice
const char *categories(int choice) {
    switch (choice) {
        case 1: return "Electronics";
        case 2: return "Clothing";
        case 3: return "Furniture";
        case 4: return "Appliances";
        case 5: return "Sports & Outdoor";
        case 6: return "Toys & Games";
        default: return "Invalid Item";
    }
}

// Structure to store item information
struct Inventory {
   std::string name;
   std::string description;
   int category;
   char date[80]; // Stores the date of adding item
   int quantity;
   float price;
};

// Function to add an item to the inventory
void AddItem(vector<Inventory> &inventory) {
    Inventory newItem;
    cout << "Enter item details: " << endl;
    cout << "Name: ";
    cin >> newItem.name;
    cout << "Description: ";
    cin >> newItem.description;
    cout << "Category (1-6): ";
    cin >> newItem.category;
    cout << "Quantity: ";
    cin >> newItem.quantity;
    cout << "Price: ";
    cin >> newItem.price;

    // Get current time and format it
    std::time_t currentTime = std::time(nullptr);
    std::strftime(newItem.date, sizeof(newItem.date), "%d-%m-%Y", std::localtime(&currentTime));

    inventory.push_back(newItem);
    cout << "-------------------------------------------- Item added successfully! --------------------------------------" << endl;
}

// Function to delete an item from the inventory
void DeleteItem(vector<Inventory> &inventory) {
    string name;
    int deleteQuantity;

    cout << "Enter item name: ";
    cin >> name;

    bool found = false;

    transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (size_t i = 0; i < inventory.size(); i++) {
        string itemNameLower = inventory[i].name;
        transform(itemNameLower.begin(), itemNameLower.end(), itemNameLower.begin(), ::tolower);

        if (name == itemNameLower) {
            found = true;
            cout << endl;
            cout << "Enter Quantity to delete: ";
            cin >> deleteQuantity;
            
            if (deleteQuantity <= 0) {
                cout << "Invalid quantity. Please enter a positive value." << endl;
            } else if (deleteQuantity > inventory[i].quantity) {
                cout << "Quantity to delete exceeds available quantity. Available quantity: " << inventory[i].quantity << endl;
            } else {
                inventory[i].quantity -= deleteQuantity;

                if (inventory[i].quantity == 0) {
                    inventory.erase(inventory.begin() + i);
                    cout << "Item deleted successfully." << endl;
                } else {
                    cout << "Remaining quantity: " << inventory[i].quantity << endl;
                }
            }
            
            break;
        }
    }

    if (!found) {
        cout << "Item not found in the inventory." << endl;
    }
}

// Function to search for an item in the inventory
void SearchItem(vector<Inventory> &inventory) {
    string name;

    cout << "Enter item name: ";
    cin >> name;

    bool found = false;

    transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (size_t i = 0; i < inventory.size(); i++) {
        string itemNameLower = inventory[i].name;
        transform(itemNameLower.begin(), itemNameLower.end(), itemNameLower.begin(), ::tolower);

        if (name == itemNameLower) {
            found = true;
            cout << endl;
            cout << "Name: " << inventory[i].name << endl;
            cout << "Description: " << inventory[i].description << endl;
            cout << "Category: " << categories(inventory[i].category) << endl;
            cout << "Date: " << inventory[i].date << endl;
            cout << "Quantity: " << inventory[i].quantity << endl;
            cout << "Price: Rs" << inventory[i].price << endl;
            break;
        }
    }

    if (!found) {
        cout << "Item not found in the inventory." << endl;
    }
}

// Function to generate reports of the inventory
void GenerateReports(const vector<Inventory> &inventory) {
    cout<< endl;
    
    cout << "Report 1: List of all items in the inventory" << endl;
    for (const Inventory &item : inventory) {
        cout << "Name: " << item.name << ", Description: " << item.description << ", Category: " << categories(item.category) << ", Quantity: " << item.quantity << ", Price: Rs" << item.price << endl;
    }
    cout << endl;

    cout << "Report 2: Total value of inventory" << endl;
    double totalValue = 0;
    for (const Inventory &item : inventory) {
        totalValue += item.quantity * item.price;
    }
    cout << "Total value of inventory: Rs" << totalValue << endl;
    cout << endl;
}

int main() {
    vector<Inventory> inventory;
    int choice;

    do {
        cout << endl;
        cout << "=========================================== Welcome to Inventory Management System! ===========================================" << endl;
        cout << "1. Add New Item" << endl;
        cout << "2. Delete Item" << endl;
        cout << "3. Search Item" << endl;
        cout << "4. Generate Reports" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                AddItem(inventory);
                break;

            case 2:
                DeleteItem(inventory);
                break;

            case 3:
                SearchItem(inventory);
                break;

            case 4:
                GenerateReports(inventory);
                break;

            case 5:
                cout << "Exiting the Inventory Management System. Thank you for using!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while(choice != 5);

    return 0;
}
