#ifndef STRINGARRAY_H
#define STRINGARRAY_H


#include "generic-string.h"
#inlcude "string.h"

//this class will maintain an array of GenericString object pointers, made up of the words in the original string
class StringArray {
    int size;
    GenericString **array;
public:
    StringArray(); // constructor
    StringArray(const StringArray &other); // copy constructor
    ~StringArray(); // destructor
};

#endif // STRINGARRAY_H