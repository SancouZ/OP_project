#include <iostream>
#include <iomanip>
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
    BY_product_NAME,
    BY_product_COUNT,
    BY_DATE,
    BY_DISTRICT,
    BY_CHIEF_SURNAME,
};

product Add(vector<product>& product);
int GetCorrectValue();
size_t utf8_length(const string& str);
void printAligned(const string& str, size_t width);
void PrintTable(const vector<product>& products);
void FixStreamState();
bool SortByCriterion(const product &a, const product &b, SortCriterion criterion);
void SortVector(vector<product>& products);
void TypeOfSort(vector<product>& products, SortCriterion criterion);
void GetCorrectName(string &name, string object);
int getCorrectInputNumber(int begin, int end);


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
                PrintTable(products);
                break;
            case 3:
                SortVector(products);
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

int getCorrectInputNumber(int begin, int end){
    int n{};
    bool isNotOk{};
    do{
        isNotOk = false;
        if(((cin >> n).fail()) || (n < begin || n > end)){
            FixStreamState();
            cout << "Incorrect input! The number must be between " << begin << " and " << end << "!"<< endl;
            cout << "Try again!" << endl;
            isNotOk = true;  
        }
    }
    while (isNotOk);

    return n;
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


size_t utf8_length(const string& str) {
    size_t length = 0;
    for (size_t i = 0; i < str.length();) {
        unsigned char c = str[i];
        if ((c & 0x80) == 0) {
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            i += 4;
        } else {
            i += 1; // �������� ����, ������ ��������
        }
        length++;
    }
    return length;
}

// ������� ��� ������������ ������ �� �������� ������
void printAligned(const string& str, size_t width) {
    size_t len = utf8_length(str);
    cout << str;
    for (size_t i = 0; i < width - len; i++) {
        cout << ' ';
    }
}



//�������
void PrintTable(const vector<product>& products) {
    if (products.empty()) {
        cout << "Нет компаний для отображения. Таблица пуста." << endl;
        return;
    }

    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| № |     Компания      |       Мастерская    |       Название продукта | Кол-во | Дата выпуска  | Район          | Фамилия начальника |\n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";

    for (const auto& prod : products) {
        cout << "|" << left << setw(3) << prod.number << "|";
        printAligned(prod.company, 19);
        cout << "|";
        printAligned(prod.workshop, 21);
        cout << "|";
        printAligned(prod.productName, 25);
        cout << "|";
        string temp;
        temp = to_string(prod.productCount);
        printAligned(temp, 8);
        cout << "|" << setw(2) << prod.date.day << "." << setw(2) << prod.date.month << "."  << setw(4) << prod.date.year; 
        cout << "     |";
        printAligned(prod.districtOfCompany, 16);
        cout << "|";
        printAligned(prod.chiefSurname, 20);
        cout << "|";
        cout << "\n----------------------------------------------------------------------------------------------------------------------------------------\n";
    }
}


// Ввод данных
product Add(vector<product>& Product) {
    product product;
    
    cin.ignore();
    GetCorrectName(product.company, "name of the enterprise");
    

    GetCorrectName(product.workshop, "name of the workshop");
    

    GetCorrectName(product.productName, "name of the product");
    
    cout << "Enter the number of units in the batch: ";
    product.productCount = GetCorrectValue();
    
    cout << "Enter the day of product release: ";
    product.date.day = getCorrectInputNumber(1, 31);
    
    cout << "Enter the month of product release: ";
    product.date.month = getCorrectInputNumber(1, 12);

    cout << "Enter the year of product release: ";
    product.date.year = getCorrectInputNumber(1970, 2025);

    GetCorrectName(product.districtOfCompany, "district where the enterprise is located");
    

    GetCorrectName(product.chiefSurname, "surname of the workshop chief");
    
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
        case BY_product_NAME:
            return a.productName < b.productName;
        case BY_product_COUNT:
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
void SortCriterionMenu() {
    cout << "1 - Sort in ascending order" << endl;
    cout << "2 - Sort in descending order" << endl;
}
//Функция сортировки
void SortVector(vector<product>& products) {
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
                criterion = BY_product_NAME;
                break;
            case 5:
                criterion = BY_product_COUNT;
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
                cout << "Undefined command, it must be 1, 2, 3, 4, 5, 6, 7 or 8, try again!" << endl;
        }

        TypeOfSort(products, criterion);
        cout << "Sort complete!" << endl;
    } while (sortCommand);
}

//Выбор вида сортировки
void TypeOfSort(vector<product>& products, SortCriterion criterion) {
    int sortCriterionCommand;
    do {
        SortCriterionMenu();
        sortCriterionCommand = GetCorrectValue();
        switch (sortCriterionCommand) {
            case 1:
                sort(products.begin(), products.end(), [criterion](const product &a, const product &b) {
                    return SortByCriterion(a, b, criterion);
                });
                return ;
            case 2:
                sort(products.begin(), products.end(), [criterion](const product &a, const product &b) {
                    return !SortByCriterion(a, b, criterion);
                });
                return ;
            default:
                cout << "Undefined command, it must be 1 or 2, try again!" << endl;
        }
    } while (sortCriterionCommand);
}

//Проверка строк
void GetCorrectName(string &name, string object) {
    bool isNotOk{};
    string temp;

    do {
        isNotOk = false;
        cout << "Enter the " << object << ": ";
        cin >> temp;

        if (temp.length() > 20) {
            cout << "The name must be at most 20 characters long!" << endl;
            isNotOk = true;
            continue;
        }

        for (int i = 0; temp[i] != '\0'; i++) {
            if ((temp[i] >= ' ' && temp[i] <= '@') || (temp[i] >= '[' && temp[i] < 'a') || 
                (temp[i] >= '{' && temp[i] <= '~')){
                cout << "The name must contain only letters!" << endl;
                isNotOk = true;
                break;
            }
        }

        if (!isNotOk) {
            name = temp;
        }
    } while (isNotOk);
}