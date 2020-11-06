/***********************************************************************
Alexis Lopez
01/31/18
String.cpp

Implementation of constructors and member functions defined in String.h.
***********************************************************************/

#include <cassert>
#include "String.h"

//default constructor
String::String()
{
    size = 0;
    buffer = nullptr;
}

// copy constructor
String::String(const String & source)
{
    size = source.size;
    buffer = new char[size];
    assert(buffer != nullptr);

    for (int i = 0; i < size; i++)
        buffer[i] = source.buffer[i];
}

// move constructor
String::String(String && source): size{source.size}, buffer{source.buffer}
{
    source.size = 0;
    source.buffer = nullptr;
}

// constructor from "char string" to String
// find size of p, allocate space, assign p to buffer
String::String(const char * p)
{
    size = 0;
    for (const char *q = p; *q; q++)
        size++;
    buffer = new char[size];
    assert(buffer != nullptr);

    for (int i = 0; i < size; i++)
        buffer[i] = p[i];
}

String::String(char)
{

}

String::~String()
{
    delete [] buffer;
}

int String::length()
{
    return size;
}

char & String::operator[](const int i)
{
    return buffer[i];
}

// copy assignment
// similar to char string constructor, but here
// create a temp buffer based on source,
// delete existing buffer, then assign temp buffer to buffer
String & String::operator=(const String & source)
{
    char * temp = new char[source.size];
    assert(temp != nullptr);

    for (int i = 0; i < source.size; i++)
        temp[i] = source.buffer[i];

    delete [] buffer;
    buffer = temp;
    size = source.size;

    return *this;
}

// move assignment
String & String::operator=(String && source)
{
    size = source.size;
    source.size = 0;
    buffer = source.buffer;
    source.buffer = nullptr;
	
    return *this;
}

String & String::operator+=(const String  & arg)
{
    char * temp;
    int tempSize = size + arg.size;
    temp = new char[tempSize];
    int i;

    for (i = 0; i < size; i++)
    {
        temp[i] = buffer[i];
    }
    
    for(int p = 0; p < arg.size;p++, i++)
    {
        temp[i] = arg.buffer[p];
    }

    size = tempSize;
    delete [] buffer;
    buffer = temp;

    return * this;
}

String & String::operator+=(const char & arg)
{
    char * temp;
    int tempSize = size + 1;
    temp = new char[tempSize];
    int i;

    for (i = 0; i < size; i++)
    {
        temp[i] = buffer[i];
    }
    
    temp[i] = arg;


    size = tempSize;
    delete [] buffer;
    buffer = temp;

    return * this;
}

String String::operator+(const String & arg)
{
    char * temp;
    int tempSize = size + arg.size;
    temp = new char[tempSize];
    int i;

    for (i = 0; i < size; i++)
    {
        temp[i] = buffer[i];
    }
    
    for(int p = 0; p < arg.size;p++, i++)
    {
        temp[i] = arg.buffer[p];
    }
	
	temp[i] = '\0';

    //size = tempSize;
    //delete [] buffer;
    //buffer = temp;

    return temp;
	
	
}

/*String String::operator+(const String & lhs, const String & rhs)
{
	return String(lhs) += rhs;
}

String String::operator+(const String & lhs, char rhs)
{
	return String(lhs) += String(rhs);
}

String String::operator+(const String & lhs, const char * rhs)
{
	return String(lhs) += String(rhs);
}

String String::operator+(char lhs, const String & rhs)
{
	return String(lhs) += String(rhs);
}

String String::operator+(const char * lhs, const String & rhs)
{
	return String(lhs) += rhs;
}*/

int String::find(const String & arg) const
{
	for(int pos = 0; pos < size; pos++){
		for(int j = 0; j < arg.size; j++){
			if(buffer[pos] == arg.buffer[j]){
				return 	pos;
			}
		}
	}
	
	return -1;
}

String String::substr(unsigned pos, unsigned len)
{
	char * temp = new char[len + 1];
	assert(temp);
	int i = 0;
	for(; i < len && pos + i < size; i++){
		temp[i] = buffer[pos + i];
	}
	
	temp[i] = '\0';
	return temp;
}

String String::substr(unsigned pos)
{
	char * temp = new char[size + 1];
	assert(temp);
	int i = 0;
	for(; pos + i < size; i++){
		temp[i] = buffer[pos + i];
	}
	
	temp[i] = '\0';
	return temp;
}

const char * String::c_str() const
{
	char * temp = new char[size+1];
	int i;
	for(i =0; i< size; i++){
		temp[i] = buffer[i];
	}
	temp[i] = '\0';
	return temp;
}

bool operator==(const String & left, const String & right)
{
    if (left.size != right.size)
        return false;

    for (int i = 0; i < left.size; i++)
        if (left.buffer[i] != right.buffer[i])
            return false;
    return true;
}

bool operator<=(const String & left, const String & right)
{
    for (int i = 0; i < left.size & i < right.size; i++)
    {
        if (left.buffer[i] > right.buffer[i])
        {
            return false;
        }
    }
    return true;
}

bool operator<(const String & left, const String & right)
{
    for(int i = 0; i < left.size & i < right.size; i++)
    {
        if(left.size > right.size)
        {
            return false;
        }
    }

    for (int i = 0; i < left.size & i < right.size; i++)
    {
        if (left.buffer[i] > right.buffer[i])
        {
            return false;
        }
    }
    return true;
}

ostream & operator<<(ostream & out, const String & s)
{
    for (int i = 0; i < s.size; i++)
        out << s.buffer[i];
    return out;
}

istream & operator>>(istream & in, String & s)
{
    char * temp = new char[1000];
	in >> temp;
	s = String(temp);
	delete [] temp;
	
	return in;
}

istream & operator>>(istream & in, const String & s)
{
    char * temp = new char[1000];
	int i = 0;
	
	for(; in >> temp; i++){
		s.buffer[i] = temp[i];
	}
	delete [] temp;
	
	return in;
}

istream & getline(istream & in, String & s, char delim)
{
	char read;
	int i = 0;
	s = "";
	
	for(; in.get(read) && read != delim; i++){
		s += read;
	}
	
	return in;
}

istream & getline(istream & in, String & s)
{
	return getline(in, s, '\n');
}
