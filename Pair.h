#ifndef _PAIR_H_
#define _PAIR_H_

#include <iostream>
#include <string>

using namespace std;

template <class Item>
class Pair {
public:
    // default constructor
    Pair();

    // explicit-value constructor
    Pair(Item first, Item second);

    // getters
    Item getFirst() const;
    Item getSecond() const;

    // setters
    void setFirst(Item newVal);
    void setSecond(Item newVal);

    string toString() const;

    bool operator==(const Pair<Item> &other) const;

private:
    Item myFirst;
    Item mySecond;
};

// default constructor
template <class Item>
Pair<Item>::Pair() {
    myFirst = Item();
    mySecond = Item();
}

// explicit-value constructor
template <class Item>
Pair<Item>::Pair(Item first, Item second) {
    myFirst = first;
    mySecond = second;
}

template <class Item>
Item Pair<Item>::getFirst() const {
    return myFirst;
}

template <class Item>
Item Pair<Item>::getSecond() const {
    return mySecond;
}

template <class Item>
void Pair<Item>::setFirst(Item newVal) {
    myFirst = newVal;
}

template <class Item>
void Pair<Item>::setSecond(Item newVal) {
    mySecond = newVal;
}

template <class Item>
string Pair<Item>::toString() const {
    return "<" + to_string(myFirst) + ", " + to_string(mySecond) + ">";
}

template <class Item>
bool Pair<Item>::operator==(const Pair<Item> &other) const {
    return myFirst == other.myFirst && mySecond == other.mySecond;
}

template <class Item>
ostream &operator<<(ostream &out, const Pair<Item> &p) {
    out << p.toString();
    return out;
}


// template <class string>
// template <>
// string Pair<string>::toString() const {
    // return "<" + myFirst + ", " + mySecond + ">";
// }

#endif
