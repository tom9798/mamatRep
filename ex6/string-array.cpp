#include "string-array.h"
#include "generic-string.h"
#include <cstring>
#include <cstdlib>

//constructor
//we will initialize the StringArray without a given size and array, and just return a pointer,
//so we could change it directly with the copy constructor but with a reference
StringArray::StringArray() {
    this->size = 0;
    this->array = nullptr;
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






//older version of the constructor
//StringArray::StringArray(int size, GenericString **array) {
//    this->size = size;
//    this->array = new GenericString *[size];
//    for (int i = 0; i < size; i++) {
//        this->array[i] = array[i];
//    }
//}