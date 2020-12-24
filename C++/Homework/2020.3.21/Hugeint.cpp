/*
homework 10.8 Hugeint.cpp
*/
#include "Hugeint.h"
#include <cctype>
#include <iostream>
using namespace std;
HugeInt::HugeInt(long value) {
    if (value < 0) negative = 1;
    for (int i = 0; i < digits; i++)
        integer[i] = 0;
    for (int j = digits - 1; value != 0 && j >= 0; j--) {
        integer[j] = value % 10;
        value /= 10;
    }
}
HugeInt::HugeInt(const string &number) {
    string usenum = number;
    if (number[0] == '-') {
        negative = 1;
        usenum = number.substr(1);
    }
    for (int i = 0; i < digits; i++)
        integer[i] = 0;
    int length = usenum.size();

    for (int j = digits - length, k = 0; j < digits; j++, k++)
        if (isdigit(usenum[k])) integer[j] = usenum[k] - '0';
}
int HugeInt::getLength() const {
    int i = 0;
    while (i < digits && integer[i] != 0)
        i++;
    return digits - i;
}
HugeInt HugeInt::operator+(const HugeInt &HI2) const {
    HugeInt temp;
    if (HI2.negative + negative == 1) {
        HugeInt tem1 = *this;
        HugeInt tem2 = HI2;
        if (tem1.negative == 1) {
            tem1.negative = 0;
            temp = tem2 - tem1;
        } else {
            tem2.negative = 0;
            temp = tem1 - tem2;
        }
    } else {
        int carry = 0;
        for (int i = digits - 1; i >= 0; i--) {
            temp.integer[i] = integer[i] + HI2.integer[i] + carry;
            if (temp.integer[i] > 9) {
                temp.integer[i] %= 10;
                carry = 1;
            } else
                carry = 0;
        }
        temp.negative = HI2.negative;
    }
    return temp;
}
HugeInt HugeInt::operator+(int HI2) const {
    return *this + HugeInt(HI2);
}
bool HugeInt::operator==(const HugeInt &HI2) const {
    if (HI2.negative != negative) return false;
    for (int i = 0; i < digits; i++)
        if (HI2.integer[i] != integer[i]) return false;
    return true;
}
bool HugeInt::operator!=(const HugeInt &HI2) const {
    return !(*this == HI2);
}
bool HugeInt::operator<(const HugeInt &HI2) const {
    if (HI2.negative + negative == 1) {
        return negative == 1;
    } else if (HI2.negative + negative == 2) {
        for (int i = 0; i < digits; i++) {
            if (integer[i] == HI2.integer[i])
                continue;
            else if (integer[i] > HI2.integer[i])
                return true;
            else
                return false;
        }
    } else {
        for (int i = 0; i < digits; i++) {
            if (integer[i] == HI2.integer[i])
                continue;
            else if (integer[i] > HI2.integer[i])
                return false;
            else
                return true;
        }
    }
    return false;
}
bool HugeInt::operator<=(const HugeInt &HI2) const {
    return !(*this > HI2);
}
bool HugeInt::operator>(const HugeInt &HI2) const {
    return HI2 < *this;
}
bool HugeInt::operator>=(const HugeInt &HI2) const {
    return !(*this < HI2);
}
ostream &operator<<(ostream &output, const HugeInt &num) {
    int i = 0;
    while (i < HugeInt::digits && num.integer[i] == 0)
        i++;
    if (num.negative == 1 && (i != HugeInt::digits)) output << '-';
    if (i == HugeInt::digits)
        output << 0;
    else
        while (i < HugeInt::digits)
            output << num.integer[i++];
    return output;
}
HugeInt HugeInt::operator-(const HugeInt &HI2) const {
    if (HI2 > *this) {
        HugeInt ans = HI2 - *this;
        ans.negative = 1;
        return ans;
    }
    if (HI2.negative == 1) {
        if (this->negative == 1) {
            HugeInt tmp1 = *this;
            HugeInt tmp2 = HI2;
            tmp1.negative = 0;
            tmp2.negative = 0;
            return tmp2 - tmp1;
        } else {
            HugeInt tmp1 = *this;
            HugeInt tmp2 = HI2;
            tmp2.negative = 0;
            return tmp1 + tmp2;
        }
    }
    HugeInt ans("0");
    bool tag = false;
    for (int i = digits - 1; i >= 0; i--) {
        int thisvalue = this->integer[i];
        int decvalue = HI2.integer[i];
        if (tag) thisvalue--;
        tag = false;
        if (thisvalue >= decvalue)
            ans.integer[i] = thisvalue - decvalue;
        else {
            thisvalue += 10;
            tag = true;
            ans.integer[i] = thisvalue - decvalue;
        }
    }
    return ans;
}
HugeInt HugeInt::operator*(const HugeInt &HI2) const {
    int dep = 0;
    HugeInt total("0");
    HugeInt smaller = (*this < HI2) ? *this : HI2;
    HugeInt larger = (*this > HI2) ? *this : HI2;
    int x = 0;
    while (x < digits && larger.integer[x] == 0)
        x++;
    int head = x;
    for (int i = digits; i > digits - smaller.getLength(); i--) {
        HugeInt answer("0");
        int tail = i - 1;
        for (int j = digits; j > digits - larger.getLength(); j--) {
            int ans = dep + (larger.integer[j - 1] * smaller.integer[i - 1]);
            if (j - 1 == head) {
                dep = 0;
                answer.integer[tail] = ans % 10;
                tail -= 1;
                answer.integer[tail] = ans / 10;
                tail -= 1;
            } else {
                dep = ans / 10;
                answer.integer[tail] = ans % 10;
                tail -= 1;
            }
        }
        total = total + answer;
    }
    total.negative = (this->negative + HI2.negative) % 2;
    return total;
}
HugeInt HugeInt::operator/(const HugeInt &HI2) const {
    HugeInt last(*this);
    HugeInt calcul("0");
    HugeInt answer("0");
    HugeInt cal2 = HI2;
    cal2.negative = 0;
    int anslen = this->getLength();
    for (int i = digits - anslen; i < digits; i++) {
        calcul = calcul * HugeInt("10");
        calcul.integer[digits - 1] = last.integer[i];
        HugeInt ans("0");
        if (cal2 > calcul)
            answer.integer[i] = 0;
        else {
            int j;
            for (j = 1; j <= 10; j++) {
                HugeInt tempProduct = cal2 * HugeInt(j);
                if (tempProduct > calcul) break;
            }
            answer.integer[i] = j - 1;
            ans = cal2 * HugeInt(j - 1);
        }
        calcul = calcul - ans;
    }
    answer.negative = (this->negative + HI2.negative) % 2;
    return answer;
}
int main() {
    string s1, s2;
    cin >> s1 >> s2;
    HugeInt a, b;
    a = s1;
    b = s2;
    cout << a << "\n" << b << '\n';
    cout << a - b << '\n';
    cout << a + b << '\n';
    cout << a * b << '\n';
    cout << a / b << '\n';
    cout << (a > b) << '\n';
    cout << (a < b) << '\n';
    cout << (a == b) << '\n';
    cout << (a != b) << '\n';
    return 0;
}
// this is end
