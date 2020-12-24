/*
 * assignment2 Library.h
 */
#include <string>
#include <vector>
using namespace std;

class Borrower {
  private:
    int borrower_id;
    string first_name;
    string last_name;
    int number_of_books_loaned;
    vector<string> book_ids;

  public:
    Borrower(const vector<string> &);
    ~Borrower();
    void displays() const;
    vector<string> get_loaned_books() const;
};

class BookRecord {
  private:
    string book_id;
    string book_title;
    string first_name;
    string last_name;
    int year_published;
    int number_of_copies;
    int number_of_copies_available;

  public:
    BookRecord(const vector<string> &);
    ~BookRecord();
    string get_book_id() const;
    void displays() const;
    int get_number() const;
    int get_number_can_loan() const;
    void loan();
};

class Catalogue {
  private:
    int total_books;
    vector<BookRecord> book_records;

  public:
    Catalogue();
    ~Catalogue();
    void displays() const;
    void add_book(BookRecord);
    void loan_book(string);
    int get_loan_num() const;
    int get_free_num() const;
};

class Library {
  private:
    int books_total;
    int borrowers_total;
    Catalogue catalogue;
    vector<Borrower> borrowers;

  public:
    Library();
    ~Library();
    void show_books_on_loan() const;
    void show_borrowers() const;
    void add_book();
    void loan_book(string);
    void add_borrower();
};

vector<string> split(string str, const string &delimiters);
// this is end
