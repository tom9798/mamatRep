#include "port.h"

#define PORT "port"
#define NUM_COM 4
#define NUM_SEGMENTS 2
#define PORT_PARTS 3
#define PORT_VALUE 2

bool Port::set_value(String value) {
    String command = value.trim();
    char delimiters[] = "-";
    String *output = NULL;
    size_t size = 0;
    command.split(delimiters, &output, &size);
    if (size != NUM_SEGMENTS) {
        return false;
    }
    String str_min = output[0];
    String str_max = output[1];

    this->min_port = str_min.to_integer();
    this->max_port = str_max.to_integer();
    delete[] output;
    return true;
}

bool Port::match(String packet) {
    if (packet.equals("")){
        return false;
    }
    String *commands = nullptr;
    const char coma[] = ",";
    size_t num = 0;
    //split the packet into 4 fields and trim
    packet.split(coma, &commands, &num);
    if (commands == nullptr) {
    }
    if (num != NUM_COM) {
        delete[] commands;
        return false;
    }
    for (int i = 0; i < NUM_COM; i++) {
        commands[i] = commands[i].trim();
    }
    //split each field into segments
    const char delimiters[] = "-=.";
    size_t size = 0;
    int port = 0;
    const char *src_or_dst = (this->get_dst()) ? "dst" : "src";
    for(int i = 0; i < NUM_COM; i++) {
        String *segments = nullptr;
        commands[i].split(delimiters, &segments, &size);
        for (size_t k = 0 ; k < size; k++){
            segments[k] = segments[k].trim();
        }
        //check if current field is PORT field and if it is src/dst
        if (size != PORT_PARTS || !segments[0].equals(src_or_dst)) {
            delete[] segments;
            continue;
        }
        port = segments[PORT_VALUE].to_integer();
        delete[] segments;
        break;
    }
    delete[] commands;
    return (port <= this->get_max() && port >= this->get_min());
}