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

//Вывод таблицы
size_t utf8Length(const string& str);
void printAligned(const string& str, size_t width);
void printTable(const vector<product>& products);

//Сортировка
bool sortByCriterion(const product &a, const product &b, SortCriterion criterion);
void sortVector(vector<product>& products);
void typeOfSort(vector<product>& products, SortCriterion criterion);

//Обработка ошибок при вводе
void getCorrectName(string &name, string object);
int getCorrectInputNumber(int begin, int end);
void fixStreamState();
int getCorrectValue();

//Работа с данными
void actionsData(vector<product>& products);
product addData(vector<product>& product);
void editData(vector<product>& products);
void deleteData(vector<product>& products);

//Работа с текстовыми файлами
void txtData(vector<product>& products);
void readingDataFromTxt(vector<product>& products);
void addToTxt(vector<product>& products);

//Дополнительные запросы
void businessesInTheArea(const vector<product>& products);
void theCommonSurname(const vector<product>& products);
void listOfWorkshops(const vector<product>& products);
void companyProducingProducts(const vector<product>& products);
void requests(vector<product>& products);

//МЕНЮ
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
                cout << "Программа завершена!" << endl; 
                break;
            default:
                cout << "Неизвестная команда!" << endl;
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
            cout << "Неизвестная команда!" << endl;
            cout << "Попробуйте снова!" << endl;
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

// Пробелы
void printAligned(const string& str, size_t width) {
    size_t len = utf8Length(str);
    cout << str;
    for (size_t i = 0; i < width - len; i++) {
        cout << ' ';
    }
}



//Вывод таблицы
void printTable(const vector<product>& products) {
    if (products.empty()) {
        cout << "Нет данных для отображения. Таблица пуста." << endl;
        return;
    }

    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| № |    Предпритие     |       Цех           |   Название продукта     | Кол-во | Дата выпуска  |      Район     | Фамилия начальника |\n";
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
product addData(vector<product>& Product) {
    product product;
    
    cin.ignore();
    getCorrectName(product.company, "название предприятия");
    

    getCorrectName(product.workshop, "название цеха");
    

    getCorrectName(product.productName, "название продукта");
    
    cout << "Введите колличество единиц в партии: ";
    product.productCount = getCorrectValue();
    
    cout << "Укажите день выпуска продукта: ";
    product.date.day = getCorrectInputNumber(1, 31);
    
    cout << "Укажите месяц выпуска продукта: ";
    product.date.month = getCorrectInputNumber(1, 12);

    cout << "Укажите год выпуска продукта ";
    product.date.year = getCorrectInputNumber(1970, 2025);

    getCorrectName(product.districtOfCompany, "район, в котором расположено предприятие");
    

    getCorrectName(product.chiefSurname, "фамилию начальника цеха");
    
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
                cout << "Неизвестная команда, выберите пункт меню 1-3. Повторите попытку!" << endl;
        }
    } while (actionsDataCommand);
}


// Критерий соортировки
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

// Основное меню
void printMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - Действия с данными                             |" << endl;
    cout << "| 2 - Показать таблицу                               |" << endl;
    cout << "| 3 - Сортировка                                     |" << endl;
    cout << "| 4 - Работа с текстовыми файлами                    |" << endl;
    cout << "| 5 - Дополнительный функционал                      |" << endl;
    cout << "| 0 - Выход                                          |" << endl;
    cout << "======================================================" << endl;
}

void actionsDataMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - Добавить предприятие                           |" << endl;
    cout << "| 2 - Изменить фамилию начальника                    |" << endl;
    cout << "| 3 - Удалить данные                                 |" << endl;
    cout << "| 0 - Назад                                          |" << endl;
    cout << "======================================================" << endl;
}


//Меню сортировки
void sortMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - Сортировка по номеру                           |" << endl;
    cout << "| 2 - Сортировка по названию предприятия             |" << endl;
    cout << "| 3 - Сортировка по названию цеха                    |" << endl;
    cout << "| 4 - Сортировка по названию продукции               |" << endl;
    cout << "| 5 - Сортировка по колличеству продукции            |" << endl;
    cout << "| 6 - Сортировка по дате                             |" << endl;
    cout << "| 7 - Сортировка по району                           |" << endl;
    cout << "| 8 - Сортировка по фамилии начальника               |" << endl;
    cout << "| 0 - Назад                                          |" << endl;
    cout << "======================================================" << endl;
}

// Меню вида сортировки
void sortCriterionMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - Сортировка по возрастанию                      |" << endl;
    cout << "| 2 - Сортировка по убыванию                         |" << endl;
    cout << "| 0 - Назад                                          |" << endl;
    cout << "======================================================" << endl;
}


void txtMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - Считать данные с текстового файла              |" << endl;
    cout << "| 2 - Вывести данные в текстовый файл                |" << endl;
    cout << "| 0 - Назад                                          |" << endl;
    cout << "======================================================" << endl;
}


void requestsMenu() {
    cout << "======================================================" << endl;
    cout << "| 1 - Колличество предприятий в районе               |" << endl;
    cout << "| 2 - Самая распространённая фамилия начальника      |" << endl;
    cout << "| 3 - Cписок цехов предприятия                       |" << endl;
    cout << "| 4 - Предприятия выпускающие одинаковую продукцию   |" << endl;
    cout << "| 0 - Назад                                          |" << endl;
    cout << "======================================================" << endl;
}


//Функция сортировки
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
                cout << "Неизвестная команда, выберите пункт меню 1-8. Повторите попытку!" << endl;
        }

        typeOfSort(products, criterion);
        cout << "Сортировка успешно завершена!" << endl;
    } while (sortCommand);
}

//Выбор вида сортировки
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
                cout << "Неизвестная команда, выберите пункт 1 или 2. Повторите попытку!" << endl;
        }
    } while (sortCriterionCommand);
}

//Проверка строк
void getCorrectName(string &name, string object) {
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
            fixStreamState();
            cout << "Некорректный ввод! Число должно быть между " << begin << " и " << end << "!"<< endl;
            cout << "Попробуйте снова!" << endl;
            isNotOk = true;  
        }
    }
    while (isNotOk);

    return n;
}

//Редактирование
void editData(vector<product>& products) {
    if(!products.empty()){
        string chiefSurname;
        printTable(products);
        cout << "Введите номер для редактирования (от 1 до " << products.size() << "): " << endl;
        int numberToeditData = getCorrectInputNumber(1, products.size());
        getCorrectName(products[numberToeditData - 1].chiefSurname, "Введите новую фамилию начальника: ");
        cout << "Данные были успешно обновлены!" << endl;
        return ;
    }
    else {
        cout << "В таблице нет данных!" << endl;
        return ;
    }
}

//Удаление
void deleteData(vector<product>& products) {
    if (!products.empty()) {
        printTable(products);
        cout << "Enter the number to deleteData (1 to " << products.size() << "): " << endl;
        int numberTodeleteData = getCorrectInputNumber(1, products.size());
        products.erase(products.begin() + (numberTodeleteData - 1));

        for (int i = numberTodeleteData - 1; i < products.size(); i++) {
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
                cout << "Неизвестная команда, выберите пункт меню 1-2. Повторите попытку!" << endl;
        }
    } while (actionsDataCommand);
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
        cout << "\nВ данном районе расположено " << count << " предприятия(-ий).";
        cout << "\nНазвание предприятия(-ий) расположенной(-ых) в данном районе:\n";
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
    
    cout << "\nВведите название предприятия: ";
    cin >> Company;

    for(const auto& prod : products){
        if(Company == prod.company){
            count++;
        }
    }

    if(count != 0){
        cout << "\nУ предприятия <" << Company << "> имеется " << count << " цеха(-ов)\n";
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


void companyProducingProducts(const vector<product>& products){
    int companyCount = 0;
    string product;

    cout << "Введите название продукции: ";
    cin >> product;

    for(const auto& prod : products){
        if(product == prod.productName){
            companyCount++;
        }
    }

    if(companyCount == 0){
        cout << "\nНет данных о выпуске данной продукции!\n\n";
        return;
    }
    else if(companyCount == 1){
        cout << "\n" << companyCount << " предприятие выпускает данную продукцию\n\n";
    }
    else{
        cout << "\n" << companyCount << " предприятия(-ий) выпускают(-ет) данную продукцию\n\n";
    }

    cout << "Предприятия(-ие) выпускающие(-ие) данную продукцию: \n";

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
                cout << "Неизвестная команда, выберите пункт меню 1-2. Повторите попытку!" << endl;
        }
    } while (actionsDataCommand);
}