#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Medicine {
private:
    string name;
    string expirationDate;
    double price;

public:
    Medicine(string n, string exp, double p) : name(n), expirationDate(exp), price(p) {}

    string getName() const { return name; }
    string getExpirationDate() const { return expirationDate; }
    double getPrice() const { return price; }
};

class Pharmacy {
private:
    vector<Medicine> coughMedicines;
    vector<Medicine> feverMedicines;
    vector<Medicine> coldMedicines;
    vector<Medicine> stomachAcheMedicines;
    vector<Medicine> headacheMedicines;

public:
    Pharmacy() {
        // Pre-defined medicines categorized by type
        coughMedicines.push_back(Medicine("Dextromethorphan", "07/2023", 4.50));
        coughMedicines.push_back(Medicine("Guaifenesin", "09/2024", 3.25));

        feverMedicines.push_back(Medicine("Paracetamol", "12/2024", 5.99));
        feverMedicines.push_back(Medicine("Ibuprofen", "11/2023", 3.75));

        coldMedicines.push_back(Medicine("Loratadine", "10/2024", 3.75));
        coldMedicines.push_back(Medicine("Phenylephrine", "08/2023", 8.50));

        stomachAcheMedicines.push_back(Medicine("Loperamide", "09/2024", 8.50));
        stomachAcheMedicines.push_back(Medicine("Ranitidine", "07/2023", 6.25));

        headacheMedicines.push_back(Medicine("Acetylsalicylic Acid", "12/2023", 5.75));
        headacheMedicines.push_back(Medicine("Mefenamic Acid", "08/2024", 6.99));
    }

    void addMedicine(const string& type, const string& name, const string& expDate, double price) {
        Medicine med(name, expDate, price);
        if (type == "cough") {
            coughMedicines.push_back(med);
            sortInventory(coughMedicines);
        } else if (type == "fever") {
            feverMedicines.push_back(med);
            sortInventory(feverMedicines);
        } else if (type == "cold") {
            coldMedicines.push_back(med);
            sortInventory(coldMedicines);
        } else if (type == "stomach ache") {
            stomachAcheMedicines.push_back(med);
            sortInventory(stomachAcheMedicines);
        } else if (type == "headache") {
            headacheMedicines.push_back(med);
            sortInventory(headacheMedicines);
        } else {
            cout << "Invalid medicine type." << endl;
        }
    }

    void sortInventory(vector<Medicine>& inventory) {
        sort(inventory.begin(), inventory.end(), [](const Medicine& a, const Medicine& b) {
            return a.getName() < b.getName();
        });
    }

    void searchMedicine(const string& type, const string& name) {
        vector<Medicine>* inventory = getInventoryByType(type);
        if (!inventory) return;

        bool found = false;
        cout << "Medicine(s) found:" << endl;
        for (const auto& med : *inventory) {
            if (med.getName() == name) {
                cout << "Name: " << med.getName() << ", Expiration Date: " << med.getExpirationDate() << ", Price: $" << fixed << setprecision(2) << med.getPrice() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Medicine not found!" << endl;
        }
    }

    void displayMedicines(const string& type) {
        vector<Medicine>* inventory = getInventoryByType(type);
        if (!inventory) return;

        cout << "Medicine Inventory (" << type << "):" << endl;
        for (const auto& med : *inventory) {
            cout << "Name: " << med.getName() << ", Expiration Date: " << med.getExpirationDate() << ", Price: $" << fixed << setprecision(2) << med.getPrice() << endl;
        }
    }

private:
    vector<Medicine>* getInventoryByType(const string& type) {
        if (type == "cough") {
            return &coughMedicines;
        } else if (type == "fever") {
            return &feverMedicines;
        } else if (type == "cold") {
            return &coldMedicines;
        } else if (type == "stomach ache") {
            return &stomachAcheMedicines;
        } else if (type == "headache") {
            return &headacheMedicines;
        } else {
            cout << "Invalid medicine type." << endl;
            return nullptr;
        }
    }
};

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    Pharmacy chuchusPharmacy;
    int choice;
    string type, name, expDate;
    double price;

    do {
        cout << "\nChuchu's Pharmacy Menu:" << endl;
        cout << "1. Add Medicine" << endl;
        cout << "2. Search For Medicine" << endl;
        cout << "3. Display Medicines" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter the type of medicine (cough, fever, cold, stomach ache, headache): ";
                cin >> type;
                cout << "Enter the number of medicines to add: ";
                int numMedicines;
                cin >> numMedicines;
                for (int i = 0; i < numMedicines; ++i) {
                    cout << "Medicine " << i + 1 << ":" << endl;
                    cout << "Enter medicine name: ";
                    cin >> name;
                    cout << "Enter expiration date (MM/YYYY): ";
                    cin >> expDate;
                    cout << "Enter price: $";
                    cin >> price;
                    chuchusPharmacy.addMedicine(type, name, expDate, price);
                }
                cout << "Medicines added successfully!" << endl;
                break;
            }
            case 2: {
                cout << "Enter the type of medicine (cough, fever, cold, stomach ache, headache): ";
                cin >> type;
                cout << "Enter medicine name to search: ";
                cin >> name;
                chuchusPharmacy.searchMedicine(type, name);
                break;
            }
            case 3: {
                cout << "Enter the type of medicine to display (cough, fever, cold, stomach ache, headache): ";
                cin >> type;
                chuchusPharmacy.displayMedicines(type);
                break;
            }
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}
    
