#include "zoo.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    Zoo zoo;
    while (!zoo.is_close())
        zoo.run();
    zoo.fin();
}