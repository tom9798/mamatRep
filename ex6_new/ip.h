#ifndef IP_H
#define IP_H

#include "generic-field.h"
#include "string.h"

class Ip : public GenericField {
    int mask;
    unsigned int ip;
    bool dst;
//    String ip_str;

public:

    Ip(); //constructor
    ~Ip(); //destructor
//    Ip(const Ip &other); //copy constructor

    void get_rule(GenericString &rule);
    bool match(GenericString &packet);
};

#endif // IP_H