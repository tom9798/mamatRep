#include "ip.h"

#define SRC_NAME "src-ip"
#define DST_NAME "dst-ip"
#define IP_FIELDS 5
#define ACTIVE_RULE  true

Ip::Ip() {
    dst = false;
    mask_ip = 0;
    ip = 0;
}

Ip::~Ip() {}


void Ip::get_rule(GenericString &rule){
    String ip_str("");
    StringArray key_value = rule.split("=");
    key_value.trimArray();
    String key = key_value.stringAtIndex(0)->as_string();
    String value = key_value.stringAtIndex(1)->as_string();
    if (key == SRC_NAME || key == DST_NAME) {
        if (key == DST_NAME) {
            dst = true;
        }
        StringArray ipRule = value.split("/"); //splitting the value into the IP and the rule
        ipRule.trimArray();
        ip_str = ipRule.stringAtIndex(0)->as_string().get_str();
        this->mask_ip = ipRule.stringAtIndex(1)->to_integer();
    }

    //converting the IP to binary
    StringArray octets = ip_str.split(".");
    octets.trimArray();
    std::bitset<32> ip_bits = 0;
    for (int i = 0; i < octets.getSize(); i++) {
        std::bitset<32> octet_bits(octets.stringAtIndex(i)->as_string().to_integer());
        //preform a bitwise OR operation between the ip_bits and the octet_bits shifted to the left by 8 * (3 - i)
        ip_bits = (ip_bits | octet_bits)<<8;
    }
    this->ip = ip_bits.to_ulong();
}

bool Ip::match(const GenericString &packet) const{
    StringArray fields = packet.split(",");
    fields.trimArray();
    std::bitset<32> ip_bits = 0;
    for (int i = 0; i < fields.getSize(); i++) { //iterating over the fields
        StringArray key_value = fields.stringAtIndex(i)->as_string().split("=");
        key_value.trimArray();
        String key = key_value.stringAtIndex(0)->as_string();

        //searching the right ip field according to this->dst
        if (key == SRC_NAME && !dst) {
            String value = key_value.stringAtIndex(1)->as_string();
            StringArray octets = value.split(".");
            //put zeros in the ip_bits
            ip_bits = 0;
            for (int j = 0; j < octets.getSize(); j++) {
                std::bitset<32> octet_bits(octets.stringAtIndex(j)->as_string().to_integer());
                ip_bits = (ip_bits | octet_bits)<<8;
            }
        }
        if (dst && key == DST_NAME) {
            String value = key_value.stringAtIndex(1)->as_string();
            StringArray octets = value.split(".");
            //put zeros in the ip_bits
            ip_bits = 0;
            for (int j = 0; j < octets.getSize(); j++) {
                std::bitset<32> octet_bits(octets.stringAtIndex(j)->as_string().to_integer());
                ip_bits = (ip_bits | octet_bits)<<8;
            }
        }
    }
    //checking if the IP address matches the rule
    unsigned int rule_ip = this->ip >> (32 - this->mask_ip);
    unsigned int packet_ip = ip_bits.to_ulong() >> (32 - this->mask_ip);
    return rule_ip == packet_ip;
}


