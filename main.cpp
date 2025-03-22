#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <locale>
#include <unordered_map>

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

//����� �������
size_t utf8Length(const string& str);
void printAligned(const string& str, size_t width);
void printTable(const vector<product>& products);

//����������
bool sortByCriterion(const product &a, const product &b, SortCriterion criterion);
void sortVector(vector<product>& products);
void typeOfSort(vector<product>& products, SortCriterion criterion);

//��������� ������ ��� �����
void getCorrectName(string &name, string object);
int getCorrectInputNumber(int begin, int end);
void fixStreamState();
int getCorrectValue();

//������ � �������
void actionsData(vector<product>& products);
product addData(vector<product>& product);
void editData(vector<product>& products);
void deleteData(vector<product>& products);

//������ � ���������� �������
void txtData(vector<product>& products);
void readingDataFromTxt(vector<product>& products);
void addToTxt(vector<product>& products);

//�������������� �������
void businessesInTheArea(const vector<product>& products);
void theCommonSurname(const vector<product>& products);
void listOfWorkshops(const vector<product>& products);
void companyProducingProducts(const vector<product>& products);
void requests(vector<product>& products);

//����
void printMenu();
void actionsDataMenu();
void sortMenu();
void sortCriterionMenu();
void txtMenu();
void requestsMenu();


int main() {
    setlocale(LC_ALL, "Russian");
    int command{};
    vector<product> products;
    do {
        printMenu();
        command = getCorrectValue();
        switch (command) {
            case 1:
                actionsData(products);
                break;
            case 2:
                printTable(products);
                break;
            case 3:
                sortVector(products);
                break;
            case 4:
                txtData(products);
                break;
            case 5:
                requests(products);
                break;
            case 0:
                cout << "��������� ���������!" << endl; 
                break;
            default:
                cout << "����������� �������!" << endl;
        }
    } while (command);
    return 0;
}

void fixStreamState() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getCorrectValue() {
    int n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail()) {
            fixStreamState();
            cout << "����������� �������!" << endl;
            cout << "���������� �����!" << endl;
            isNotOk = true;
        }
    } while (isNotOk);

    return n;
}


size_t utf8Length(const string& str) {
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
            i += 1;
        }
        length++;
    }
    return length;
}

// �������
void printAligned(const string& str, size_t width) {
    size_t len = utf8Length(str);
    cout << str;
    for (size_t i = 0; i < width - len; i++) {
        cout << ' ';
    }
}



//����� �������
void printTable(const vector<product>& products) {
    if (products.empty()) {
        cout << "��� ������ ��� �����������. ������� �����." << endl;
        return;
    }

    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| � |    ����������     |       ���           |   �������� ��������     | ���-�� | ���� �������  |      �����     | ������� ���������� |\n";
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


// ���� ������
product addData(vector<product>& Product) {
    product product;
    
    cin.ignore();
    getCorrectName(product.company, "�������� �����������");
    

    getCorrectName(product.workshop, "�������� ����");
    

    getCorrectName(product.productName, "�������� ��������");
    
    cout << "������� ����������� ������ � ������: ";
    product.productCount = getCorrectValue();
    
    cout << "������� ���� ������� ��������: ";
    product.date.day = getCorrectInputNumber(1, 31);
    
    cout << "������� ����� ������� ��������: ";
    product.date.month = getCorrectInputNumber(1, 12);

    cout << "������� ��� ������� �������� ";
    product.date.year = getCorrectInputNumber(1970, 2025);

    getCorrectName(product.districtOfCompany, "�����, � ������� ����������� �����������");
    

    getCorrectName(product.chiefSurname, "������� ���������� ����");
    
    product.number = Product.size() + 1;
    return product;
}

void actionsData(vector<product>& products) {
    int actionsDataCommand{};
    do {
        actionsDataMenu();
        actionsDataCommand = getCorrectValue();

        switch (actionsDataCommand) {
            case 1:
                products.push_back(addData(products));
                break;
            case 2:
                editData(products);
                break;
            case 3:
                deleteData(products);
                break;
            case 0:
                return;
            default:
                cout << "����������� �������, �������� ����� ���� 1-3. ��������� �������!" << endl;
        }
    } while (actionsDataCommand);
}


// �������� �����������
bool sortByCriterion(const product &a, const product &b, SortCriterion criterion) {
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

// �������� ����
void printMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - �������� � �������                             |" << endl;
    cout << "| 2 - �������� �������                               |" << endl;
    cout << "| 3 - ����������                                     |" << endl;
    cout << "| 4 - ������ � ���������� �������                    |" << endl;
    cout << "| 5 - �������������� ����������                      |" << endl;
    cout << "| 0 - �����                                          |" << endl;
    cout << "======================================================" << endl;
}

void actionsDataMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - �������� �����������                           |" << endl;
    cout << "| 2 - �������� ������� ����������                    |" << endl;
    cout << "| 3 - ������� ������                                 |" << endl;
    cout << "| 0 - �����                                          |" << endl;
    cout << "======================================================" << endl;
}


//���� ����������
void sortMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - ���������� �� ������                           |" << endl;
    cout << "| 2 - ���������� �� �������� �����������             |" << endl;
    cout << "| 3 - ���������� �� �������� ����                    |" << endl;
    cout << "| 4 - ���������� �� �������� ���������               |" << endl;
    cout << "| 5 - ���������� �� ����������� ���������            |" << endl;
    cout << "| 6 - ���������� �� ����                             |" << endl;
    cout << "| 7 - ���������� �� ������                           |" << endl;
    cout << "| 8 - ���������� �� ������� ����������               |" << endl;
    cout << "| 0 - �����                                          |" << endl;
    cout << "======================================================" << endl;
}

// ���� ���� ����������
void sortCriterionMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - ���������� �� �����������                      |" << endl;
    cout << "| 2 - ���������� �� ��������                         |" << endl;
    cout << "| 0 - �����                                          |" << endl;
    cout << "======================================================" << endl;
}


void txtMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - ������� ������ � ���������� �����              |" << endl;
    cout << "| 2 - ������� ������ � ��������� ����                |" << endl;
    cout << "| 0 - �����                                          |" << endl;
    cout << "======================================================" << endl;
}


void requestsMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - ����������� ����������� � ������               |" << endl;
    cout << "| 2 - ����� ��������������� ������� ����������      |" << endl;
    cout << "| 3 - C����� ����� �����������                       |" << endl;
    cout << "| 4 - ����������� ����������� ���������� ���������   |" << endl;
    cout << "| 0 - �����                                          |" << endl;
    cout << "======================================================" << endl;
}


//������� ����������
void sortVector(vector<product>& products) {
    int sortCommand{};
    do {
        sortMenu();
        sortCommand = getCorrectValue();
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
                cout << "����������� �������, �������� ����� ���� 1-8. ��������� �������!" << endl;
        }

        typeOfSort(products, criterion);
        cout << "���������� ������� ���������!" << endl;
    } while (sortCommand);
}

//����� ���� ����������
void typeOfSort(vector<product>& products, SortCriterion criterion) {
    int sortCriterionCommand;
    do {
        sortCriterionMenu();
        sortCriterionCommand = getCorrectValue();
        switch (sortCriterionCommand) {
            case 1:
                sort(products.begin(), products.end(), [criterion](const product &a, const product &b) {
                    return sortByCriterion(a, b, criterion);
                });
                return ;
            case 2:
                sort(products.begin(), products.end(), [criterion](const product &a, const product &b) {
                    return !sortByCriterion(a, b, criterion);
                });
                return ;
            default:
                cout << "����������� �������, �������� ����� 1 ��� 2. ��������� �������!" << endl;
        }
    } while (sortCriterionCommand);
}

//�������� �����
void getCorrectName(string &name, string object) {
    bool isNotOk{};
    string temp;

    do {
        isNotOk = false;
        cout << "������� " << object << ": ";
        cin >> temp;

        if (temp.length() > 20) {
            cout << "����� ����� ������ ���������� �� ����� 20 ��������!" << endl;
            isNotOk = true;
            continue;
        }

        for (int i = 0; temp[i] != '\0'; i++) {
            if ((temp[i] >= ' ' && temp[i] <= '@') || (temp[i] >= '[' && temp[i] < 'a') || 
                (temp[i] >= '{' && temp[i] <= '~')){
                cout << "��� ������ ��������� ������ �����!" << endl;
                isNotOk = true;
                break;
            }
        }

        if (!isNotOk) {
            name = temp;
        }
    } while (isNotOk);
}

int getCorrectInputNumber(int begin, int end){
    int n{};
    bool isNotOk{};
    do{
        isNotOk = false;
        if(((cin >> n).fail()) || (n < begin || n > end)){
            fixStreamState();
            cout << "������������ ����! ����� ������ ���� ����� " << begin << " � " << end << "!"<< endl;
            cout << "���������� �����!" << endl;
            isNotOk = true;  
        }
    }
    while (isNotOk);

    return n;
}

//��������������
void editData(vector<product>& products) {
    if(!products.empty()){
        string chiefSurname;
        printTable(products);
        cout << "������� ����� ��� �������������� (�� 1 �� " << products.size() << "): " << endl;
        int numberToeditData = getCorrectInputNumber(1, products.size());
        getCorrectName(products[numberToeditData - 1].chiefSurname, "������� ����� ������� ����������: ");
        cout << "������ ���� ������� ���������!" << endl;
        return ;
    }
    else {
        cout << "� ������� ��� ������!" << endl;
        return ;
    }
}

//��������
void deleteData(vector<product>& products) {
    if (!products.empty()) {
        printTable(products);
        cout << "Enter the number to deleteData (1 to " << products.size() << "): " << endl;
        int numberTodeleteData = getCorrectInputNumber(1, products.size());
        products.erase(products.begin() + (numberTodeleteData - 1));

        for (int i = numberTodeleteData - 1; i < products.size(); i++) {
            products[i].number -= 1; 
        }
        cout << "������ ���� ������� �������!" << endl;
        return;

    } else {
        cout << "� ������� ��� ������!" << endl;
        return;
    }
}


void readingDataFromTxt(vector<product>& products){
    ifstream fin("text.txt");
    if (!fin.is_open()) {
        cout << "�� ������� ������� ����..." << endl;
        return;
    }

    product prod;
    while (fin >> prod.company >> prod.workshop >> prod.productName 
           >> prod.productCount >> prod.date.day >> prod.date.month >> prod.date.year 
           >> prod.districtOfCompany >> prod.chiefSurname) {
                prod.number = products.size() + 1;
                products.push_back(prod);
    }

    cout << "������ ������� �������." << endl;
    fin.close();
}


//����� ������ � ��������� ����
void addToTxt(vector<product>& products){
    ofstream fout;
    fout.open("text.txt");
    if(fout.is_open()){
        cout << "���� ������!";
        for(const auto& prod : products){
            fout << prod.company << " ";
            fout << prod.workshop << " ";
            fout << prod.productName << " ";
            fout << prod.productCount << " ";
            fout << prod.date.day << " ";
            fout << prod.date.month << " ";
            fout << prod.date.year << " ";
            fout << prod.districtOfCompany << " ";
            fout << prod.chiefSurname << " " << "\n";
        }
        cout << "\n������ ������� �������� � ����.\n";
    }
    else{
        cout << "�� ������� ������� ����...\n";
    }
    fout.close();
}


void txtData(vector<product>& products) {
    int actionsDataCommand{};
    do {
        txtMenu();
        actionsDataCommand = getCorrectValue();

        switch (actionsDataCommand) {
            case 1:
                readingDataFromTxt(products);
                break;
            case 2:
                addToTxt(products);
                break;
            case 0:
                return;
            default:
                cout << "����������� �������, �������� ����� ���� 1-2. ��������� �������!" << endl;
        }
    } while (actionsDataCommand);
}


void businessesInTheArea(const vector<product>& products){
    int count = 0;
    string Area;
    
    cout << "\n������� �������� ������:";
    cin >> Area;

    for(const auto& prod : products){
        if(Area == prod.districtOfCompany){
            count = count + 1;
        }
    }

    if(count != 0){
        cout << "\n� ������ ������ ����������� " << count << " �����������(-��).";
        cout << "\n�������� �����������(-��) �������������(-��) � ������ ������:\n";
    }
    else{
        cout << "\n������ ������ ��� � ���� ������!\n\n";
        return;
    }

    for(const auto& prod : products){
        if(Area == prod.districtOfCompany){
            cout <<  prod.company << endl;
        }
    }

}


void theCommonSurname(const vector<product>& products){
    unordered_map<string, int> surnameCount;
    string mostCommonSurname;
    int count = 0;

    for(const auto& prod : products){
        surnameCount[prod.chiefSurname]++;
    }

    for (const auto& prod : surnameCount) {
        if (prod.second > count){
            count = prod.second;
            mostCommonSurname = prod.first;
        }
    }

    if(count > 1){
        cout << "\n�������� ��������������� ������� ���������� ����: \n" << mostCommonSurname << " (����������� " << count << " ���(�) )\n\n";
    }
    else{
        cout << "\n���������� �� �������!\n\n";
    }

}


void listOfWorkshops(const vector<product>& products){
    int count = 0;
    string Company;
    
    cout << "\n������� �������� �����������: ";
    cin >> Company;

    for(const auto& prod : products){
        if(Company == prod.company){
            count++;
        }
    }

    if(count != 0){
        cout << "\n� ����������� <" << Company << "> ������� " << count << " ����(-��)\n";
        cout << "\n������ �����:\n";
    }
    else{
        cout << "\n����������� ������!\n\n";
        return;
    }

    for(const auto& prod : products){
        if(Company == prod.company){
            cout  << "   "<< prod.workshop << endl;
        }
    }
    cout << "\n";
}


void companyProducingProducts(const vector<product>& products){
    int companyCount = 0;
    string product;

    cout << "������� �������� ���������: ";
    cin >> product;

    for(const auto& prod : products){
        if(product == prod.productName){
            companyCount++;
        }
    }

    if(companyCount == 0){
        cout << "\n��� ������ � ������� ������ ���������!\n\n";
        return;
    }
    else if(companyCount == 1){
        cout << "\n" << companyCount << " ����������� ��������� ������ ���������\n\n";
    }
    else{
        cout << "\n" << companyCount << " �����������(-��) ���������(-��) ������ ���������\n\n";
    }

    cout << "�����������(-��) �����������(-��) ������ ���������: \n";

    for(const auto& prod : products){
        if(product == prod.productName){
            cout << "   " << prod.company << "\n";
        }
    }
}


void requests(vector<product>& products) {
    int actionsDataCommand{};
    do {
        requestsMenu();
        actionsDataCommand = getCorrectValue();

        switch (actionsDataCommand) {
            case 1:
                businessesInTheArea(products);
                break;
            case 2:
                theCommonSurname(products);
                break;
            case 3:
                listOfWorkshops(products);
                break;
            case 4:
                companyProducingProducts(products);
                break;
            case 0:
                return;
            default:
                cout << "����������� �������, �������� ����� ���� 1-2. ��������� �������!" << endl;
        }
    } while (actionsDataCommand);
}