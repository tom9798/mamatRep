#include "string-array.h"


StringArray::StringArray()
    : string_array(nullptr), size(0){
}


StringArray::~StringArray() {
    for (int i = 0; i < this->size; ++i) {
        delete this->string_array[i];
    }
    delete[] this->string_array;
}

void StringArray::str_insert(char* str) {
    // resize the array
    this->size++;
    GenericString** new_array = new GenericString*[this->size];
    // copy string array to new one
    if (this->size > 1){
        for (int i = 0; i < (this->size - 1); i++) {
            new_array[i] = this->string_array[i];
        }
    }
    // update string array to be the new one
    delete[] this->string_array;
    this->string_array = new_array;

    // insert input to string array
    GenericString* new_generic_string = make_string(str);
    this->string_array[this->size - 1] = new_generic_string;
}


int StringArray::get_size() const{
    return this->size;
}

GenericString* StringArray::get_string_from_array(int index) const{
    if(index > this->size || index < 0){
        cerr << this->size << " Invalid index\n" << endl;
        return nullptr;
    }
    return this->string_array[index];
}

void StringArray::string_array_trim() const{
    for(int i = 0; i < this->size; i++)
        this->string_array[i]->trim();
}
