#include <iostream>
#include <cstring>
#include <iomanip>
#include <limits>
#include <fstream>


using namespace std;


const int MAXSTUD = 100;
int number = 0;


//����������������� ���������
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


// ����������������� �������
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
                cout << "��������� ���������. ����������!" << endl; 
                break;
            default: 
                cout << "����������� �������! ���������� �����." << endl;
        }
    }
    while (command != 0);

    
}


//����
void PrintMenu(){
    cout << "\n|-----------------����-----------------|" << endl;
    cout << "|1 - ������� ������� �� �����.         |" << endl;
    cout << "|2 - �������� �������� �������.        |" << endl;
    cout << "|3 - �������� ������.                  |" << endl;
    cout << "|4 - ������� ������.                   |" << endl;
    cout << "|5 - ����� �� �������.                 |" << endl;
    cout << "|6 - ����������.                       |" << endl;
    cout << "|7 - ������ � �������.                 |" << endl;
    cout << "|0 - ����� �� ���������.               |" << endl;
    cout << "|--------------------------------------|" << endl;
}


void PrintMenuAddStud(){
    cout << "\n|------���������� ��������------|" << endl;
    cout << "|1 - ������ ������ �������.     |" << endl;
    cout << "|2 - ������ ��������� ��������. |" << endl;
    cout << "|0 - �����.                     |" << endl;
    cout << "|-------------------------------|" << endl;
}


void PrintMenuSort(){
    cout << "\n|----------����������-----------|" << endl;
    cout << "|1 - �� �����������.            |" << endl;
    cout << "|2 - �� ��������.               |" << endl;
    cout << "|0 - �����.                     |" << endl;
    cout << "|-------------------------------|" << endl;
}


void PrintMenuSortData(){
    cout << "\n|----------����������-----------|" << endl;
    cout << "|1 - �� ������.                 |" << endl;
    cout << "|2 - �� �������.                |" << endl;
    cout << "|3 - �� �����.                  |" << endl;
    cout << "|4 - �� ���� ��������.          |" << endl;
    cout << "|5 - �� ���� �����������.       |" << endl;
    cout << "|6 - �� �����.                  |" << endl;
    cout << "|7 - �� ������.                 |" << endl;
    cout << "|0 - �����.                     |" << endl;
    cout << "|-------------------------------|" << endl;
}



void PrintMenuChange(){
    cout << "\n1 - �� �������." << endl;
    cout << "2 - �� �����." << endl;
    cout << "3 - �� ���� ��������." << endl;
    cout << "4 - �� ���� �����������." << endl;
    cout << "5 - �� �����." << endl;
    cout << "6 - �� ������." << endl;
}




void PrintMenuWorkFiles(){
    cout << "\n|----------������ � �������------------|" << endl;
    cout << "|1 - ������� ������ � ��������� �����. |" << endl;
    cout << "|2 - ������� ������ � ���������� �����.|" << endl;
    cout << "|3 - ������� ������ � �������� ����.   |" << endl;
    cout << "|4 - ������� ������ � ��������� ����.  |" << endl;
    cout << "|0 - �����.                            |" << endl;
    cout << "|--------------------------------------|" << endl;
}






//���������� ��������
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
                cout << "������� ���-�� ��������� ��� ����������: " << endl;
                quanity = getCorrectInputNumber(1, 100000);
                addManyStud(students, number, quanity);
                break;
            case 0:
                break;
            default:
                cout << "����������� �������! ���������� �����." << endl;
        }
    }
    while(command != 0);
}



//������ � �������
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
                cout << "����������� �������! ���������� �����." << endl;
        }
    }
    while(command != 0);
}




//����� ���� ����������
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
                cout << "����������� �������! ���������� �����." << endl;
        }   
    }
    while(command != 0);
}





//���������� �� �����������
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
                cout << "����������� �������! ���������� �����." << endl;
        }
    }
    while(command != 0);
}




//���������� �� ��������
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
                cout << "����������� �������! ���������� �����." << endl;
        }
    }
    while(command != 0);
}





//���������� ������ � ���������� �����
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
                    cout << "\n��������� ����� ���������!";
                    break;
                }
            }
            cout << "\n������ ������� ������.";
        }
        else{
            cout << "��������� ����� ���������!\n������ ������� ������!";
        }
    }
    else{
        cout << "�� ������� ������� ����...";
    }
    fin.close();
}



//����� ������ � ��������� ����
void addToTxt(Student students[], int n){
    ofstream fout;
    fout.open("text.txt");
    if(fout.is_open()){
        cout << "���� ������!";
        for(int i = 0; i < n; i++){
            fout << students[i].surname << " ";
            fout << students[i].name << " ";
            fout << students[i].yearOfBirth << " ";
            fout << students[i].yearOfAdmission << " ";
            fout << students[i].course << " ";
            fout << students[i].groupe << "\n";
        }
        cout << "\n������ ������� �������� � ����.";
    }
    else{
        cout << "�� ������� ������� ����...";
    }
    fout.close();
}



//����� ������ � �������� ����
void addToBin(Student students[], int n){
    ofstream fout("binar.dat", ios::out | ios::binary);
    if(fout.is_open()){
        for(int i = 0; i < n; i++){
            fout.write((char*)&students[i], sizeof(Student));
        }
        cout << "������ ������� �������� � ����!";
    }
    else{
        cout << "�� ������� ������� ����!";
    }
    fout.close();
}



//���������� ������ � ��������� �����
void readingDataFromBin(Student students[], int& n){
    ifstream fin("binar.dat", ios::in | ios::binary);
    if(fin.is_open()) {
        if(n + 1 <= MAXSTUD){
            while(fin.read((char *)&students[n], sizeof(Student))) {
                students[n].studentn = n + 1;
                n++;
                if(n + 1 > MAXSTUD){
                    cout << "��������� ����� ���������!";
                    break;
                }
            }
            cout << "\n������ ������� �������!";
            }
        else{
            cout << "��������� ����� ���������!\n������ ������� ������!";
        }
    }
    else{
        cout << "�� ������� ������� ����...";
    }
    fin.close();
}




//���������� ������ ��������
void addOneStud(Student students[], int& n) {
    int yearOfBirth;
    if (n + 1 >= MAXSTUD) { 
    cout << "������� ������� �������� ���������!\n";
    return; 
    } 
        getCorrectSurname(students[n].surname);
        getCorrectName(students[n].name);
        cout << "������� ��� ��������:";
        students[n].yearOfBirth = getCorrectInputNumber(1900, 2007);
        cout << "������� ��� �����������:"; 
        students[n].yearOfAdmission = getCorrectInputNumber(1900, 2024);
        cout << "������� ����:"; 
        students[n].course = getCorrectInputNumber(1, 9); 
        getCorrectGroupe(students[n].groupe);
        cout << "������ � �������� ���������!\n";
        students[n].studentn = number + 1;
        n++; 
}

//���������� ���������� ���������
void addManyStud(Student students[], int& n, int quanity){
    if (n + quanity > MAXSTUD) {
        cout << "������� ������� ��������!\n";
        return;
    }
    for (int i = 0; i < quanity; i++){ 
        getCorrectSurname(students[n].surname);
        getCorrectName(students[n].name); 
        cout << "������� ��� ��������:"; 
        students[n].yearOfBirth = getCorrectInputNumber(1900, 2007);
        cout << "������� ��� �����������:"; 
        students[n].yearOfAdmission = getCorrectInputNumber(1900, 2024);
        cout << "������� ����:";
        students[n].course = getCorrectInputNumber(1, 9); 
        getCorrectGroupe(students[n].groupe);
        cout << "������ � �������� ���������!\n";
        students[n].studentn = n + 1;
        n++; 
    }
}


//�������������� ��������
void changeStud(Student students[], int n) {
    sortBubbleNumberIncreasing(students, n);
    if (n < 1) {
        cout << "������� �����. ��������� ����������." << endl;
        return;
    }

    int num;
    cout << "\n������� ���������� ����� �������� ��� ��������������: ";
    cin >> num;


    if (num < 1 || num > n) {
        cout << "������������ ����� ��������!" << endl;
        return;
    }

    
    PrintMenuChange();
    int field;
    cout << "�������� ���� ��� ���������: ";
    cin >> field;

    switch (field) {
        case 1:
            getCorrectSurname(students[num - 1].surname);
            break;
        case 2:
            getCorrectName(students[num - 1].name);
            break;
        case 3:
            cout << "������� ����� ��� ��������: ";
            students[num - 1].yearOfBirth = getCorrectInputNumber(1900, 2007);
            break;
        case 4:
            cout << "������� ����� ��� �����������: ";
            students[num - 1].yearOfAdmission = getCorrectInputNumber(1900, 2024);
            break;
        case 5:
            cout << "������� ����� ����: ";
            students[num - 1].course = getCorrectInputNumber(1, 9);
            break;
        case 6:
            cout << "������� ����� ������: ";
            getCorrectGroupe(students[num - 1].groupe);
            break;
        default:
            cout << "������������ ����� ����!" << endl;
            return;
    }

    cout << "������ �������� � ���������� ������� " << num << " ���������!" << endl;
    tableStud(students, n);
}



//�������� ���������
void deleteStud(Student students[], int& n){
    sortBubbleNumberIncreasing(students, n);
    int num;
    if(n < 1){
        cout << "������� �����. �������� ����������.";
        return;
    }
    while (true) {
        cout << "\n����� ��������:";
        cin >> num;
        if (cin.fail() || num < 1 || num > n) {
            cout << "������� �������� �������. ����������, ������� ����� �������� (�� 1 �� " << n << ") ";
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

    cout << "������� �����!";
    cout << "��������� �������\n";
    tableStud(students, number);
}




//���������� ������ �� �������
void printoutOnRequest(Student students[], int n){
    if (n < 1) {
        cout << "��� ��������� ��������� ��� ������." << endl;
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




//���������� ��������� (������) �� ��������
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



//���������� ��������� (�������) �� ��������
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


//���������� ��������� (���) �� ��������
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





//���������� ��������� (��� ��������) �� ��������
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



//���������� ��������� (��� �����������) �� ��������
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



//���������� ��������� (����) �� ��������
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




//���������� ��������� (������) �� ��������
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



//���������� ��������� (�����) �� �����������
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



//���������� ��������� (�������) �� �����������
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


//���������� ��������� (���) �� �����������
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



//���������� ��������� (��� ��������) �� �����������
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



//���������� ��������� (��� �����������) �� �����������
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



//���������� ��������� (����) �� �����������
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




//���������� ��������� (������) �� �����������
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







//������� ����������� ��� ���������� ������ �������
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



//�������
void tableStud(Student students[], int n) {
    cout << "-----------------------------------------------------------------------------------------------------------\n";
    cout << "| � |     �������        |       ���          |  ��� ��������  |  ��� �����������  | ���� |    ������     |\n";
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




//�������� �� ���� �����
void getCorrectName(char name[]){
    bool isNotOk{};
    char temp[100];

    do{
        isNotOk = false;
        cout << "������� ���:";
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
                cout << "������������ ����! ��� ������ ��������� ������ �����." << endl;
                isNotOk = true;
                break;
            }
        }
    }
    while(isNotOk);
}



//�������� �� ���� �������
void getCorrectSurname(char surname[]){
    bool isNotOk{};
    char temp[100];

    do{
        isNotOk = false;
        cout << "������� �������:";
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
                cout << "������������ ����! ������� ������ ��������� ������ �����." << endl;
                isNotOk = true;
                break;
            }
        }
    }
    while(isNotOk);
}




//�������� �� ���� ������
void getCorrectGroupe(char groupe[]){
    bool isNotOk{};
    char temp[100];

    do{
        isNotOk = false;
        cout << "������� ������:";
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
                cout << "������������ ����! ������� ����������� �������." << endl;
                isNotOk = true;
                break;
            }
        }
    }
    while(isNotOk);
}





//�������� �� ���� ����
int getCorrectInputNumber(int begin, int end){
    int n{};
    bool isNotOk{};
    do{
        isNotOk = false;
        if(((cin >> n).fail()) || (n < begin || n > end)){
            FixStreamState();
            cout << "������������ ����! ���������� �����." << endl;
            isNotOk = true;  
        }
    }
    while (isNotOk);

    return n;
}


//�������� �� ������������ �����
int GetCorrectValue(void PrintMenu()){
    int n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail()){
            FixStreamState();
            cout << "����������� ��������! ���������� �����." << endl;
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
            cout << "����������� ��������! ���������� �����." << endl;
            isNotOk = true;
        }
    }
    while (isNotOk);

    return n;
}