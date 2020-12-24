/*
homework 13.17 Ascii.cpp
*/
#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    cout << setw(8) << "Decimal " << setw(9) << "Octal " << setw(15)
         << "Hexadecimal " << setw(14) << "Character " << showbase << '\n';
    for (int loop = 33; loop <= 126; loop++)
        cout << setw(7) << dec << loop << setw(9) << oct << loop << setw(15)
             << hex << loop << setw(14) << static_cast<char>(loop) << endl;
}
// this is end
