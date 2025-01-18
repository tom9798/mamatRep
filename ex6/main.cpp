#include "string.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

int main() {
    // Test constructor
    String str1("Hello, World!");
    std::cout << "str1: " << str1.as_string() << std::endl;

    // Test copy constructor
    String str2(str1);
    std::cout << "str2 (copy of str1): " << str2.as_string() << std::endl;

    // Test operator=
    str2 = "Goodbye, World!";
    std::cout << "str2 (after assignment): " << str2.as_string() << std::endl;

    // Test operator== with GenericString
    String str3("Goodbye, World!");
    std::cout << "str2 == str3: " << (str2 == str3) << std::endl;

    // Test operator== with char*
    std::cout << "str2 == \"Goodbye, World!\": " << (str2 == "Goodbye, World!") << std::endl;

    // Test to_integer
    String str4("12345");
    std::cout << "str4 as integer: " << str4.to_integer() << std::endl;

    // Test trim
    String str5("   Trim me!   ");
    str5.trim();
    std::cout << "str5 (after trim): \"" << str5.as_string() << "\"" << std::endl;

    // Test split
    String str6("split,this,string");
    StringArray array = str6.split(",");
    std::cout << "str6 split by ',':" << std::endl;
    for (int i = 0; i < array.size; ++i) {
        std::cout << "  " << array.array[i]->as_string() << std::endl;
    }

    // Clean up
    for (int i = 0; i < array.size; ++i) {
        delete array.array[i];
    }
    delete[] array.array;

    return 0;
}