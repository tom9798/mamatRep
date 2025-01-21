#include "string.h"
#include <cstdlib>

String::String(const char *str){
    this->str = new char[strlen(str) + 1];
    strcpy(this->str,str);
}

String::~String() {
    delete[] this->str;
}

StringArray String::split(const char *delimiters) const{
    // split using strtok
    char *str_copy = new char[strlen(this->str) + 1];
    strcpy(str_copy, this->str);
    char *token = strtok(str_copy,delimiters); // first token
    StringArray string_array;

    while(token != NULL) // insert each token to the array
    {
        string_array.str_insert(token);
        token = strtok(NULL,delimiters);
    }
    delete[] str_copy;
    return string_array;
}

GenericString& String::operator=(const char *new_str) {
    if (this->str == new_str) {
        return *this; // same string
    }

    delete[] this->str; // delete current data

    this->str = new char[strlen(new_str) + 1]; // allocate memory new string
    strcpy(this->str, new_str); 

    return *this;
}

GenericString& String::trim(){
    int length = strlen(this->str);
    int first_index = -1;
    int last_index = -1;
    if (length == 1 && (this->str[0] != ' ' || length == 0)) {
        return *this;
    }

    for (int i = 0; i < length; i++) { // find first non-space index
        if (this->str[i] != ' ') {
            first_index = i;
            break;
        }
    }
    for (int i = (length - 1); i >= 0 ; i--) { // find last non-space index
        if (this->str[i] != ' ') {
            last_index = i;
            break;
        }
    }

    // temp string from which we copy without spaces
    char *temp_str = new char[strlen(this->str) + 1]; 
    strcpy(temp_str, this->str);
    delete[] this->str;

    this->str = new char[last_index - first_index + 2]; // no spaces string size
    int j = 0; // filled-in indexes counter
    for(int i = first_index; i < last_index + 1; i++){
        this->str[j] = temp_str[i];
        j++;
    }
    this->str[j] = '\0';
    delete[] temp_str;
    return *this;
}

bool String::operator==(const char *other) const{
    if(!strcmp(this->str, other))
        return true;
    return false;
}
bool String::operator==(const GenericString &other) const{
    if(!strcmp(this->str, other.as_string().str))
        return true;
    return false;
}

int String::to_integer() const{
    int num = std::atoi(this->str);
    return num;
}

String& String::as_string(){
    return *dynamic_cast<String*>(this);
}

const String& String::as_string() const{
    return *dynamic_cast<const String*>(this);
}


GenericString* make_string(const char *str){
    String *new_str = new String(str);
    return new_str;
}

const char* String::get_str() const{
    return this->str;
}
