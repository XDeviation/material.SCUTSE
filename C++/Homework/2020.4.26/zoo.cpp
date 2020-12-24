#include "zoo.h"
#include <bits/stdc++.h>
using namespace std;

Money::Money(int dollar, int cent) {
    cent += dollar * 100;
    dollars = cent / 100;
    cents = cent % 100;
}

ostream &operator<<(ostream &cout, const Money &money) {
    if (money.dollars > 0) cout << money.dollars << " dollar";
    if (money.dollars > 1) cout << 's';
    cout << ' ';
    cout << money.cents << " cent";
    if (money.cents > 1) cout << 's';
    return cout;
}

int Money::get_in_cents() const {
    return cents + 100 * dollars;
}

Money Money::operator+(const Money &tmp) const {
    return Money(0, dollars * 100 + cents + tmp.dollars * 100 + tmp.cents);
}

Money Money::operator-(const Money &tmp) const {
    return Money(0, dollars * 100 + cents - tmp.dollars * 100 - tmp.cents);
}

AnimalFood::AnimalFood(Food food, int val) {
    Type = food;
    num = val;
}

Food AnimalFood::get_type() const {
    return Type;
}

int AnimalFood::get_num() const {
    return num;
}

void AnimalFood::inc(int val) {
    num += val;
}

void AnimalFood::dec(int val) {
    num -= val;
}

bool AnimalEnclosure::is_open() const {
    return !close;
}

int AnimalEnclosure::get_dirty() const {
    return dirty;
}

int AnimalEnclosure::get_close() const {
    return close_day;
}

void AnimalEnclosure::mess(int val) {
    dirty += val;
}

void AnimalEnclosure::open() {
    close = false;
}

void AnimalEnclosure::clean() {
    dirty = 0;
    close = true;
    close_day++;
}

void Animal::feed(int val) {
    ate += val;
    if (ate > maxate) mess(ate - maxate);
    ate = min(ate, maxate);
}

void ZooKeeper::clean(Animal &animal) {
    work_days++;
    animal.clean();
}

int ZooKeeper::get_work_days() {
    return work_days;
}

bool ZooKeeper::work_enough() const {
    return work_days == 10;
}

FoodSeller::FoodSeller()
    : income(Money(0, 0))
    , elephant_food(AnimalFood(peanuts, 10000))
    , giraffe_food(AnimalFood(carrots, 7000))
    , monkey_food(AnimalFood(bananas, 4000)) {
}

Money FoodSeller::get_income() const {
    return income;
}

int FoodSeller::check_empty() const {
    if (elephant_food.get_num() == 0) return 1;
    if (giraffe_food.get_num() == 0) return 2;
    if (monkey_food.get_num() == 0) return 3;
    return 0;
}

AnimalFood FoodSeller::sell_elephant_food(Money &money, Money max_spend) {
    int cnt = min(elephant_food.get_num(), max_spend.get_in_cents() / price[0]);
    money = money - Money(0, price[0] * cnt);
    income = income + Money(0, price[0] * cnt);
    elephant_food.dec(cnt);
    return AnimalFood(peanuts, cnt);
}

AnimalFood FoodSeller::sell_giraffe_food(Money &money, Money max_spend) {
    int cnt = min(giraffe_food.get_num(), max_spend.get_in_cents() / price[1]);
    money = money - Money(0, price[1] * cnt);
    income = income + Money(0, price[1] * cnt);
    giraffe_food.dec(cnt);
    return AnimalFood(carrots, cnt);
}

AnimalFood FoodSeller::sell_monkey_food(Money &money, Money max_spend) {
    int cnt = min(monkey_food.get_num(), max_spend.get_in_cents() / price[2]);
    money = money - Money(0, price[2] * cnt);
    income = income + Money(0, price[2] * cnt);
    monkey_food.dec(cnt);
    return AnimalFood(bananas, cnt);
}

void Child::recieve_food(AnimalFood animalfood) {
    animal_foods.push_back(animalfood);
}

void Child::feed_animal(Elephant *ele, Giraffe *gir, Monkey *mon) {
    for (auto animalfood : animal_foods) {
        if (animalfood.get_type() == peanuts) feed_elephant(ele, animalfood);
        if (animalfood.get_type() == carrots) feed_giraffe(gir, animalfood);
        if (animalfood.get_type() == bananas) feed_Monkey(mon, animalfood);
    }
}

void Child::feed_elephant(Elephant *ele, AnimalFood &animalfood) {
    if (ele->is_open()) ele->feed(animalfood.get_num());
}

void Child::feed_giraffe(Giraffe *gir, AnimalFood &animalfood) {
    if (gir->is_open()) gir->feed(animalfood.get_num());
}

void Child::feed_Monkey(Monkey *mon, AnimalFood &animalfood) {
    if (mon->is_open()) mon->feed(animalfood.get_num());
}

Adult::Adult()
    : money(Money(0, 0)) {
    int child_num = rand() % 3 + 1;
    money = Money(rand() % 9 + 10, -child_num * 40);
    for (int i = 0; i < child_num; i++)
        children.push_back(Child());
}

int Adult::number_of_children() const {
    return children.size();
}

void Adult::spend_money(Money spend) {
    money = money - spend;
}

void Adult::buy_food(FoodSeller *foodseller) {
    int tmp = money.get_in_cents() / 3;
    give_food(foodseller->sell_elephant_food(money, Money(0, tmp)));
    give_food(foodseller->sell_giraffe_food(money, Money(0, tmp)));
    give_food(foodseller->sell_monkey_food(money, Money(0, tmp)));
}

void Adult::give_food(AnimalFood animalfood) {
    int give = animalfood.get_num() / (children.size());
    for (int i = children.size() - 1; i >= 0; i--)
        children[i].recieve_food(AnimalFood(animalfood.get_type(), give));
}

void Adult::lead_to_feed(Elephant *ele, Giraffe *gir, Monkey *mon) {
    for (auto &child : children)
        child.feed_animal(ele, gir, mon);
}

Zoo::Zoo()
    : days(0)
    , close_reason("")
    , adult_total(0)
    , child_total(0)
    , close(false)
    , elephant(Elephant())
    , giraffe(Giraffe())
    , monkey(Monkey())
    , zookeeper(ZooKeeper())
    , foodseller(FoodSeller()) {
}

bool Zoo::is_close() {
    return close;
}

void Zoo::run() {
    days++;
    int number_adult = rand() % (40 - 20 + 1) + 20;
    for (int i = 0; i < number_adult; i++) {
        Adult adult;
        adult_total++;
        child_total += adult.number_of_children();
        adult.buy_food(&foodseller);
        adult.lead_to_feed(&elephant, &giraffe, &monkey);
    }

    elephant.open();
    giraffe.open();
    monkey.open();
    if (elephant.get_dirty() > 2000)
        elephant.clean();
    else if (giraffe.get_dirty() > 2000)
        giraffe.clean();
    else if (monkey.get_dirty() > 2000)
        monkey.clean();
    if (foodseller.check_empty()) {
        if (foodseller.check_empty() == 1)
            close_reason = "The zoo closed because the seller ran out of "
                           "peanuts.";
        if (foodseller.check_empty() == 2)
            close_reason =
                "The zoo closed because the seller ran out of carrots.";
        if (foodseller.check_empty() == 3)
            close_reason =
                "The zoo closed because the seller ran out of bananas.";
    }
    if (zookeeper.work_enough())
        close_reason = "The zoo closed because the zoo keeper had enough of "
                       "cleaning and quit!";

    if (close_reason != "") close = true;
}

void Zoo::fin() {
    cout << "open days: " << days << "\n";
    cout << close_reason << "\n";
    cout << "total adult: " << adult_total << "\n";
    cout << "total child: " << child_total << "\n";
    cout << "total income: " << foodseller.get_income() << "\n";
    cout << "total clean: " << zookeeper.get_work_days() << "\n";
    cout << "elephant close: " << elephant.get_close() << "\n";
    cout << "giraffe close: " << giraffe.get_close() << "\n";
    cout << "monkey close: " << monkey.get_close() << "\n";
}
