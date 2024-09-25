#include <iostream>
#include <limits>
#include <windows.h>
using namespace std;

// переприсваиваем значение max из windows.h в limits
#ifdef max
#undef max
#endif


HANDLE hConsoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csb;

// функция представления целого числа в памяти
void findint(int num) {
    unsigned int order = 32;
    unsigned int mask = 1 << order - 1;
    for (int i = 1; i <= order; i++)
    {
        putchar(num & mask ? '1' : '0');
        mask >>= 1;
        if (i == 1)
        {
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
            putchar(' ');
        }
        if (i % 8 == 0)
        {
            putchar(' ');
        }
    }
}

// функция представления вещественного(float) числа в памяти
void findfloat(float num) {
    union {
        float num1;
        int cur_int_num;
    } crt;
    crt.num1 = num;
    unsigned int order = 32;
    unsigned int mask = 1 << order - 1;
    for (int i = 1; i <= order; i++)
    {
        putchar(crt.cur_int_num & mask ? '1' : '0');
        mask >>= 1;
        if (order - i == 23)
        {
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
            putchar(' ');
        }
        if (order - i == order - 1) {
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
            putchar(' ');
        }
    }
}

// функция представления вещественного(double) числа в памяти
void finddouble(double num)
{
    union
    {
        double cur_num;
        int binary[2];
    } crt;
    crt.cur_num = num;
    char cur_ans[64];
    unsigned int order = 32;
    unsigned int mask = 1;
    int count = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < order; j++)
        {
            cur_ans[count] = crt.binary[i] & mask ? '1' : '0';
            mask <<= 1;
            count++;
        }
        mask = 1;
    }
    for (int k = 63; k >= 0; k--) {
        putchar(cur_ans[k]);
        if (order * 2 - k == 1) {
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
            putchar(' ');
        }
        if (order * 2 - k == 11) {
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
            putchar(' ');
        }
    }
}



int main() {
    ::GetConsoleScreenBufferInfo(hConsoleOutput, &csb);
    int num2;
    float num3;
    double num4;
    cout << "First task: " << sizeof(int) << " " << sizeof(short int) << " " << sizeof(long int) << " " << sizeof(float) << " " << sizeof(double) << " " << sizeof(long double) << " " << sizeof(char) << " " << sizeof(bool) << endl;
    cout << "Second task(input int data, to quit type 0): ";
    cin >> num2;
    // проверка на правильность ввода
    while (num2 != 0 || cin.fail()) {
        if (cin.fail() || isalpha(cin.peek()))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not int number. Try again: ";
        }
        else
        {
            cout << "white - sign bit, ";
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
            cout << "blue - discharge bit " << endl;
            ::SetConsoleTextAttribute(hConsoleOutput, csb.wAttributes);
            findint(num2);
            ::SetConsoleTextAttribute(hConsoleOutput, csb.wAttributes);
            cout << endl;
            cout << "Try new numbers(To quit type 0): ";
        }
        cin >> num2;
    }
    cout << "Third task(input float data, to quit type 0): ";
    cin >> num3;
    // проверка на правильность ввода
    while (num3 != 0 || cin.fail()){
        if (cin.fail() || isalpha(cin.peek()))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not float number. Try again: ";
        }
        else
        {
            cout << "white - sign bit, ";
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
            cout << "red - exponent bit,  ";
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
            cout << "blue - mantisa bit" << endl;
            ::SetConsoleTextAttribute(hConsoleOutput, csb.wAttributes);
            findfloat(num3);
            ::SetConsoleTextAttribute(hConsoleOutput, csb.wAttributes);
            cout << endl;
            cout << "Try new numbers(To quit type 0): ";
        }
        cin >> num3;
    }
    cout << "Fourth task(input double data, to quit type 0): ";
    cin >> num4;
    // проверка на правильность ввода
    while (num4 != 0 || cin.fail()) {
        if (cin.fail() || isalpha(cin.peek()))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not double number. Try again: ";
        }
        else
        {
            cout << "white - sign bit, ";
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
            cout << "red - exponent bit,  ";
            ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
            cout << "blue - mantisa bit" << endl;
            ::SetConsoleTextAttribute(hConsoleOutput, csb.wAttributes);
            finddouble(num4);
            cout << endl;
            ::SetConsoleTextAttribute(hConsoleOutput, csb.wAttributes);
            cout << "Try new numbers(To quit type 0): ";
        }
        cin >> num4;
    }
    system("PAUSE");
    return 0;
}
