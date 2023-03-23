#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include <stdexcept>
using namespace std;

template <class Item>
class Queue {
public:
    Queue();
    Queue(const Queue<Item> &original);
    virtual ~Queue();
    unsigned getSize() const { return mySize; }
    void add(const Item &it);
    Item remove();

    Item getFirst() const;
    Item getLast() const;
    void writeTo(ostream &out) const;
    int getIndexOf(const Item &it) const;
    bool contains(const Item &it) const;
    bool operator==(const Queue<Item> &rhs) const;

private:
    struct Node {
        Node();
        Node(Item it, Node *next);
        virtual ~Node();
        Item myItem;
        Node *myNext;
    };
    void append(const Item &it);
    unsigned mySize;
    Node *myFirst;
    Node *myLast;

public:
    class iterator {
    public:
        iterator(typename Queue<Item>::Node *c) : current(c) {}

        bool operator!=(const iterator &it) const {
            return this->current != it.current;
        }

        // value-at operator overload -- const and non-const
        Item const &operator*() const { return current->myItem; }
        Item &operator*() { return current->myItem; }
        // arrow operator overload
        Item *operator->() { return &(current->myItem); }

        // pre-increment
        iterator &operator++() {
            current = current->myNext;
            return *this;
        }
        // post-increment
        iterator operator++(int) {
            iterator clone(*this);
            current = current->myNext;
            return clone;
        }

    private:
        typename Queue<Item>::Node *current;  // current node we are iterating over.
    };  // end of inner-class "iterator"

    iterator begin() { return iterator(myFirst); }
    iterator end() { return iterator(nullptr); }
};

template <class Item>
Queue<Item>::Queue() {
    mySize = 0;
    myFirst = myLast = nullptr;
}

// copy constructor
template <class Item>
Queue<Item>::Queue(const Queue<Item> &original) {
    myFirst = myLast = nullptr;
    mySize = 0;
    // do a deep copy
    for (Node *curr = original.myFirst; curr; curr = curr->myNext) {
        append(curr->myItem);
    }
    mySize = original.mySize;
}

template <class Item>
Queue<Item>::~Queue() {
    mySize = 0;
    delete myFirst;
    myFirst = myLast = nullptr;
}

template <class Item>
Queue<Item>::Node::Node() {
    myItem = Item();
    myNext = nullptr;
}

template <class Item>
Queue<Item>::Node::Node(Item it, Node *next) {
    myItem = it;
    myNext = next;
}

template <class Item>
Queue<Item>::Node::~Node() {
    delete myNext;
    myNext = nullptr;
}

template <class Item>
Item Queue<Item>::getFirst() const {
    if (mySize == 0) {
        throw underflow_error("Queue is empty");
    }
    return myFirst->myItem;
}

template <class Item>
Item Queue<Item>::getLast() const {
    if (mySize == 0) {
        throw underflow_error("Queue is empty");
    }
    return myLast->myItem;
}

template <class Item>
void Queue<Item>::add(const Item &it) {
    append(it);
}

// removes from the beginning of the queue.
template <class Item>
Item Queue<Item>::remove() {
    if (mySize == 0) {
        throw underflow_error("Queue is empty");
    }
    Item ret = myFirst->myItem;
    Node *tmp = myFirst;
    myFirst = myFirst->myNext;
    tmp->myNext = nullptr;
    delete tmp;
    if (myFirst == nullptr) {
        myLast = nullptr;
    }
    mySize--;
    return ret;
}

template <class Item>
void Queue<Item>::append(const Item &it) {
    Node *newNode = new Node(it, nullptr);
    if (mySize == 0) {
        myFirst = newNode;
    } else {
        myLast->myNext = newNode;
    }
    myLast = newNode;
    mySize++;
}

template <class Item>
void Queue<Item>::writeTo(ostream &out) const {
    for (Node *curr = myFirst; curr != nullptr; curr = curr->myNext) {
        out << curr->myItem << " ";
    }
}

template <class Item>
int Queue<Item>::getIndexOf(const Item &it) const {
    int i = 0;
    for (Node *curr = myFirst; curr != nullptr; curr = curr->myNext) {
        if (curr->myItem == it) {
            return i;
        }
        i++;
    }
    return -1;
}

template <class Item>
bool Queue<Item>::operator==(const Queue<Item> &rhs) const {
    if (mySize != rhs.mySize) {
        return false;
    }
    Node *myCurr = myFirst;
    Node *rhsCurr = rhs.myFirst;
    while (myCurr) {
        if (myCurr->myItem != rhsCurr->myItem) {
            return false;
        }
        myCurr = myCurr->myNext;
        rhsCurr = rhsCurr->myNext;
    }
    return true;
}

template <class Item>
bool Queue<Item>::contains(const Item &it) const {
    return getIndexOf(it) != -1;
}

#endif /* Queue_H_ */
