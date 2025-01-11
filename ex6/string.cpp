#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <cstring>
#include <cstdlib>

//allocate memory and copy the string
static char* String::allocate_and_copy(const char *str, int size) {
    return strcpy(new char[size + 1], str);
}

//constructor
String::String(const char *str){
    length = strlen(str);
    this->str = allocate_and_copy(str, length);
}

//copy constructor
String::String(const String &other){
    length = other.length;
    str = allocate_and_copy(other.str, length);
}

//destructor
String::~String(){
    delete[] this->str;
}

//operator=
String& String::operator=(const char *str){
    if(this->str == str){
        return *this;
    }
    delete[] this->str;
    length = strlen(str);
    this->str = allocate_and_copy(str, length);
    return *this;
}

//operator== for GenericString
bool String::operator==(const GenericString &other) const{
    const String *other_string = dynamic_cast<const String*>(&other);
    if(other_string == nullptr){
        return false;
    }
    return *this == other_string->str;
}

//operator== for char*
bool String::operator==(const char *other) const{
    return strcmp(this->str, other) == 0;
}

//split the string according to delimiters
//#####################need to implement in string-array.cpp and string-array.h#####################

//convert the string into integer
int String::to_integer() const {
    return atoi(this->str);
}

//remove leading and trailing white spaces
String &String::trim(){
    //check if the string is empty
    int start = 0;
    int end = length - 1;
    //first remove leading white spaces
    while(start < length && (this->str[start] == ' ' || this->str[start] == '\t')){ //check if it's a white space or a tab
        start++;
    }
    //then remove trailing white spaces
    while(end >= 0 && (this->str[end] == ' ' || this->str[end] == '\t')){ //check if it's a white space or a tab
        end--;
    }
    //if the string is empty, meaning it's all white spaces
    if(start > end){
        delete[] this->str;
        this->str = new char[1];
        this->str[0] = '\0';
        length = 0;
        return *this;
    }
    //if there are no white spaces
    if(start == 0 && end == length - 1){
        return *this;
    }
    //if there are white spaces
    this -> length = end - start + 1;
    char *new_str = allocate_and_copy(this->str + start, end - start + 1);
    delete[] this->str;
    this->str = new_str;

}