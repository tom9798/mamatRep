#ifndef PORT_H
#define PORT_H

#include "generic-field.h"
#include "string.h"

class Port : public GenericField {
    int mask;
    int min_port;
    int max_port;
    bool dst;

public:

    Port(); //constructor
    ~Port(); //destructor
//    Ip(const Ip &other); //copy constructor

    void get_rule(GenericString &rule);
    bool match(GenericString &packet) override;
};

#endif // PORT_H