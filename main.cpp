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
    string company;
    string workshop;
    string productName;
    int productCount;
    date date;
    string districtOfCompany;
    string chiefSurname;
};

product Add();
int GetCorrectValue();
void FixStreamState();

//МЕНЮ
void PrintMenu();

int main() {
    setlocale(LC_ALL, "Russian");
    int command{};
    vector<product> products;
    do {
        PrintMenu();
        command = GetCorrectValue();
        switch (command) {
            case 1:
                products.push_back(Add());
                break;
            case 2:
                for(int i = 0; i < products.size(); i++) {
                    cout << products[i].company << endl;
                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                cout << "The program is over" << endl; break;
            default:
                cout << "Неизвестная команда" << endl;
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
            cout << "Неизвестная команда" << endl;
            cout << "Введите команду еще раз" << endl;
            isNotOk = true;
        }
    } while (isNotOk);

    return n;
}

// Ввод данных
product Add() {
    product product;
    
    cout << "Введите название предприятия: ";
    cin.ignore();
    getline(cin, product.company);
    
    cout << "Введите название цеха: ";
    getline(cin, product.workshop);
    
    cout << "Введите наименование продукции: ";
    getline(cin, product.productName);
    
    cout << "Введите количество единиц в партии: ";
    cin >> product.productCount;
    FixStreamState();
    
    cout << "Введите день выпуска продукции: ";
    cin >> product.date.day;
    FixStreamState();
    
    cout << "Введите месяц выпуска продукции: ";
    cin >> product.date.month;
    FixStreamState();
    
    cout << "Введите год выпуска продукции: ";
    cin >> product.date.year;
    FixStreamState();
    
    cout << "Введите район, в котором находится предприятие: ";
    getline(cin, product.districtOfCompany);
    
    cout << "Введите фамилию начальника цеха: ";
    getline(cin, product.chiefSurname);
    
    return product;
}

// Сортировка по дате
// bool compareByDate(const product &a, const product &b) {
//     if (a.date.year != b.date.year)
//         return a.date.year < b.date.year;
//     if (a.date.month != b.date.month)
//         return a.date.month < b.date.month;
//     return a.date.day < b.date.day;
// }

// Основное меню
void PrintMenu() {
    cout << "1 - Добавить продукцию" << endl;
    cout << "2 - Показать таблицу" << endl;

}
//