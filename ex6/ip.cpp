#include "generic-field.h"
#include "generic-string.h"
#include "string-array.h"
#include "string.h"
#include "ip.h"
#include <bitset>
#include <cstring>
//#include <cstdib>

Ip::Ip() {
    dst = false;
    mask = 0;
    ip = 0;
}

Ip::~Ip() {}

void Ip::get_rule(GenericString &rule){
//    StringArray fields = rule.split(",");
//    String ip_str;
//    String ip_str;
//    unsigned int ip_mask;
//    for (size_t i = 0; i < fields.size; ++i) {
//        StringArray key_value = fields.array[i]->as_string().split("=");
//        String key = key_value.array[0]->as_string();
//        String value = key_value.array[1]->as_string();
//        if (key == "src-ip" || key == "dst-ip") {
//            if (key == "dst-ip") {
//                dst = true;
//            }
//            StringArray ip_mask = value.split("/"); //splitting the value into the IP and the rule
//            ip_str = ip_mask.array[0]->as_string();
//            ip_mask = ip_mask.array[1]->as_string().to_integer();
//        }
//    }
    //no need to split the rule
    String ip_str("");
    unsigned int ip_mask;
    StringArray key_value = rule.split("=");
    String key = key_value.array[0]->as_string();
    String value = key_value.array[1]->as_string();
    if (key == "src-ip" || key == "dst-ip") {
        if (key == "dst-ip") {
            dst = true;
        }
        StringArray ipRule = value.split("/"); //splitting the value into the IP and the rule
//        ip_str = ip_mask.array[0]->as_string();
        ip_str = ipRule.array[0]->as_string().str;
        ip_mask = ipRule.array[1]->as_string().to_integer();
    }

    //converting the IP to binary
    StringArray octets = ip_str.split(".");
    std::bitset<32> ip_bits;
    for (size_t i = 0; i < octets.size; ++i) {
        std::bitset<8> octet_bits(octets.array[i]->as_string().to_integer());
        ip_bits |= (octet_bits << (8 * (3 - i)));
    }
    this->ip = ip_bits;

    //converting the mask to an integer
    this->mask = ip_mask;
}

bool Ip::match(GenericString &packet){
    StringArray fields = packet.split(",");
    for (size_t i = 0; i < fields.size; ++i) {
        fields.array[i]->trim();
    }
    for (size_t i = 0; i < fields.size; ++i) { //iterating over the fields
        StringArray key_value = fields.array[i]->as_string().split("=");
        String key = key_value.array[0]->as_string();
        String value = key_value.array[1]->as_string();
        //searching the right ip field according to this->dst
        if (key == "src-ip" || key == "dst-ip") {
            StringArray octets = value.split(".");
            std::bitset<32> ip_bits;
            for (size_t j = 0; j < octets.size; ++j) {
                std::bitset<8> octet_bits(octets.array[j]->as_string().to_integer());
                ip_bits |= octet_bits << (8 * (3 - j));
            }
        }
    }

    //creating a mask for the left-most bits
    unsigned int mask_bits = 0;
    mask_bits = (1 << this->mask) - 1;
    mask_bits <<= (32 - this->mask);

    //checking if the IP address matches the rule
    unsigned int rule_ip = this->ip & mask_bits >> (32 - this->mask);
    unsigned int packet_ip = ip_bits & mask_bits >> (32 - this->mask);
    return rule_ip == packet_ip;
}