#include "generic-field.h"
#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <iostream>
#include <bitset>
using std::bitset;

class Ip : public GenericField{
private:
    bool dst;
    unsigned int ip;
    int mask_ip;

public:
    Ip();

    ~Ip();

    void get_rule(GenericString &rule);
    bool match(const GenericString &packet) const;
};