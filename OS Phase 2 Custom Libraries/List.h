/****************************************************************************************
* Alexis Lopez
* List.h
* 02/14/18
* This class is and implementation of a list and its properties of copy list, move,
* check the size, add or remove, check if is empty and many more. This lets the
* user to interact with List and manipulate them.
****************************************************************************************/
#ifndef LIST_H
#define LIST_H
#include<iostream>
using namespace std;

template <typename Object>
class List
{
    struct Node;

    int theSize;
    Node *head;
    Node *tail;

    void init();

public:
    class const_iterator;
    class iterator;

    List() { /*cout << "Default Constructor\n";*/ init(); }
    List(const List & rhs);
    List(List && rhs);
    ~List();
    List & operator=(const List & rhs);
    List & operator=(List && rhs);

    iterator begin() { return head->next; }
    const_iterator begin() const { return head->next; }
    iterator end() { return tail; }
    const_iterator end() const { return tail; }

    int size() const { return theSize; }
    bool empty() const { return theSize == 0; }

    void clear();

    Object & front() { return *begin(); }
    const Object & front() const { return *begin(); }
    Object & back() { return *--end(); }
    const Object & back() const { return *--end(); }

    void push_front(const Object & x) { insert(begin(), x); }
    void push_front(Object && x) { insert(begin(), move(x)); }
    void push_back(const Object & x) { insert(end(), x); }
    void push_back(Object && x) { insert(end(), move(x)); }

    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }

    iterator insert(iterator, const Object &);
    iterator insert(iterator, Object &&);

    iterator erase(iterator);
    iterator erase(iterator, iterator);
};

template <typename Object>
void List<Object>::init()
{
    theSize = 0;
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}

template <typename Object>
List<Object>::List(const List & rhs)
{
    init();
    for (auto & x: rhs)
        push_back(x);
}

template <typename Object>
List<Object>::List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <typename Object>
List<Object>::~List()
{
    clear();
    delete head;
    delete tail;
}

template <typename Object>
List<Object> & List<Object>::operator=(const List & rhs)
{
    List copy = rhs;
    swap(*this, copy);
    return *this;
}
template <typename Object>
List<Object> & List<Object>::operator=(List && rhs)
{
    swap(theSize, rhs.theSize);
    swap(head, rhs.head);
    swap(tail, rhs.tail);

    return *this;
}

template <typename Object>
void List<Object>::clear()
{
    while(!empty())
    {
        pop_front();
    }
}

template <typename Object>
typename List<Object>::iterator List<Object>::insert(iterator itr, const Object & x)
{
    Node *p = itr.current;
    theSize++;
    return p->prev = p->prev->next = new Node{x, p->prev, p};
}

template <typename Object>
typename List<Object>::iterator List<Object>::insert(iterator itr, Object && z)
{
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{move(z), p->prev,p}};
}

template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator itr)
{
    Node *p = itr.current;
    iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;

    return retVal;
}

template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator start, iterator end)
{
    for(iterator itr = start; itr != end;)
    {
        itr = erase(itr);
    }
    return end;
}    

//******************************** Node
template <typename Object>
struct List<Object>::Node
{
    Object data;
    Node *prev;
    Node *next;

    Node(const Object & d = Object{}, Node * p = nullptr, Node * n = nullptr):
        data{d}, prev{p}, next{n} { }

    Node(Object && d, Node * p = nullptr, Node * n = nullptr):
        data{move(d)}, prev{p}, next{n} { }
};


//******************************** const_iterator
template <typename Object>
class List<Object>::const_iterator
{
public:
    const_iterator(): current{nullptr} { }
    const Object & operator*() const { return retrieve(); }

    const_iterator & operator++();
    const_iterator operator++(int);    

    const_iterator & operator--();  // not in textbook
    const_iterator operator--(int); // not in textbook

    bool operator==(const const_iterator & rhs) const { return current == rhs.current; }
    bool operator!=(const const_iterator & rhs) const { return current != rhs.current; }

protected:
    Node *current;

    Object & retrieve() const { return current->data; }
    const_iterator(Node *p): current{p} { }

    friend class List<Object>;
};

template <typename Object>
typename List<Object>::const_iterator & List<Object>::const_iterator::operator++()
{
    current = current->next;
    return *this;
}

template <typename Object>
typename List<Object>::const_iterator List<Object>::const_iterator::operator++(int)
{
    const_iterator old = *this
    ++(*this);
    return old;
}

template <typename Object>
typename List<Object>::const_iterator & List<Object>::const_iterator::operator--()
{
    current = current->prev;
    return *this;
}

template <typename Object>
typename List<Object>::const_iterator List<Object>::const_iterator::operator--(int)
{
    const_iterator old = *this
    --(*this);
    return old;
}

//******************************** iterator
template <typename Object>
class List<Object>::iterator: public List<Object>::const_iterator
{
public:
    iterator() { }
    Object & operator*() { return List<Object>::const_iterator::retrieve(); }              // mutator
    const Object & operator*() const { return List<Object>::const_iterator::operator*(); } // accessor

    iterator & operator++();
    iterator operator++(int);    

    iterator & operator--();
    iterator operator--(int);    

protected:
    iterator(Node *p): List<Object>::const_iterator{p} { }
    friend class List<Object>;
};

template <typename Object>
typename List<Object>::iterator & List<Object>::iterator::operator++()
{
    this->current = this->current->next; // must use "this" pointer for protected members
    return *this;
}

template <typename Object>
typename List<Object>::iterator List<Object>::iterator::operator++(int)
{
    iterator old = *this;
    ++(*this);
    return old;
}

template <typename Object>
typename List<Object>::iterator & List<Object>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
}

template <typename Object>
typename List<Object>::iterator List<Object>::iterator::operator--(int)
{
    iterator old = *this;
    --(*this);
    return old;
}

#endif
