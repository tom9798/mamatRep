#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

#include "generic-string.h"
#include "string.h"



class StringArray{
    GenericString **array;
    int size;
public:
    StringArray(); //constructor
    StringArray(const StringArray &other); //copy constructor
    ~StringArray(); //destructor
    void insert(char *str); //insert string to array
    void trimArray() const; //trim each string in the array
    int getSize() const; //get array size
    GenericString *stringAtIndex(int index) const; //return a pointer to a GenericString object located in a given index
};

#endif