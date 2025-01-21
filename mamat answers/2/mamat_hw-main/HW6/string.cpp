#include "string.h"
#include <cstring>

String::String() {
    this->length = 0;
    this->data = new char[1];
    this->data[0] = '\0';
}

String::String(const char *str) {
    this->length = strlen(str);
    this->data = new char[this->length + 1];
    strcpy(this->data, str);
}

String::String(const String &str) {
    this->length = str.length;
    this->data = new char[this->length + 1];
    strcpy(this->data, str.data);
}

String::~String() {
    delete[] data;
}

String& String::operator=(const String &rhs) {
    if (this != &rhs) {
        delete[] this->data;
        this->length = rhs.length;
        this->data = new char[this->length + 1];
        strcpy(this->data, rhs.data);
    }
    return *this;
}

String& String::operator=(const char *str) {
    delete[] this->data;
    this->length = strlen(str);
    this->data = new char[this->length + 1];
    strcpy(this->data, str);
    return *this;
}

bool String::equals(const String &rhs) const {
    return !strcmp(this->data, rhs.data);
}

bool String::equals(const char *rhs) const {
    return !strcmp(this->data, rhs);
}

void String::split(const char *delimiters, String **output, size_t *size)const {

    size_t count = 0;
    char* tempString = new char[this->length + 1];
    strcpy(tempString, data);

    char* token = std::strtok(tempString, delimiters);
    while (token != nullptr) {
        ++count;
        token = std::strtok(nullptr, delimiters);
    }
    // Set the output size
    if (size != nullptr) {
        *size = count;
    }
    // Allocate memory for output if necessary
    if (output != nullptr) {
        *output = new String[count];
        // Tokenize the string and store in the output array
        char* new_tempString = new char[this->length + 1];
        strcpy(new_tempString, this->data);
        token = std::strtok(new_tempString, delimiters);
        for (size_t i = 0; i < count; ++i) {
            (*output)[i] = token;
            token = std::strtok(nullptr, delimiters);
        }
        delete[] new_tempString;
    }
    delete[] tempString;
}

int String::to_integer() const {
    return atoi(this->data);
}

String String::trim() const {
    int start = 0;
    int end = strlen(this->data) - 1;
    char *str = this->data;
    while (str[start] == ' ') {
        start++;
    }
    while (str[end] == ' ') {
        end--;
    }
    size_t size = (end - start + 1);
    char *trimmed = new char[size + 1];
    strncpy(trimmed, str + start, size);
    trimmed[size] = '\0';
    String const retval(trimmed);
    delete[] trimmed;
    return retval;
}


