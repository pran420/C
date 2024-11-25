#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

class SymbolInfo 
{
public:
    string name;
    string type;
    int scope;

    SymbolInfo() : name(""), type(""), scope(0) {}

    SymbolInfo(const string& name, const string& type, int scope)
        : name(name), type(type), scope(scope) {}

    void display() const {
        cout << "Name: " << name << ", Type: " << type << ", Scope: " << scope << endl;
    }
};

class SymbolTable {
private:
    unordered_map<string, SymbolInfo> table;

public:
    void insertSymbol(const string& name, const string& type, int scope) {
        if (table.find(name) == table.end()) {
            table.emplace(name, SymbolInfo(name, type, scope));
            cout << "Symbol '" << name << "' inserted successfully.\n";
        } else {
            cout << "Symbol '" << name << "' already exists in the table.\n";
        }
    }

    bool lookupSymbol(const string& name) const {
        return table.find(name) != table.end();
    }

    void displaySymbol(const string& name) const {
        auto it = table.find(name);
        if (it != table.end()) {
            it->second.display();
        } else {
            cout << "Symbol '" << name << "' not found in the table.\n";
        }
    }
    void deleteSymbol(const string& name) {
        if (table.erase(name)) {
            cout << "Symbol '" << name << "' deleted successfully.\n";
        } else {
            cout << "Symbol '" << name << "' not found in the table.\n";
        }
    }

    void displayAll() const {
        if (table.empty()) {
            cout << "Symbol table is empty.\n";
        } else {
            cout << "Symbol Table:\n";
            for (const auto& entry : table) {
                entry.second.display();
            }
        }
    }
};
int main() {
    SymbolTable symTable;
    int choice;

    do {
        cout << "\nSymbol Table Menu:\n";
        cout << "1. Insert Symbol\n";
        cout << "2. Lookup Symbol\n";
        cout << "3. Delete Symbol\n";
        cout << "4. Display All Symbols\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
           
            cin.clear();
          
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
        }

        switch (choice) {
            case 1: {
               
                string name, type;
                int scope;
                cout << "Enter symbol name: ";
                cin >> name;
                cout << "Enter symbol type: ";
                cin >> type;
                cout << "Enter symbol scope: ";
                cin >> scope;
                symTable.insertSymbol(name, type, scope);
                break;
            }
            case 2: {
                
                string name;
                cout << "Enter symbol name to lookup: ";
                cin >> name;
                if (symTable.lookupSymbol(name)) {
                    symTable.displaySymbol(name);
                } else {
                    cout << "Symbol '" << name << "' not found.\n";
                }
                break;
            }
            case 3: {
                
                string name;
                cout << "Enter symbol name to delete: ";
                cin >> name;
                symTable.deleteSymbol(name);
                break;
            }
            case 4: {
            
                symTable.displayAll();
                break;
            }
            case 5: {
               
                cout << "Exiting program.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
