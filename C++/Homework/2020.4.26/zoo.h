
#include <bits/stdc++.h>
using namespace std;

enum Food { peanuts, carrots, bananas };

class Money {
  public:
    Money(int, int);
    int get_in_cents() const;
    Money operator+(const Money &tmp) const;
    Money operator-(const Money &tmp) const;
    friend ostream &operator<<(ostream &cout, const Money &money);

  private:
    int dollars, cents;
};

class AnimalFood {
  public:
    AnimalFood(Food, int = 0);
    Food get_type() const;
    int get_num() const;
    void inc(int);
    void dec(int);

  private:
    Food Type;
    int num;
};

class AnimalEnclosure {
  public:
    bool is_open() const;
    int get_dirty() const;
    int get_close() const;
    void mess(int);
    void open();
    void clean();

  private:
    bool close;
    int dirty;
    int close_day;
};

class Animal : public AnimalEnclosure {
  public:
    void feed(int);

  private:
    int weight;
    int ate;
    int maxate;
};

class Elephant : public Animal {
  private:
    int trunk_length;
};

class Giraffe : public Animal {
  private:
    int neck_length;
};

class Monkey : public Animal {
  private:
    int arm_length;
};

class Person {
  private:
    string name;
    int age;
};

class ZooKeeper : public Person {
  public:
    void clean(Animal &);
    int get_work_days();
    bool work_enough() const;

  private:
    int work_days;
};

class FoodSeller : public Person {
  public:
    FoodSeller();
    Money get_income() const;
    int check_empty() const;
    AnimalFood sell_elephant_food(Money &, Money);
    AnimalFood sell_giraffe_food(Money &, Money);
    AnimalFood sell_monkey_food(Money &, Money);

  private:
    Money income;
    const int price[3] = {20, 30, 50};
    AnimalFood elephant_food;
    AnimalFood giraffe_food;
    AnimalFood monkey_food;
};

class Visitor : public Person {
  private:
    int id;
};

class Child : public Visitor {
  public:
    void recieve_food(AnimalFood);
    void feed_animal(Elephant *, Giraffe *, Monkey *);
    void feed_elephant(Elephant *, AnimalFood &);
    void feed_giraffe(Giraffe *, AnimalFood &);
    void feed_Monkey(Monkey *, AnimalFood &);

  private:
    vector<AnimalFood> animal_foods;
};

class Adult : public Visitor {
  public:
    Adult();
    int number_of_children() const;
    void spend_money(Money);
    void buy_food(FoodSeller *);
    void give_food(AnimalFood);
    void lead_to_feed(Elephant *, Giraffe *, Monkey *);

  private:
    Money money;
    vector<Child> children;
};

class Zoo {
  public:
    Zoo();
    bool is_close();
    void run();
    void fin();

  private:
    int days;
    string close_reason;
    int adult_total, child_total;
    bool close;
    Elephant elephant;
    Giraffe giraffe;
    Monkey monkey;
    ZooKeeper zookeeper;
    FoodSeller foodseller;
};