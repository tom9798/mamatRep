#include "string-array.h"

//constructor
//we will initialize the StringArray without a given size and array, and just return a pointer,
//so we could change it directly with the copy constructor but with a reference
StringArray::StringArray() { //################tried a different approach################
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

//destructor, delete the array and the strings in it
StringArray::~StringArray() {
    for (int i = 0; i < this->size; ++i) {
        delete this->array[i];
    }
    delete[] this->array;
}

//insert a string to the array
void StringArray::insert(char* str) { //################tried a different approach################
    this->size++; // update the size
    this->array = static_cast<GenericString**>(realloc(this->array, this->size * sizeof(GenericString*)));
    if (this->array == nullptr) {
        cerr << "failed to allocate extra memory" << endl;
        exit(1);
    }

    GenericString* new_generic_string = make_string(str);
    this->array[this->size - 1] = new_generic_string;
}

int StringArray::getSize() const {
    return this->size;
}

GenericString* StringArray::stringAtIndex(int index) const {
    if(index > this->size || index < 0){
        cerr << this->size << " Invalid index\n" << endl;
        return nullptr;
    }
    return this->array[index];
}

void StringArray::trimArray() const {
    for(int i = 0; i < this->size; i++)
        this->array[i]->trim();
}
