#include "generic-field.h"
#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <bitset>
#include <cstring>
#include <cstdib>

Port::Port() {
    dst = false;
    mask = 0;
    port = "";
}

Port::~Port() {}

void Port::get_rule(GenericString &rule){
    StringArray fields = rule.split(",");
    fields.string_array_trim();

    for (size_t i = 0; i < fields.size; ++i) {
        StringArray key_value = fields.array[i]->as_string().split("=");
        String key = key_value.array[0]->as_string();

        //splitting the value to min and max
        StringArray port = key_value.array[1]->as_string().split("-");
        int min_port = port.array[0]->as_string().to_integer();
        int max_port = port.array[1]->as_string().to_integer();

        if (key == "src-port" || key == "dst-port") {
            if (key == "dst-port") {
                dst = true;
            }
        }
    }
}

bool Port::match(GenericString &packet){
    StringArray fields = packet.split(",");
    fields.string_array_trim();
    int input_port = 0;
    for (size_t i = 0; i < fields.size; ++i) {
        StringArray key_value = fields.array[i]->as_string().split("=");
        String key = key_value.array[0]->as_string();
        int value = key_value.array[1]->to_integer();
        if (key == "src-port" || key == "dst-port") {
            input_port = value;
        }
    }
    if (input_port <= max_port && input_port >= min_port) {
        return true;
    }
    return false;
}