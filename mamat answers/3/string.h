#ifndef STRING_H
#define STRING_H

#include "generic-string.h"
#include "string-array.h"
#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

class String : public GenericString {
private:
    char* str;

public:

    String(const char *str = ""); // constructor with default empty string
    ~String(); // deconstructor

    // Explanations are given in the .h file:
    StringArray split(const char *delimiters) const override; 
    GenericString& operator=(const char *str);
    GenericString& trim();
    bool operator==(const GenericString &other) const;
    bool operator==(const char *other) const;
    int to_integer() const;
    String& as_string();
    const String& as_string() const;
    const char* get_str() const;

};

#endif