/****************************************************************************************
* Alexis Lopez
* Vector.h
* 02/07/18
* This class is and implementation of a vector and its properties of copy vector, move
* set the size, capacity, check if is empty and many more. This lets the user to
* interact with vector and manipulate them.
****************************************************************************************/
#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

using namespace std;

template <class T>  
class Vector
{
public:

    typedef T * iterator;
 
    Vector(unsigned int size = 0, const T & initial = T()); // default constructor
    Vector(const Vector<T> & v);                            // copy constructor
    Vector(Vector<T> && v);                                 // move constructor
    ~Vector();                                              // destructor
    Vector<T> & operator=(const Vector<T> & v);             // copy assignment
    Vector<T> & operator=(Vector<T> && v);                  // move assignment
 
    unsigned int capacity() const;
    unsigned int size() const;   
    bool empty() const;
 
    iterator begin();                      // return iterator to first element
    iterator end();                        // return iterator to past last element
    T & front();                           // return reference to first element
    T & back();                            // return reference to last element
    void push_back(const T & value);
    void pop_back();               
 
    void reserve(unsigned int capacity);   // adjust capacity
    void resize(unsigned int size);        // adjust size
 
    T & operator[](unsigned int index);
    void erase(iterator);                  // erase elem iterator points to (shift left from iterator)
 
private:
    unsigned int my_size;
    unsigned int my_capacity;
    T * buffer;
};

// default constructor
template <class T>  
Vector<T>::Vector(unsigned int size, const T & initial)
{
    my_size = size;
    my_capacity = size;
    if (size == 0)
        buffer = nullptr;
    else {
        buffer = new T[size];
        assert(buffer != nullptr);
    }

    for (int i = 0; i < size; i++)
        buffer[i] = initial;
}

// copy constructor
template <class T>  
Vector<T>::Vector(const Vector<T> & v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T[my_capacity];
    assert(buffer != nullptr);

    for (int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];
}

// move constructor
template <class T>  
Vector<T>::Vector(Vector<T> && v): my_size{v.my_size}, my_capacity{v.my_capacity}, buffer{v.buffer}
{
    v.my_size = 0;
    v.my_capacity = 0;
    v.buffer = nullptr;
}

//destructor
template <class T>  
Vector<T>::~Vector()
{
    my_size = 0;
    my_capacity = 0;
    delete [] buffer;
}

// copy assignment
template <class T>  
Vector<T> & Vector<T>::operator=(const Vector<T> & v)
{
    T * temp = new T[v.my_capacity];
    assert(temp != nullptr);

    for (int i = 0; i < v.my_size; i++)
        temp[i] = v.buffer[i];

    delete [] buffer;
    buffer = temp;
    my_size = v.my_size;
    my_capacity = v.my_capacity;

    return *this;
}

// move assignment
template <class T>  
Vector<T> & Vector<T>::operator=(Vector<T> && v)
{
    my_size = v.my_size;
    v.my_size = 0;
    my_capacity = v.my_capacity;
    v.my_capacity = 0;
    delete [] buffer;
    buffer = v.buffer;
    v.buffer = 0;

    return *this;
}

//return the capacity value
template <class T>
unsigned int Vector<T>::capacity() const
{
    return my_capacity;
}

//return the size value
template <class T>
unsigned int Vector<T>::size() const
{
    return my_size;
}

//checks if is empty. If empty return 0 otherwhise 1
template <class T>
bool Vector<T>::empty() const
{
    return my_size == 0;
}

//return iterator to first element
template <class T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return &buffer[0];
}

//return iterator to past to last element
template <class T>
typename Vector<T>::iterator Vector<T>::end()
{
    return &buffer[my_size];
}

//return reference to first element
template <class T>
T & Vector<T>::front()
{
    return buffer[0];
}

//return reference to last element
template <class T>
T & Vector<T>::back()
{
    return buffer[my_size-1];
}

//adds an elemnt to the back of the vector
template <class T>
void Vector<T>::push_back(const T & value)
{
    if(my_size == my_capacity)
    {
        reserve(my_capacity+1);
    }
    buffer[my_size++] = value;
}

//removes the last element of the vector
template <class T>
void Vector<T>::pop_back()
{
    my_size--;
}

//reserves the capacity of the vector
template <class T>  
void Vector<T>::reserve(unsigned int capacity)
{
    if (capacity <= my_capacity)
        return;

    T * new_buffer = new T[capacity];
    assert(new_buffer != nullptr);

    my_capacity = capacity;
    int size;
    for (size = 0; size < my_size; size++)
        new_buffer[size] = buffer[size];

    delete [] buffer;
    buffer = new_buffer;
}

//sets the new size and capacity of the vector
template <class T>  
void Vector<T>::resize(unsigned int size)
{
    if (size > my_capacity)
        reserve(size*2);

    if (size > my_size)
        for (; my_size < size; my_size++)
            buffer[my_size] = T();
    else my_size = size;
}

//returns the value of the index on the vector
template <class T>
T & Vector<T>::operator[](unsigned int index)
{
    return buffer[index];
}

//erase element iteretor point to
template <class T>
void Vector<T>::erase(iterator)
{  
}

#endif
