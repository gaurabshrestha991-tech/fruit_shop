#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Fruit {
public:
    string name;
    int quantity;
    double price;

    Fruit(string n, int q, double p) {
        name = n;
        quantity = q;
        price = p;
    }
};

class CartItem {
public:
    string name;
    int quantity;
    double price;

    CartItem(string n, int q, double p) {
        name = n;
        quantity = q;
        price = p;
    }
    double getTotal() {
        return quantity * price;
    }
};

void showFruits(vector<Fruit>& fruits) {
    cout << "\nAvailable Fruits\n";

    cout << left << setw(5) << "NO."
         << setw(15) << "Fruits"
         << setw(15) << "Available Qty"
         << setw(10) << "Price"
         << endl;

    for (int i = 0; i < fruits.size(); i++) {
        cout << setw(5) << i+1
             << setw(15) << fruits[i].name
             << setw(15) << fruits[i].quantity
             << "Rs. " << fixed << setprecision(2)
             << fruits[i].price << endl;
    }
}

void showCart(vector<CartItem>& cart) {
    if (cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }

    cout << "Your Cart\n";

    cout << left << setw(5) << "NO."
         << setw(15) << "Fruits"
         << setw(10) << "Quantity"
         << setw(12) << "Price"
         << setw(12) << "Total"
         << endl;

    double grandTotal = 0;

    for (int i = 0; i < cart.size(); i++) {
        double total = cart[i].getTotal();
        grandTotal += total;

        cout << left << setw(5) << i + 1
             << setw(15) << cart[i].name
             << setw(10) << cart[i].quantity
             << "Rs. " << setw(8) << fixed << setprecision(2)
             << cart[i].price
             << "Rs. " << total << endl;
    }
    cout << "Grand Total: Rs. " << fixed << setprecision(2)
         << grandTotal << endl;
}

void addToCart(vector<Fruit>& fruits, vector<CartItem>& cart) {
    showFruits(fruits);

    int choice;
    cout << "\nEnter fruits number to add to cart: ";
    cin >> choice;

    if (choice < 1 || choice > fruits.size()) {
        cout << "Invalid Input!\n";
        return;
    }

    int qty;
    cout << "Enter Quantity: ";
    cin >> qty;

    if (qty <= 0) {
        cout << "Invalid Quantity Input!\n";
        return;
    }

    if (qty > fruits[choice - 1].quantity) {
        cout << "Sorry Only "
             << fruits[choice - 1].quantity
             << " Units are available.\n";
        return;
    }

    for (int i = 0; i < cart.size(); i++) {
        if (cart[i].name == fruits[choice - 1].name) {
            cart[i].quantity += qty;
            fruits[choice - 1].quantity -= qty;

            cout << qty << " "
                 << fruits[choice - 1].name
                 << "(s) added to cart.\n";
            return;
        }
    }

    cart.push_back(
        CartItem (
            fruits[choice - 1].name,
            qty,
            fruits[choice - 1].price
        )
    );

    fruits[choice - 1].quantity -= qty;

    cout << qty << " "
         << fruits[choice - 1].name
         << "(S) added to cart.\n";
}

void removeFromCart(vector<Fruit>& fruits, vector<CartItem>& cart) {
    if (cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }

    showCart(cart);

    int choice;
    cout << "\nEnter cart item number to remove: ";
    cin >> choice;

    if (choice < 1 || choice > cart.size()) {
        cout << "Invalid item number!\n";
        return;
    }

    for (int i = 0; i < fruits.size(); i++) {
        if(fruits[i].name == cart[choice - 1].name) {
            fruits[i].quantity += cart[choice - 1].quantity;
            break;
        }
    }

    cout << cart[choice - 1].name
         << " remove from cart.\n";

    cart.erase(cart.begin() + (choice - 1));
}

void checkout(vector<CartItem>& cart) {
    if (cart.empty()) {
        cout << "\nYour cart is empty. Nothing to purchase.\n";
        return;
    }

    showCart(cart);

    char confirm;
    cout << "\nDo you want to purchase these items? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        double total = 0;

        for (int i = 0; i < cart.size(); i++) {
            total += cart[i].getTotal();
        }

        cout << "\nReceipt\n";

        for (int i = 0; i < cart.size(); i++) {
            cout << cart[i].name
                 << "x" << cart[i].quantity
                 << fixed << setprecision(2)
                 << cart[i].getTotal()
                 << endl;
        }

        cout << "Total Amount: Rs. "
             << fixed << setprecision(2)
             << total << endl;

        cout << "Thank You for shopping!\n";
        cart.clear();
    }

    else {
        cout << "Purchase cancelled.\n";
    }
}

int main () {
    vector<Fruit> fruits = {
        Fruit("Apple", 20, 150), Fruit("Banana", 30, 100), Fruit("Mango", 15, 200), Fruit("Orange", 25, 120), Fruit("Grapes", 10, 180), Fruit("Watermelon", 8, 300), Fruit("Pineapple", 12, 250)
    };

    vector<CartItem> cart;

    int choice;

    cout << "Welcome to the Fruit Shop\n";

    do {
        cout << "1. Show Fruits\n";
        cout << "2. Add Fruit to cart\n";
        cout << "3. View Cart\n";
        cout << "4. Remove Item from the Cart\n";
        cout << "5. CheckOut / purchase\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                showFruits(fruits);
                break;
            case 2:
                addToCart(fruits, cart);
                break;
            case 3:
                showCart(cart);
                break;
            case 4:
                removeFromCart(fruits, cart);
            case 5:
                checkout(cart);
                break;
            case 6:
                cout << "\nThank You for visiting our fruit shop!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

