#include "generic-field.h"
#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include <iostream>
#include <bitset>
using std::bitset;

class Ip : public GenericField{
private:
    bool src_rule;
    bool dst_rule;
    unsigned int ip_reformatted;
    int dc_bits;

public:
    Ip();

    ~Ip();
    // edit rule ip, dont care bits, source/destination
    void edit_rule(GenericString &rule);
    // match between input packet and current rule
    virtual bool match(const GenericString &packet) const;
};