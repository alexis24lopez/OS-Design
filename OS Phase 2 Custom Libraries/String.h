#ifndef STRING_H
#define STRING_H

/********************************************************************************************
Alexis Lopez
01/31/18
Revised: 11/5/2020
String.h

String class definition
*********************************************************************************************/

#include <iostream>
#include <cassert>

using namespace std;

class String
{
    int size;
    char * buffer;
public:
    String();               // default constructor
    String(const String &); // copy constructor
    String(String &&);      // move constructor
    String(const char *);
    String(char);
    ~String();              // destructor

    int length();
    char & operator[](const int);
    String & operator=(const String &); //copy assignment
    String & operator=(String &&);      //move assignment
    String & operator+=(const String &);
    String & operator+=(const char &);
    String operator+(const String &);
	
	
    int find(const String &) const;	// looks for input in string return -1 if not found.
    String substr(unsigned, unsigned);
    String substr(unsigned);
    const char * c_str() const;

    friend bool operator==(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator<(const String &, const String &);

    friend ostream & operator<<(ostream &, const String &);
    friend istream & operator>>(istream &, String &);
    friend istream & operator>>(istream &, const String &);
	
    friend istream & getline(istream &, String &);
    friend istream & getline(istream &, String &, char);
};

#endif
