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

product Add(vector<product>& product);
int GetCorrectValue();
size_t utf8_length(const string& str);
void printAligned(const string& str, size_t width);
void PrintTable(const vector<product>& products);
void FixStreamState();
bool SortByCriterion(const product &a, const product &b, SortCriterion criterion);
void SortVector(vector<product>& products);
void TypeOfSort(vector<product>& products, SortCriterion criterion);
void txtVector(vector<product>& products);
void GetCorrectName(string &name, string object);
int getCorrectInputNumber(int begin, int end);
void Edit(vector<product>& products);
void Delete(vector<product>& products);
void readingDataFromTxt(vector<product>& products);
void addToTxt(vector<product>& products);
//Дополнительные запросы
void businessesInTheArea(const vector<product>& products);
void theCommonSurname(const vector<product>& products);
void listOfWorkshops(const vector<product>& products);
void Requests(vector<product>& products);

//МЕНЮ
void PrintMenu();
void SortMenu();
void SortCriterionMenu();
void TxtMenu();
void RequestsMenu();


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
                Edit(products);
                break;
            case 5:
                Delete(products);
                break;
            case 6:
                txtVector(products);
                break;
            case 7:
                Requests(products);
                break;
            case 0:
                cout << "Программа завершена!" << endl; 
                break;
            default:
                cout << "Неизвестная команда!" << endl;
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
            cout << "Неизвестная команда!" << endl;
            cout << "Попробуйте снова!" << endl;
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
            i += 1;
        }
        length++;
    }
    return length;
}

// Пробелы
void printAligned(const string& str, size_t width) {
    size_t len = utf8_length(str);
    cout << str;
    for (size_t i = 0; i < width - len; i++) {
        cout << ' ';
    }
}



//Вывод таблицы
void PrintTable(const vector<product>& products) {
    if (products.empty()) {
        cout << "Нет данных для отображения. Таблица пуста." << endl;
        return;
    }

    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| № |     Компания      |       Цех           |   Название продукта     | Кол-во | Дата выпуска  |      Район     | Фамилия начальника |\n";
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
    GetCorrectName(product.company, "название компании");
    

    GetCorrectName(product.workshop, "название цеха");
    

    GetCorrectName(product.productName, "название продукта");
    
    cout << "Введите колличество единиц в партии: ";
    product.productCount = GetCorrectValue();
    
    cout << "Укажите день выпуска продукта: ";
    product.date.day = getCorrectInputNumber(1, 31);
    
    cout << "Укажите месяц выпуска продукта: ";
    product.date.month = getCorrectInputNumber(1, 12);

    cout << "Укажите год выпуска продукта ";
    product.date.year = getCorrectInputNumber(1970, 2025);

    GetCorrectName(product.districtOfCompany, "район, в котором расположено предприятие");
    

    GetCorrectName(product.chiefSurname, "фамилию начальника цеха");
    
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
    cout << "================================================" << endl;
    cout << "| 1 - Добавить компанию                        |" << endl;
    cout << "| 2 - Показать таблицу                         |" << endl;
    cout << "| 3 - Сортировка                               |" << endl;
    cout << "| 4 - Изменить фамилию начальника              |" << endl;
    cout << "| 5 - Удалить данные                           |" << endl;
    cout << "| 6 - Работа с текстовыми файлами              |" << endl;
    cout << "| 7 - Дополнительный функционал                |" << endl;
    cout << "| 0 - Выход                                    |" << endl;
    cout << "================================================" << endl;
}

//Меню сортировки
void SortMenu() {
    cout << "================================================" << endl;
    cout << "| 1 - Сортировка по номеру                     |" << endl;
    cout << "| 2 - Сортировка по названию компании          |" << endl;
    cout << "| 3 - Сортировка по названию цеха              |" << endl;
    cout << "| 4 - Сортировка по названию продукции         |" << endl;
    cout << "| 5 - Сортировка по колличеству продукции      |" << endl;
    cout << "| 6 - Сортировка по дате                       |" << endl;
    cout << "| 7 - Сортировка по району                     |" << endl;
    cout << "| 8 - Сортировка по фамилии начальника         |" << endl;
    cout << "| 0 - Назад                                    |" << endl;
    cout << "================================================" << endl;
}

// Меню вида сортировки
void SortCriterionMenu() {
    cout << "================================================" << endl;
    cout << "| 1 - Сортировка по возрастанию                |" << endl;
    cout << "| 2 - Сортировка по убыванию                   |" << endl;
    cout << "| 0 - Назад                                    |" << endl;
    cout << "================================================" << endl;
}


void TxtMenu() {
    cout << "================================================" << endl;
    cout << "| 1 - Считать данные с текстового файла        |" << endl;
    cout << "| 2 - Вывести данные в текстовый файл          |" << endl;
    cout << "| 0 - Назад                                    |" << endl;
    cout << "================================================" << endl;
}


void RequestsMenu() {
    cout << "================================================" << endl;
    cout << "| 1 - Колличество предприятий в районе         |" << endl;
    cout << "| 2 - Самая распространённая фамилия начальника|" << endl;
    cout << "| 3 - Получить список цехов предприятия        |" << endl;
    cout << "| 0 - Назад                                    |" << endl;
    cout << "================================================" << endl;
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
                cout << "Неизвестная команда, выберите пункт меню 1-8. Повторите попытку!" << endl;
        }

        TypeOfSort(products, criterion);
        cout << "Сортировка успешно завершена!" << endl;
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
                cout << "Неизвестная команда, выберите пункт 1 или 2. Повторите попытку!" << endl;
        }
    } while (sortCriterionCommand);
}

//Проверка строк
void GetCorrectName(string &name, string object) {
    bool isNotOk{};
    string temp;

    do {
        isNotOk = false;
        cout << "Введите " << object << ": ";
        cin >> temp;

        if (temp.length() > 20) {
            cout << "Длина имени должна составлять не более 20 символов!" << endl;
            isNotOk = true;
            continue;
        }

        for (int i = 0; temp[i] != '\0'; i++) {
            if ((temp[i] >= ' ' && temp[i] <= '@') || (temp[i] >= '[' && temp[i] < 'a') || 
                (temp[i] >= '{' && temp[i] <= '~')){
                cout << "Имя должно содержать только буквы!" << endl;
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
            FixStreamState();
            cout << "Некорректный ввод! Число должно быть между " << begin << " и " << end << "!"<< endl;
            cout << "Попробуйте снова!" << endl;
            isNotOk = true;  
        }
    }
    while (isNotOk);

    return n;
}

//Редактирование
void Edit(vector<product>& products) {
    if(!products.empty()){
        string chiefSurname;
        PrintTable(products);
        cout << "Введите номер для редактирования (от 1 до " << products.size() << "): " << endl;
        int numberToEdit = getCorrectInputNumber(1, products.size());
        GetCorrectName(products[numberToEdit - 1].chiefSurname, "Введите новую фамилию начальника: ");
        cout << "Данные были успешно обновлены!" << endl;
        return ;
    }
    else {
        cout << "В таблице нет данных!" << endl;
        return ;
    }
}

//Удаление
void Delete(vector<product>& products) {
    if (!products.empty()) {
        PrintTable(products);
        cout << "Enter the number to delete (1 to " << products.size() << "): " << endl;
        int numberToDelete = getCorrectInputNumber(1, products.size());
        products.erase(products.begin() + (numberToDelete - 1));

        for (int i = numberToDelete - 1; i < products.size(); i++) {
            products[i].number -= 1; 
        }
        cout << "Данные были успешно удалены!" << endl;
        return;

    } else {
        cout << "В таблице нет данных!" << endl;
        return;
    }
}


void readingDataFromTxt(vector<product>& products){
    ifstream fin("text.txt");
    if (!fin.is_open()) {
        cout << "Не удалось открыть файл..." << endl;
        return;
    }

    product prod;
    while (fin >> prod.company >> prod.workshop >> prod.productName 
           >> prod.productCount >> prod.date.day >> prod.date.month >> prod.date.year 
           >> prod.districtOfCompany >> prod.chiefSurname) {
                prod.number = products.size() + 1;
                products.push_back(prod);
    }

    cout << "Данные успешно считаны." << endl;
    fin.close();
}


//ВЫВОД ДАННЫХ В ТЕКСТОВЫЙ ФАЙЛ
void addToTxt(vector<product>& products){
    ofstream fout;
    fout.open("text.txt");
    if(fout.is_open()){
        cout << "Файл открыт!";
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
        cout << "\nДанные успешно записаны в файл.\n";
    }
    else{
        cout << "Не удалось открыть файл...\n";
    }
    fout.close();
}


void txtVector(vector<product>& products) {
    int requestsCommand{};
    do {
        TxtMenu();
        requestsCommand = GetCorrectValue();

        switch (requestsCommand) {
            case 1:
                readingDataFromTxt(products);
                break;
            case 2:
                addToTxt(products);
                break;
            case 0:
                return;
            default:
                cout << "Неизвестная команда, выберите пункт меню 1-2. Повторите попытку!" << endl;
        }
    } while (requestsCommand);
}


void businessesInTheArea(const vector<product>& products){
    int count = 0;
    string Area;
    
    cout << "\nВведите название района:";
    cin >> Area;

    for(const auto& prod : products){
        if(Area == prod.districtOfCompany){
            count = count + 1;
        }
    }

    if(count != 0){
        cout << "\nВ данном районе расположено " << count << " компании(-ий).";
        cout << "\nНазвание компании(-ий) расположенной(-ых) в данном районе:\n";
    }
    else{
        cout << "\nТакого района нет в базе данных!\n\n";
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
        cout << "\nНаиболее распространённая фамилия начальника цеха: \n" << mostCommonSurname << " (встречается " << count << " раз(а) )\n\n";
    }
    else{
        cout << "\nСовпадений не найдено!\n\n";
    }

}


void listOfWorkshops(const vector<product>& products){
    int count = 0;
    string Company;
    
    cout << "\nВведите название компании: ";
    cin >> Company;

    for(const auto& prod : products){
        if(Company == prod.company){
            count++;
        }
    }

    if(count != 0){
        cout << "\nУ компании <" << Company << "> имеется " << count << " цеха(-ов)\n";
        cout << "\nСписок цехов:\n";
    }
    else{
        cout << "\nОтсутствуют данные!\n\n";
        return;
    }

    for(const auto& prod : products){
        if(Company == prod.company){
            cout  << "   "<< prod.workshop << endl;
        }
    }
    cout << "\n";
}



void Requests(vector<product>& products) {
    int requestsCommand{};
    do {
        RequestsMenu();
        requestsCommand = GetCorrectValue();

        switch (requestsCommand) {
            case 1:
                businessesInTheArea(products);
                break;
            case 2:
                theCommonSurname(products);
                break;
            case 3:
                listOfWorkshops(products);
                break;
            case 0:
                return;
            default:
                cout << "Неизвестная команда, выберите пункт меню 1-2. Повторите попытку!" << endl;
        }
    } while (requestsCommand);
}