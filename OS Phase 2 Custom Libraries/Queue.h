#ifndef QUEUE_H
#define QUEUE_H
/*****************************************************************************
* Alexis Lopez
* Queue.h  -- a queue implemented as an adapter (of vector or list or ..)
* This program allows the user to use Queues and to check if is empty
* the size, and to add element from the front and back. 
* and to remove from the front.
******************************************************************************/

#include "List.h"

template <class T, template <class Q> class Container = List>
class Queue
{
public:
    bool empty() const {return container.empty(); }
    unsigned int size() const {return container.size(); }
    T & front(){return container.front();} 
    T & back() {return container.back(); }
    void push (const T & z) {return container.push_back(z); }
    void push(T && z) {return container.push_back(move(z)); }
    void pop () {return container.pop_front(); }

protected:
    Container<T> container;
};

#endif
