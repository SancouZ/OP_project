#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <locale>

using namespace std;

struct date{
    int day;
    int month;
    int year;
};

struct product{
    int number;
    string company;
    string workshop;
    string productName;
    int productCount;
    date date;
    string districtOfCompany;
    string chiefSurname;
};

enum SortCriterion {
    BY_NUMBER,
    BY_COMPANY,
    BY_WORKSHOP,
    BY_PRODUCT_NAME,
    BY_PRODUCT_COUNT,
    BY_DATE,
    BY_DISTRICT,
    BY_CHIEF_SURNAME,
};


product Add(vector<product>& Product);
int GetCorrectValue();
void FixStreamState();
bool SortByCriterion(const product &a, const product &b, SortCriterion criterion);
void Sorted(vector<product>& products);

//МЕНЮ
void PrintMenu();
void SortMenu();
int main() {
    setlocale(LC_ALL, "Russian");
    int command{};
    vector<product> products;
    do {
        PrintMenu();
        command = GetCorrectValue();
        switch (command) {
            case 1:
                products.push_back(Add(products));
                break;
            case 2:
                for (const auto& p : products) {
                    cout << p.company << endl;

                }
                break;
            case 3:
                Sorted(products);
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                cout << "The program is over" << endl; break;
            default:
                cout << "Undefined command" << endl;
        }
    } while (command);
    return 0;
}

void FixStreamState() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int GetCorrectValue() {
    int n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail()) {
            FixStreamState();
            cout << "Undefined command" << endl;
            cout << "Enter command again" << endl;
            isNotOk = true;
        }
    } while (isNotOk);

    return n;
}

// Ввод данных
product Add(vector<product>& Product) {
    product product;
    
    cout << "Enter the name of the enterprise: ";
    cin.ignore();
    getline(cin, product.company);
    
    cout << "Enter the name of the workshop: ";
    getline(cin, product.workshop);
    
    cout << "Enter the name of the product: ";
    getline(cin, product.productName);
    
    cout << "Enter the number of units in the batch: ";
    cin >> product.productCount;
    FixStreamState();
    
    cout << "Enter the day of product release: ";
    cin >> product.date.day;
    FixStreamState();
    
    cout << "Enter the month of product release: ";
    cin >> product.date.month;
    FixStreamState();
    
    cout << "Enter the year of product release: ";
    cin >> product.date.year;
    FixStreamState();
    
    cout << "Enter the district where the enterprise is located: ";
    getline(cin, product.districtOfCompany);
    
    cout << "Enter the surname of the workshop chief: ";
    getline(cin, product.chiefSurname);
    
    product.number = Product.size() + 1;
    return product;
}

// Критерий соортировки
bool SortByCriterion(const product &a, const product &b, SortCriterion criterion) {
    switch (criterion) {
        case BY_NUMBER:
            return a.number < b.number;
        case BY_COMPANY:
            return a.company < b.company;
        case BY_WORKSHOP:
            return a.workshop < b.workshop;
        case BY_PRODUCT_NAME:
            return a.productName < b.productName;
        case BY_PRODUCT_COUNT:
            return a.productCount < b.productCount;
        case BY_DATE:
            if (a.date.year != b.date.year)
                return a.date.year < b.date.year;
            if (a.date.month != b.date.month)
                return a.date.month < b.date.month;
            return a.date.day < b.date.day;
        case BY_DISTRICT:
            return a.districtOfCompany < b.districtOfCompany;
        case BY_CHIEF_SURNAME:
            return a.chiefSurname < b.chiefSurname;
        default:
            return false; 
    }
}

// Основное меню
void PrintMenu() {
    cout << "1 - Add product" << endl;
    cout << "2 - Show table" << endl;
    cout << "3 - Sort" << endl;
}

//Меню сортировки
void SortMenu() {
    cout << "1 - Sort by number" << endl;
    cout << "2 - Sort by company" << endl;
    cout << "3 - Sort by worshop" << endl;
    cout << "4 - Sort by product name" << endl;
    cout << "5 - Sort by product count" << endl;
    cout << "6 - Sort by date" << endl;
    cout << "7 - Sort by district" << endl;
    cout << "8 - Sort by chief surname" << endl;
    cout << "0 - Exit" << endl;
}
//Функция сортировки
void Sorted(vector<product>& products) {
    int sortCommand{};
    do {
        SortMenu();
        sortCommand = GetCorrectValue();
        SortCriterion criterion;

        switch (sortCommand) {
            case 1:
                criterion = BY_NUMBER;
                break;
            case 2:
                criterion = BY_COMPANY;
                break;
            case 3:
                criterion = BY_WORKSHOP;
                break;
            case 4:
                criterion = BY_PRODUCT_NAME;
                break;
            case 5:
                criterion = BY_PRODUCT_COUNT;
                break;
            case 6:
                criterion = BY_DATE;
                break;
            case 7:
                criterion = BY_DISTRICT;
                break;
            case 8:
                criterion = BY_CHIEF_SURNAME;
                break;
            case 0:
                return;
            default:
                cout << "Undefined command" << endl;
                continue;
        }
        sort(products.begin(), products.end(), [criterion](const product &a, const product &b) {
            return SortByCriterion(a, b, criterion);
        });

        cout << "Sort complete!" << endl;

    } while (sortCommand);
}