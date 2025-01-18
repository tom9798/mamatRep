#ifndef STRING_H
#define STRING_H

#include "generic-string.h"
#include "string-array.h"

class String : public GenericString {
    int length;
    char *str;
    static char* allocate_and_copy(const char *str, int length);
public:
    String(const char *str); // constructor
    String(const String &other); // copy constructor
    ~String(); // destructor
    String& operator=(const char *str); // operator=
    bool operator==(const GenericString &other) const; // operator==
    bool operator==(const char *other) const; // operator==
    StringArray split(const char *delimiters) const; // split the string according to delimiters
    int to_integer() const; // convert the string to integer
    String& trim(); // remove leading and trailing white spaces
    String& as_string(); // return the string as a String object
};

#endif // STRING_H