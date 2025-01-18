#include "string.h"
#include <iostream>

int main() {
    // Test constructor
    String str1("Hello, World!");
    std::cout << "str1: " << str1.get_str() << std::endl;

    // Test copy constructor
    String str2(str1);
    std::cout << "str2 (copy of str1): " << str2.get_str() << std::endl;

    // Test operator=
    str2 = "Goodbye, World!";
    std::cout << "str2 (after assignment): " << str2.get_str() << std::endl;

    // Test operator== with GenericString
    String str3("Goodbye, World!");
    std::cout << "str2 == str3: " << (str2 == str3) << std::endl;

    // Test operator== with char*
    std::cout << "str2 == \"Goodbye, World!\": " << (str2 == "Goodbye, World!") << std::endl;

    // Test to_integer
    String str4("12345");
    std::cout << "str4 as integer: " << str4.to_integer() << std::endl;

    // Test trim
    String str5("   Trim me!   "); //#####################need to fix###################
    str5.trim();
    std::cout << "str5 (after trim): \"" << str5.get_str() << "\"" << std::endl;

    // Test split
    String str6("split,this,string");
    StringArray array = str6.split(",");
    std::cout << "str6 split by ',':" << std::endl;
    for (size_t i = 0; i < array.size; ++i) {
        std::cout << "  " << array.array[i]->as_string().get_str() << std::endl;
    }

    // Clean up
    for (size_t i = 0; i < array.size; ++i) {
        delete array.array[i];
    }
    delete[] array.array;

    return 0;
}