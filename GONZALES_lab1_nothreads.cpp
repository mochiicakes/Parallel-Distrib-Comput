#include <iostream>

using namespace std;

void FirstWord() {
    cout << "I";
}

void SecondWord() {
    cout << "GOT";
}

void ThirdWord() {
    cout << "NOBODY";
}

void FourthWord() {
    cout << "BUT";
}

void FifthWord() {
    cout << "YOU";
}

int main()
{
    int i, k;

    for (i = 0; i < 1000; i++) {
        FirstWord();
        cout << " ";
        SecondWord();
        cout << " ";
        ThirdWord();
        cout << " ";
        FourthWord();
        cout << " ";
        FifthWord();
        cout << " ";
    }

    return 0;
}


