#ifndef PORT_H
#define PORT_H

#include "generic-field.h"
#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <iostream>

class Port : public GenericField{
private:
    bool dst_rule;
    bool src_rule;
    int min_port;
    int max_port;

public:
    Port();

    ~Port();

    void edit_rule(GenericString &rule);

    bool match(const GenericString &packet) const;
};

#endif