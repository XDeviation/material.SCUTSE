/*
homework 14.12 PhoneNumber.cpp
*/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
int main() {
    int n[7] = {0};
    for (int v = 0; v < 7;) {
        int i = std::cin.get();
        if (i >= '2' && i <= '9') n[v++] = i - '0';
    }
    std::ofstream cout("phone.txt");
    const std::string s[10] = {"",    "",    "ABC", "DEF", "GHI",
                               "JKL", "MNO", "PRS", "TUV", "WXY"};
    int count = 0;
    for (int i1 = 0; i1 <= 2; i1++) {
        for (int i2 = 0; i2 <= 2; i2++) {
            for (int i3 = 0; i3 <= 2; i3++) {
                for (int i4 = 0; i4 <= 2; i4++) {
                    for (int i5 = 0; i5 <= 2; i5++) {
                        for (int i6 = 0; i6 <= 2; i6++) {
                            for (int i7 = 0; i7 <= 2; i7++) {
                                cout << s[n[0]][i1] << s[n[1]][i2]
                                     << s[n[2]][i3] << s[n[3]][i4]
                                     << s[n[4]][i5] << s[n[5]][i6]
                                     << s[n[6]][i7] << ' ';
                                if (++count % 9 == 0) cout << '\n';
                            }
                        }
                    }
                }
            }
        }
    }
}
// this is end
