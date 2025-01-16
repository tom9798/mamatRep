#include "string_array.h"
#include "generic_string.h"
#include <cstring>
#include <cstdlib>

//constructor
StringArray::StringArray(int size){
    this->size = size;
    this->array = new GenericString*[size];
}

//copy constructor
StringArray::StringArray(const StringArray &other){
    this->size = other.size;
    this->array = new GenericString*[size];
    for(int i = 0; i < size; i++){
        this->array[i] = other.array[i];
    }
}

//destructor
StringArray::~StringArray(){
    delete[] this->array;
}