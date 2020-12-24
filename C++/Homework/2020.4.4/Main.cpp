/*
 * assignment2 Main.cpp
 */
#include "Library.h"
#include <iostream>

int main() {
    Library library;
    int tot;
    cin >> tot;
    cin.get();
    for (int i = 0; i < tot; i++)
        library.add_borrower();
    library.show_books_on_loan();
    library.show_borrowers();
}
// this is end
