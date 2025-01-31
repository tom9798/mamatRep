#include "string.h"
#include <cstdlib>

//allocate memory and copy the string
char* String::allocate_and_copy(const char *str, int size) {
    char *new_str = new char[size + 1];
    for (int i = 0; i < size+1; i++) {
        new_str[i] = str[i];
    }
    return new_str;
}

//constructor
String::String(const char *str){
    this->length = strlen(str);
    this->str = allocate_and_copy(str, strlen(str));
}

//copy constructor
String::String(const String &other){
    this->length = other.length;
    this->str = allocate_and_copy(other.str, strlen(other.str));
}

//destructor
String::~String() {
    delete[] this->str;
}

//getter
const char* String::get_str() const{
    return this->str;
}

//operator=
String& String::operator=(const char *elem) {
    if (this->str == elem) {
        return *this; // same string
    }
    delete[] this->str;
    this->length = strlen(elem);
    this->str = allocate_and_copy(elem, this->length);
    return *this;
}
//operator== for char*
bool String::operator==(const char *other) const{
    if(!strcmp(this->str, other))
        return true;
    return false;
}
//operator== for GenericString
bool String::operator==(const GenericString &other) const{
    if(!strcmp(this->str, other.as_string().str))
        return true;
    return false;
}

//split the string by the delimiters
//StringArray String::split(const char *delimiters) const{
//    char *cpy = allocate_and_copy(this->str, this->length); //we don't want to change the original string
//
//    char *token = strtok(cpy,delimiters); // first token
//
//    StringArray array;
//
//    while(token != NULL) // insert each token to the array
//    {
//        array.insert(token);
//        token = strtok(NULL,delimiters);
//    }
//    delete[] cpy;
//    return array;
//}

StringArray String::split(const char *delimiters) const {
    StringArray array;
    const char *start = this->str;
    const char *end = start;

    while (*end != '\0') {
        // Find the next delimiter
        while (*end != '\0' && strchr(delimiters, *end) == nullptr) {
            ++end;
        }

        // Add the token to the array
        if (end > start) {
//            array.insert(String(start, end - start));
            array.insert(allocate_and_copy(start, end - start));
        }

        // Skip the delimiter
        if (*end != '\0') {
            ++end;
        }
        start = end;
    }
    return array;
}

//convert the string into integer
int String::to_integer() const{
    return atoi(this->str);
}

//remove leading and trailing white spaces
String &String::trim(){
    if (this->length == 0){
        return *this;
    }

    //check if the string is empty
    int start = 0;
    int end = this->length - 1;
    //first setting the index to remove leading white spaces
    while(start < this->length && (this->str[start] == ' ' || this->str[start] == '\t')){ //check if it's a white space or a tab
        start++;
    }
    //then setting the index to remove trailing white spaces
    while(end >= start && (this->str[end] == ' ' || this->str[end] == '\t')){ //check if it's a white space or a tab
        end--;
    }
    //if the string is empty, meaning it's all white spaces
    if(start > end){
        delete[] this->str;
        this->str = new char[1];
        this->str[0] = '\0';
        this->length = 0;
        return *this;
    }
    //if there are no white spaces
    if(start == 0 && end == length - 1){
        return *this;
    }
    //if there are white spaces
    this -> length = end - start + 1;
    char *new_str = allocate_and_copy(this->str + start, this->length);
    delete[] this->str;
    this->str = new_str;

    return *this;
}

//convert a GenericString to a String, no const, and return a reference
String& String::as_string(){
    return dynamic_cast<String&>(*this);
}

//convert a GenericString to a String, const
const String& String::as_string() const {
    return dynamic_cast<const String&>(*this);
}

//make a new string
GenericString* make_string(const char *str){
    return new String(str);
}


