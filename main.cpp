#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>


using namespace std;

int GetCorrectValue();
void FixStreamState();

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


int main() {
    int command{};
    do {
        command = GetCorrectValue();
        switch (command) {
            case 1:
                break;
            case 2:
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

// СОРТИРОВКА ПО ДАТЕ
bool compareByDate(const product &a, const product &b) {
    if (a.date.year != b.date.year)
        return a.date.year < b.date.year;
    if (a.date.month != b.date.month)
        return a.date.month < b.date.month;
    return a.date.day < b.date.day;
}