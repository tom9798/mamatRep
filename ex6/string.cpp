#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <cstring>
#include <cstdlib>

//allocate memory and copy the string
char* String::allocate_and_copy(const char *str, int size) {
    return strcpy(new char[size + 1], str);
}

//constructor
String::String(const char *str) {
    this->length = strlen(str);
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

//convert a GenericString to a String, no const, and return a reference
String& String::as_string(){
    return dynamic_cast<String&>(*this);
}


//convert a GenericString to a String, const
const String& String::as_string() const {
    return dynamic_cast<const String&>(*this);
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

//operator== for GenericString, checks if the string in the object is equal to the string in the other object
bool String::operator==(const GenericString &other) const {
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
//#####################need to implement string-array.cpp and string-array.h#####################
StringArray String::split(const char *delimiters) const {
    //first we initialize the StringArray object
    StringArray *array = new StringArray();

    //split this->str according to the given delimiters, using strtok
    //and find out the size of the needed array of GenericString objects
    //then allocate memory for the array and copy the strings
    //then return the array
    char *copy = allocate_and_copy(this->str, this->length); //we don't want to change the original string
    char *token = strtok(copy, delimiters); //get the first token to start iterating over the string

    while(token != nullptr){ //count the number of words
        array->size += 1;
        token = strtok(nullptr, delimiters); //get the next token
    }
    array->array = new GenericString*[array->size]; //allocate memory for the array of GenericString objects

    token = strtok(this->str, delimiters); //start iterating over the string again to add the tokens to the array
    for(int i = 0; i < array->size; i++){
        array->array[i] = make_string(token); //add the token to the array
        token = strtok(nullptr, delimiters); //get the next token
    }

    delete[] copy; //clean up

    return *array;
}

//convert the string into integer
int String::to_integer() const {
    return atoi(this->str);
}

//remove leading and trailing white spaces
//we first set indexes to note were the actual string starts and ends,
//and then we allocate memory for the new string and copy the string
String &String::trim(){
    //check if the string is empty
    int start = 0;
    int end = length - 1;
    //first setting the index to remove leading white spaces
    while(start < length && (this->str[start] == ' ' || this->str[start] == '\t')){ //check if it's a white space or a tab
        start++;
    }
    //then setting the index to remove trailing white spaces
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

    return *this;
}