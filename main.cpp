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

//����
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
                cout << "����������� �������" << endl;
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
            cout << "����������� �������" << endl;
            cout << "������� ������� ��� ���" << endl;
            isNotOk = true;
        }
    } while (isNotOk);

    return n;
}

// ���� ������
product Add() {
    product product;
    
    cout << "������� �������� �����������: ";
    cin.ignore();
    getline(cin, product.company);
    
    cout << "������� �������� ����: ";
    getline(cin, product.workshop);
    
    cout << "������� ������������ ���������: ";
    getline(cin, product.productName);
    
    cout << "������� ���������� ������ � ������: ";
    cin >> product.productCount;
    FixStreamState();
    
    cout << "������� ���� ������� ���������: ";
    cin >> product.date.day;
    FixStreamState();
    
    cout << "������� ����� ������� ���������: ";
    cin >> product.date.month;
    FixStreamState();
    
    cout << "������� ��� ������� ���������: ";
    cin >> product.date.year;
    FixStreamState();
    
    cout << "������� �����, � ������� ��������� �����������: ";
    getline(cin, product.districtOfCompany);
    
    cout << "������� ������� ���������� ����: ";
    getline(cin, product.chiefSurname);
    
    return product;
}

// ���������� �� ����
// bool compareByDate(const product &a, const product &b) {
//     if (a.date.year != b.date.year)
//         return a.date.year < b.date.year;
//     if (a.date.month != b.date.month)
//         return a.date.month < b.date.month;
//     return a.date.day < b.date.day;
// }

// �������� ����
void PrintMenu() {
    cout << "1 - �������� ���������" << endl;
    cout << "2 - �������� �������" << endl;

}
//