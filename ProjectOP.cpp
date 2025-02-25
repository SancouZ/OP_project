#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>
#include <fstream>


using namespace std;


const int MAXSTUD = 100;
int number = 0;


//ИНИЦИАЛИЗИРОВАНИЕ СТРУКТУРЫ
struct Student { 
    int studentn = 0;
    char surname[40]; 
    char name[40];
    int yearOfBirth;
    int yearOfAdmission; 
    int course;
    char groupe[15];
};

Student students[MAXSTUD];
char surname[40];
char name[40];


// ИНИЦИАЛИЗИРОВАНИЕ ФУНКЦИЙ
void PrintMenu();
void PrintMenuAddStud();
void PrintMenuSort();
void PrintMenuSortData();
void PrintMenuWorkFiles();
void addStud();
void workingWithFiles();
void readingDataFromTxt(Student students[], int& n);
void addToTxt(Student students[], int n);
void addToBin(Student students[], int n);
void readingDataFromBin(Student students[], int& n);
void addOneStud(Student students[], int& n);
void addManyStud(Student students[], int& n, int quanity);
void changeStud(Student students[], int n);
void deleteStud(Student students[], int& n);
void sortBubble();
void sortBubbleIncrease();
void sortBubbleDecreasing();
void sortBubbleNumberDecreasing(Student students[], int n);
void sortBubbleSurnameDecreasing(Student students[], int n);
void sortBubbleName(Student students[], int n);
void sortBubbleYearOfBirthDecreasing(Student students[], int n);
void sortBubbleYearOfAdmissionDecreasing(Student students[], int n);
void sortBubbleCourseDecreasing(Student students[], int n);
void sortBubbleGroupeDecreasing(Student students[], int n);
void sortBubbleNumberIncreasing(Student students[], int n);
void sortBubbleSurnameIncreasing(Student students[], int n);
void sortBubbleNameIncreasing(Student students[], int n);
void sortBubbleYearOfBirthIncreasing(Student students[], int n);
void sortBubbleYearOfAdmissionIncreasing(Student students[], int n);
void sortBubbleCourseIncreasing(Student students[], int n);
void sortBubbleGroupeIncreasing(Student students[], int n);
void printoutOnRequest(Student students[], int n);
void tableStud(Student students[], int n);
void printAligned(const char* str, size_t width);
void FixStreamState();
int GetCorrectValue(void PrintMenu());
int GetCorrectValueChange();
void getCorrectSurname(char surname[]);
void getCorrectName(char name[]);
void getCorrectGroupe(char groupe[]);
int getCorrectInputNumber(int begin, int end);


int main()
{
    setlocale(LC_ALL, "Russian");
    int command{};


    do 
    {
        PrintMenu();
        command = GetCorrectValue(PrintMenu);
        switch (command)
        {
            case 1:
                tableStud(students, number);
            break;
            case 2:
                addStud();
            break;
            case 3:
                changeStud(students, number);
                break;
            case 4:
                deleteStud(students, number);
                break;
            case 5:
                sortBubbleYearOfBirthDecreasing(students, number);
                printoutOnRequest(students, number);
                break;
            case 6:
                sortBubble();
                break;
            case 7:
                workingWithFiles();
                break;
            case 0: 
                cout << "Программа завершена. Досвидания!" << endl; 
                break;
            default: 
                cout << "Неизвестная команда! Попробуйте снова." << endl;
        }
    }
    while (command != 0);

    
}


//МЕНЮ
void PrintMenu(){
    cout << "\n|-----------------Меню-----------------|" << endl;
    cout << "|1 - Вывести таблицу на экран.         |" << endl;
    cout << "|2 - Добавить студента вручную.        |" << endl;
    cout << "|3 - Изменить запись.                  |" << endl;
    cout << "|4 - Удалить запись.                   |" << endl;
    cout << "|5 - Вывод по запросу.                 |" << endl;
    cout << "|6 - Сортировка.                       |" << endl;
    cout << "|7 - Работа с файлами.                 |" << endl;
    cout << "|0 - Выйти из программы.               |" << endl;
    cout << "|--------------------------------------|" << endl;
}


void PrintMenuAddStud(){
    cout << "\n|------Добавление учеников------|" << endl;
    cout << "|1 - Внести одного ученика.     |" << endl;
    cout << "|2 - Внести несколько учеников. |" << endl;
    cout << "|0 - Назад.                     |" << endl;
    cout << "|-------------------------------|" << endl;
}


void PrintMenuSort(){
    cout << "\n|----------Сортировка-----------|" << endl;
    cout << "|1 - По возрастанию.            |" << endl;
    cout << "|2 - По убыванию.               |" << endl;
    cout << "|0 - Назад.                     |" << endl;
    cout << "|-------------------------------|" << endl;
}


void PrintMenuSortData(){
    cout << "\n|----------Сортировка-----------|" << endl;
    cout << "|1 - По номеру.                 |" << endl;
    cout << "|2 - По фамилии.                |" << endl;
    cout << "|3 - По имени.                  |" << endl;
    cout << "|4 - По году рождения.          |" << endl;
    cout << "|5 - По году поступления.       |" << endl;
    cout << "|6 - По курсу.                  |" << endl;
    cout << "|7 - По группе.                 |" << endl;
    cout << "|0 - Назад.                     |" << endl;
    cout << "|-------------------------------|" << endl;
}



void PrintMenuChange(){
    cout << "\n1 - По фамилии." << endl;
    cout << "2 - По имени." << endl;
    cout << "3 - По году рождения." << endl;
    cout << "4 - По году поступления." << endl;
    cout << "5 - По курсу." << endl;
    cout << "6 - По группе." << endl;
}




void PrintMenuWorkFiles(){
    cout << "\n|----------Работа с файлами------------|" << endl;
    cout << "|1 - Считать данные с бинарного файла. |" << endl;
    cout << "|2 - Считать данные с текстового файла.|" << endl;
    cout << "|3 - Вывести данные в бинарный файл.   |" << endl;
    cout << "|4 - Вывести данные в текстовый файл.  |" << endl;
    cout << "|0 - Назад.                            |" << endl;
    cout << "|--------------------------------------|" << endl;
}






//ДОБАВЛЕНИЕ СТУДЕНТА
void addStud(){
    int quanity{};
    int command;
    do{
        PrintMenuAddStud();
        command = GetCorrectValue(PrintMenuAddStud);

        switch(command){
            case 1:
                addOneStud(students, number);
                break;
            case 2:
                cout << "Введите кол-во студентов для добавления: " << endl;
                quanity = getCorrectInputNumber(1, 100000);
                addManyStud(students, number, quanity);
                break;
            case 0:
                break;
            default:
                cout << "Неизвестная команда! Попробуйте снова." << endl;
        }
    }
    while(command != 0);
}



//РАБОТА С ФАЙЛАМИ
void workingWithFiles(){
    int command;
    do{
        PrintMenuWorkFiles();
        command = GetCorrectValue(PrintMenuWorkFiles);

        switch(command){
            case 1:
                readingDataFromBin(students, number);
                break;
            case 2:
                readingDataFromTxt(students, number);
                break;
            case 3:
                addToBin(students, number);
                break;
            case 4:
                addToTxt(students, number);
                break;
            case 0:
                break;
            default:
                cout << "Неизвестная команда! Попробуйте снова." << endl;
        }
    }
    while(command != 0);
}




//ВЫБОР ВИДА СОРТИРОВКИ
void sortBubble(){
    int command;

    do{
        PrintMenuSort();
        command = GetCorrectValue(PrintMenuSort);

        switch(command){
            case 1:
                sortBubbleIncrease();
                break;
            case 2:
                sortBubbleDecreasing();
                break;
            case 0:
                break;
            default:
                cout << "Неизвестная команда! Попробуйте снова." << endl;
        }   
    }
    while(command != 0);
}





//СОРТИРОВКА ПО ВОЗРАСТАНИЮ
void sortBubbleIncrease(){
    int command;

    do{
        PrintMenuSortData();
        command = GetCorrectValue(PrintMenuSortData);

        switch(command){
            case 1:
                sortBubbleNumberIncreasing(students, number);
                break;
            case 2:
                sortBubbleSurnameIncreasing(students, number);
                break;
            case 3:
                sortBubbleNameIncreasing(students, number);
                break;
            case 4:
                sortBubbleYearOfBirthIncreasing(students, number);
                break;
            case 5:
                sortBubbleYearOfAdmissionIncreasing(students, number);
                break;
            case 6:
                sortBubbleCourseIncreasing(students, number);
                break;
            case 7:
                sortBubbleGroupeIncreasing(students, number);
                break;
            case 0:
                break;
            default:
                cout << "Неизвестная команда! Попробуйте снова." << endl;
        }
    }
    while(command != 0);
}




//СОРТИРОВКА ПО УБЫВАНИЮ
void sortBubbleDecreasing(){
    int command;

    do{
        PrintMenuSortData();
        command = GetCorrectValue(PrintMenuSortData);

        switch(command){
            case 1:
                sortBubbleNumberDecreasing(students, number);
                break;
            case 2:
                sortBubbleSurnameDecreasing(students, number);
                break;
            case 3:
                sortBubbleName(students, number);
                break;
            case 4:
                sortBubbleYearOfBirthDecreasing(students, number);
                break;
            case 5:
                sortBubbleYearOfAdmissionDecreasing(students, number);
                break;
            case 6:
                sortBubbleCourseDecreasing(students, number);
                break;
            case 7:
                sortBubbleGroupeDecreasing(students, number);
                break;
            case 0:
                break;
            default:
                cout << "Неизвестная команда! Попробуйте снова." << endl;
        }
    }
    while(command != 0);
}





//СЧИТЫВАНИЕ ДАННЫХ С ТЕКСТОВОГО ФАЙЛА
void readingDataFromTxt(Student students[], int& n){
    ifstream fin;
    fin.open("text.txt");
    if(fin.is_open()){
        if(n + 1 <= MAXSTUD){
            while(fin >> students[n].surname >> students[n].name 
            >> students[n].yearOfBirth >> students[n].yearOfAdmission 
            >> students[n].course >> students[n].groupe){
                students[n].studentn = n + 1;
                n++;
                if(n + 1 > MAXSTUD){
                    cout << "\nДостигнут лимит студентов!";
                    break;
                }
            }
            cout << "\nДанные успешно считан.";
        }
        else{
            cout << "Достигнут лимит студентов!\nНельзя считать данные!";
        }
    }
    else{
        cout << "Не удалось открыть файл...";
    }
    fin.close();
}



//ВЫВОД ДАННЫХ В ТЕКСТОВЫЙ ФАЙЛ
void addToTxt(Student students[], int n){
    ofstream fout;
    fout.open("text.txt");
    if(fout.is_open()){
        cout << "Файл открыт!";
        for(int i = 0; i < n; i++){
            fout << students[i].surname << " ";
            fout << students[i].name << " ";
            fout << students[i].yearOfBirth << " ";
            fout << students[i].yearOfAdmission << " ";
            fout << students[i].course << " ";
            fout << students[i].groupe << "\n";
        }
        cout << "\nДанные успешно записаны в файл.";
    }
    else{
        cout << "Не удалось открыть файл...";
    }
    fout.close();
}



//ВЫВОД ДАННЫХ В БИНАРНЫЙ ФАЙЛ
void addToBin(Student students[], int n){
    ofstream fout("binar.dat", ios::out | ios::binary);
    if(fout.is_open()){
        for(int i = 0; i < n; i++){
            fout.write((char*)&students[i], sizeof(Student));
        }
        cout << "Данные успешно записаны в файл!";
    }
    else{
        cout << "Не удалось открыть файл!";
    }
    fout.close();
}



//СЧИТЫВАНИЕ ДАННЫХ С БИНАРНОГО ФАЙЛА
void readingDataFromBin(Student students[], int& n){
    ifstream fin("binar.dat", ios::in | ios::binary);
    if(fin.is_open()) {
        if(n + 1 <= MAXSTUD){
            while(fin.read((char *)&students[n], sizeof(Student))) {
                students[n].studentn = n + 1;
                n++;
                if(n + 1 > MAXSTUD){
                    cout << "Достигнут лимит студентов!";
                    break;
                }
            }
            cout << "\nДанные успешно считаны!";
            }
        else{
            cout << "Достигнут лимит студентов!\nНельзя считать данные!";
        }
    }
    else{
        cout << "Не удалось открыть файл...";
    }
    fin.close();
}




//ДОБАВЛЕНИЕ ОДНОГО СТУДЕНТА
void addOneStud(Student students[], int& n) {
    int yearOfBirth;
    if (n + 1 >= MAXSTUD) { 
    cout << "Слишком большое значение студентов!\n";
    return; 
    } 
        getCorrectSurname(students[n].surname);
        getCorrectName(students[n].name);
        cout << "Введите год рождения:";
        students[n].yearOfBirth = getCorrectInputNumber(1900, 2007);
        cout << "Введите год поступления:"; 
        students[n].yearOfAdmission = getCorrectInputNumber(1900, 2024);
        cout << "Введите курс:"; 
        students[n].course = getCorrectInputNumber(1, 9); 
        getCorrectGroupe(students[n].groupe);
        cout << "Данные о студенте добавлены!\n";
        students[n].studentn = number + 1;
        n++; 
}

//ДОБАВЛЕНИЕ НЕСКОЛЬКИХ СТУДЕНТОВ
void addManyStud(Student students[], int& n, int quanity){
    if (n + quanity > MAXSTUD) {
        cout << "Слишком большое значение!\n";
        return;
    }
    for (int i = 0; i < quanity; i++){ 
        getCorrectSurname(students[n].surname);
        getCorrectName(students[n].name); 
        cout << "Введите год рождения:"; 
        students[n].yearOfBirth = getCorrectInputNumber(1900, 2007);
        cout << "Введите год поступления:"; 
        students[n].yearOfAdmission = getCorrectInputNumber(1900, 2024);
        cout << "Введите курс:";
        students[n].course = getCorrectInputNumber(1, 9); 
        getCorrectGroupe(students[n].groupe);
        cout << "Данные о студенте добавлены!\n";
        students[n].studentn = n + 1;
        n++; 
    }
}


//РЕДАКТИРОВАНИЕ СТУДЕНТА
void changeStud(Student students[], int n) {
    sortBubbleNumberIncreasing(students, n);
    if (n < 1) {
        cout << "Таблица пуста. Изменение невозможно." << endl;
        return;
    }

    int num;
    cout << "\nВведите порядковый номер студента для редактирования: ";
    cin >> num;


    if (num < 1 || num > n) {
        cout << "Некорректный номер студента!" << endl;
        return;
    }

    
    PrintMenuChange();
    int field;
    cout << "Выберите поле для изменения: ";
    cin >> field;

    switch (field) {
        case 1:
            getCorrectSurname(students[num - 1].surname);
            break;
        case 2:
            getCorrectName(students[num - 1].name);
            break;
        case 3:
            cout << "Введите новый год рождения: ";
            students[num - 1].yearOfBirth = getCorrectInputNumber(1900, 2007);
            break;
        case 4:
            cout << "Введите новый год поступления: ";
            students[num - 1].yearOfAdmission = getCorrectInputNumber(1900, 2024);
            break;
        case 5:
            cout << "Введите новый курс: ";
            students[num - 1].course = getCorrectInputNumber(1, 9);
            break;
        case 6:
            cout << "Введите новую группу: ";
            getCorrectGroupe(students[num - 1].groupe);
            break;
        default:
            cout << "Некорректный выбор поля!" << endl;
            return;
    }

    cout << "Данные студента с порядковым номером " << num << " обновлены!" << endl;
    tableStud(students, n);
}



//УДАЛЕНИЕ СТУДЕНТОВ
void deleteStud(Student students[], int& n){
    sortBubbleNumberIncreasing(students, n);
    int num;
    if(n < 1){
        cout << "Таблица пуста. Удаление невозможно.";
        return;
    }
    while (true) {
        cout << "\nНомер студента:";
        cin >> num;
        if (cin.fail() || num < 1 || num > n) {
            cout << "Введены неверные символы. Пожалуйста, введите номер студента (от 1 до " << n << ") ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    for(int i = num - 1; i < n - 1; i++){
        students[i] = students[i + 1];
        students[i].studentn -= 1;
    }
    n--;

    cout << "Студент удалён!";
    cout << "Изменённая таблица\n";
    tableStud(students, number);
}




//РАСПЕЧАТКА ДАННЫХ ПО ЗАПРОСУ
void printoutOnRequest(Student students[], int n){
    if (n < 1) {
        cout << "Нет доступных студентов для вывода." << endl;
        return;
    }
    
    int countToPrint = min(3, n);
    for(int i = 0; i < countToPrint; i++){
        cout << left << setw(2) << students[i].studentn << " | ";
        printAligned(students[i].surname, 20);
        cout << "|";
        cout << setw(16) << students[i].yearOfBirth;
        cout << "|";
        printAligned(students[i].groupe, 15);
        cout << "|\n";
    }
}




//СОРТИРОВКА ПУЗЫРЬКОМ (НОМЕРУ) ПО УБЫВАНИЮ
void sortBubbleNumberDecreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].studentn < students[j + 1].studentn) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (ФАМИЛИЯ) ПО УБЫВАНИЮ
void sortBubbleSurnameDecreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(students[j].surname, students[j + 1].surname) < 0) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}


//СОРТИРОВКА ПУЗЫРЬКОМ (ИМЯ) ПО УБЫВАНИЮ
void sortBubbleName(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) < 0) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}





//СОРТИРОВКА ПУЗЫРЬКОМ (ГОД РОЖДЕНИЯ) ПО УБЫВАНИЮ
void sortBubbleYearOfBirthDecreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].yearOfBirth > students[j + 1].yearOfBirth) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (ГОД ПОСТУПЛЕНИЯ) ПО УБЫВАНИЮ
void sortBubbleYearOfAdmissionDecreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].yearOfAdmission < students[j + 1].yearOfAdmission) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (КУРС) ПО УБЫВАНИЮ
void sortBubbleCourseDecreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].course < students[j + 1].course) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}




//СОРТИРОВКА ПУЗЫРЬКОМ (ГРУППА) ПО УБЫВАНИЮ
void sortBubbleGroupeDecreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(students[j].groupe, students[j + 1].groupe) < 0) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (НОМЕР) ПО ВОЗРАСТАНИЮ
void sortBubbleNumberIncreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].studentn > students[j + 1].studentn) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (ФАМИЛИЯ) ПО ВОЗРАСТАНИЮ
void sortBubbleSurnameIncreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(students[j].surname, students[j + 1].surname) > 0) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}


//СОРТИРОВКА ПУЗЫРЬКОМ (ИМЯ) ПО ВОЗРАСТАНИЮ
void sortBubbleNameIncreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (ГОД РОЖДЕНИЯ) ПО ВОЗРАСТАНИЮ
void sortBubbleYearOfBirthIncreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].yearOfBirth < students[j + 1].yearOfBirth) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (ГОД ПОСТУПЛЕНИЯ) ПО ВОЗРАСТАНИЮ
void sortBubbleYearOfAdmissionIncreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].yearOfAdmission > students[j + 1].yearOfAdmission) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}



//СОРТИРОВКА ПУЗЫРЬКОМ (КУРС) ПО ВОЗРАСТАНИЮ
void sortBubbleCourseIncreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].course > students[j + 1].course) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}




//СОРТИРОВКА ПУЗЫРЬКОМ (ГРУППА) ПО ВОЗРАСТАНИЮ
void sortBubbleGroupeIncreasing(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(students[j].groupe, students[j + 1].groupe) > 0) {
                Student temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
    tableStud(students, number);
}







//ФУНКЦИИ НЕОБХОДИМЫЕ ДЛЯ НОРМАЛЬНОЙ РАБОТЫ ТАБЛИЦЫ
size_t utf8_length(const char* str) {
    size_t length = 0;
    for (size_t i = 0; str[i] != '\0';) {
        if ((str[i] & 0x80) == 0) {
            i += 1;
        } else if ((str[i] & 0xE0) == 0xC0) {
            i += 2;
        } else if ((str[i] & 0xF0) == 0xE0) {
            i += 3;
        } else if ((str[i] & 0xF8) == 0xF0) {
            i += 4;
        } else {
            i += 1;
        }
        length++;
    }
    return length;
}

void printAligned(const char* str, size_t width) {
    size_t len = utf8_length(str);
    cout << str;
    for (size_t i = 0; i < width - len; i++) {
        cout << ' ';
    }
}



//ТАБЛИЦА
void tableStud(Student students[], int n) {
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "| № |     Фамилия        |       Имя          |  Год рождения  |  Год поступления  | Курс |    Группа     |\n";
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < n; i++){
        cout << "|" << left << setw(3) << students[i].studentn << "|";
        printAligned(students[i].surname, 20);
        cout << "|";
        printAligned(students[i].name, 20);
        cout << "|";
        cout << setw(16) << students[i].yearOfBirth;
        cout << "|";
        cout << setw(19) << students[i].yearOfAdmission;
        cout << "|";
        cout << setw(6) << students[i].course;
        cout << "|";
        printAligned(students[i].groupe, 15);
        cout << "|\n";
        cout << "-----------------------------------------------------------------------------------------------------------\n";
    }
}


void FixStreamState(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}




//ПРОВЕРКА НА ВВОД ИМЕНИ
void getCorrectName(char name[]){
    bool isNotOk{};
    char temp[100];

    do{
        isNotOk = false;
        cout << "Введите имя:";
        cin >> temp;

        for (int i = 0; temp[i] != '\0'; i++){
            if (strlen(temp) > 20){
                temp[20] = '\0';
            }
            strcpy(name, temp);
        }

        for (int i = 0; name[i] != '\0'; i++) {
            if ((name[i] >= ' ' && name[i] <= '@') || (name[i] >= '[' && name[i] < 'a') 
            || (name[i] >= '{' && name[i] <= '~')){
                cout << "Некорректный ввод! Имя должно содержать только буквы." << endl;
                isNotOk = true;
                break;
            }
        }
    }
    while(isNotOk);
}



//ПРОВЕРКА НА ВВОД ФАМИЛИИ
void getCorrectSurname(char surname[]){
    bool isNotOk{};
    char temp[100];

    do{
        isNotOk = false;
        cout << "Введите фамилию:";
        cin >> temp;


        for (int i = 0; temp[i] != '\0'; i++){
            if (strlen(temp) > 20){
                temp[20] = '\0';
            }
        strcpy(surname, temp);
        }

        for (int i = 0; surname[i] != '\0'; i++) {
            if ((surname[i] >= ' ' && surname[i] <= '@') || (surname[i] >= '[' && surname[i] < 'a') 
            || (surname[i] >= '{' && surname[i] <= '~')){
                cout << "Некорректный ввод! Фамилия должна содержать только буквы." << endl;
                isNotOk = true;
                break;
            }
        }
    }
    while(isNotOk);
}




//ПРОВЕРКА НА ВВОД ГРУППЫ
void getCorrectGroupe(char groupe[]){
    bool isNotOk{};
    char temp[100];

    do{
        isNotOk = false;
        cout << "Введите группу:";
        cin >> temp;


        for (int i = 0; temp[i] != '\0'; i++){
            if (strlen(temp) > 15){
                temp[15] = '\0';
            }
        strcpy(groupe, temp);
        }

        for (int i = 0; groupe[i] != '\0'; i++) {
            if ((groupe[i] >= ' ' && groupe[i] <= ',') || (groupe[i] >= '.' && groupe[i] <= '/') || (groupe[i] >= ':' && groupe[i] <= '@')
              || (groupe[i] >= '[' && groupe[i] < 'a') || (groupe[i] >= '{' && groupe[i] <= '~')){
                cout << "Некорректный ввод! Введены запрещённые символы." << endl;
                isNotOk = true;
                break;
            }
        }
    }
    while(isNotOk);
}





//ПРОВЕРКА НА ВВОД ЦИФР
int getCorrectInputNumber(int begin, int end){
    int n{};
    bool isNotOk{};
    do{
        isNotOk = false;
        if(((cin >> n).fail()) || (n < begin || n > end)){
            FixStreamState();
            cout << "Некорректный ввод! Попробуйте снова." << endl;
            isNotOk = true;  
        }
    }
    while (isNotOk);

    return n;
}


//ПРОВЕРКА НА ПРАВИЛЬНОСТЬ ВВОДА
int GetCorrectValue(void PrintMenu()){
    int n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail()){
            FixStreamState();
            cout << "Неизвестная комманда! Попробуйте снова." << endl;
            isNotOk = true;
            PrintMenu();
        }
    }
    while (isNotOk);

    return n;
}



int GetCorrectValueChange(){
    int n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail()){
            FixStreamState();
            cout << "Неизвестная комманда! Попробуйте снова." << endl;
            isNotOk = true;
        }
    }
    while (isNotOk);

    return n;
}