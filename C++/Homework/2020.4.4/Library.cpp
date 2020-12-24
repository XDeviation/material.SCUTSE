/*
 * assignment2 Library.cpp
 */
#include "Library.h"
#include <bits/stdc++.h>
using namespace std;

Borrower::Borrower(const vector<string> &v)
    : borrower_id(stoi(v[0]))
    , first_name(split(v[1], " ")[0])
    , last_name(split(v[1], " ")[1])
    , number_of_books_loaned(stoi(v[2])) {
    if (v[0].length() != 5)
        throw invalid_argument(
            "Error: the borrower's ID should consists of 5 digits");
    if (number_of_books_loaned > 5)
        throw invalid_argument("Error: more than 5 books");
    for (int i = 0; i < number_of_books_loaned; i++)
        book_ids.push_back(v[3 + i]);
}

Borrower::~Borrower() = default;

void Borrower::displays() const {
    cout << "Borrower ID: " << borrower_id << "\nName: " << first_name << ' '
         << last_name << "\nNumber of loaned books: " << number_of_books_loaned
         << "\nIDs of books on loan: ";
    for (auto &it : book_ids) {
        cout << it << ' ';
    }
    cout << '\n';
}

vector<string> Borrower::get_loaned_books() const {
    return book_ids;
}

BookRecord::BookRecord(const vector<string> &v)
    : book_id(v[0])
    , book_title(v[1])
    , first_name(split(v[2], " ")[0])
    , last_name(split(v[2], " ")[1])
    , year_published(stoi(v[3]))
    , number_of_copies(stoi(v[4]))
    , number_of_copies_available(number_of_copies) {
    if (book_id[0] < 'A' || book_id[0] > 'Z')
        throw invalid_argument(
            "Error: book ID should start with an uppercase letter");
    if (year_published < 1000 || year_published > 3000)
        throw invalid_argument("Error: the year of publication should has 4 "
                               "digits and starts with a 1 or a 2 ");
}

BookRecord::~BookRecord() = default;

string BookRecord::get_book_id() const {
    return book_id;
}

void BookRecord::displays() const {
    cout << "Book ID: " << book_id << "\nTitle: " << book_title
         << "\nAuthor: " << first_name << ' ' << last_name
         << "\nYear published: " << year_published
         << "\nTotal number of copies: " << number_of_copies
         << "\nNumber available for loan: " << number_of_copies_available
         << '\n';
}

int BookRecord::get_number() const {
    return number_of_copies;
}

int BookRecord::get_number_can_loan() const {
    return number_of_copies_available;
}

void BookRecord::loan() {
    if (number_of_copies_available)
        number_of_copies_available--;
    else
        throw invalid_argument("Error: no book");
}

Catalogue::Catalogue()
    : total_books(0) {
}

Catalogue::~Catalogue() = default;

void Catalogue::displays() const {
    int tot = 0;
    for (auto &book : book_records) {
        cout << "Book Record " << tot++ << "\n=============\n";
        book.displays();
    }
}

void Catalogue::add_book(BookRecord book) {
    total_books++;
    book_records.push_back(book);
}

void Catalogue::loan_book(string str) {
    for (auto &book : book_records)
        if (book.get_book_id() == str) {
            book.loan();
            return;
        }
}

int Catalogue::get_loan_num() const {
    int ans = 0;
    for (auto &book : book_records)
        ans += book.get_number() - book.get_number_can_loan();
    return ans;
}

int Catalogue::get_free_num() const {
    int ans = 0;
    for (auto &book : book_records)
        ans += book.get_number_can_loan();
    return ans;
}

Library::Library()
    : borrowers_total(0)
    , catalogue(Catalogue()) {
    int tot;
    cin >> tot;
    cin.get();
    for (int i = 0; i < tot; i++)
        add_book();
    books_total = catalogue.get_free_num();
}

Library::~Library() = default;

void Library::show_books_on_loan() const {
    cout << "Total number of books on loan: " << catalogue.get_loan_num()
         << "\nTotal number of books in catalogue: " << catalogue.get_free_num()
         << '\n';
    catalogue.displays();
}

void Library::show_borrowers() const {
    cout << "Total number of borrowers: " << borrowers_total << '\n';
    int tot = 0;
    for (auto borrower : borrowers) {
        cout << "Borrower " << tot++ << "\n=============\n";
        borrower.displays();
    }
}

void Library::add_book() {
    string str;
    getline(cin, str);
    auto t = split(str, ";");
    BookRecord book(t);
    catalogue.add_book(book);
}

void Library::loan_book(string str) {
    catalogue.loan_book(str);
}

void Library::add_borrower() {
    string str;
    getline(cin, str);
    borrowers_total++;
    borrowers.push_back(split(str, ";"));
    for (auto book : borrowers.back().get_loaned_books()) {
        loan_book(book);
    }
}

vector<string> split(string str, const string &delimiters) {
    regex del(delimiters);
    vector<string> v(sregex_token_iterator(str.begin(), str.end(), del, -1),
                     sregex_token_iterator());
    return v;
}
// this is end
