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
    char* str;
    int length;
    static char* allocate_and_copy(const char *str, int length);
public:
    String(const char *str = ""); // empty string constructor
    String(const String &other); // copy constructor
    ~String(); // destructor

    const char* get_str() const; // get the string
    String& operator=(const char *str);
    bool operator==(const char *other) const;
    bool operator==(const GenericString &other) const;
    StringArray split(const char *delimiters) const override;
    int to_integer() const;
    String& trim();
    String& as_string();
    const String& as_string() const;
};

#endif