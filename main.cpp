#include <iostream>
#include <string>
#include <vector>
#include <limits>


using namespace std;

int GetCorrectValue();
void FixStreamState();


int main() {
    
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