#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

#include "generic-string.h"
#include "string.h"


class StringArray{
private:
    GenericString **string_array;
    int size;

public:
    // consturcor
    StringArray();
    // distructor
    ~StringArray();
    // insert string to array
    void str_insert(char *str);
    // get array size
    int get_size() const;
    // access to GenericString located in given index
    // return pointe to it
    GenericString *get_string_from_array(int index) const;
    // trim each string
    void string_array_trim() const;

};

#endif