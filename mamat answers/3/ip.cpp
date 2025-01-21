#include "ip.h"

#define SRC_NAME "src-ip"
#define DST_NAME "dst-ip"
#define IP_FIELDS 5
#define ACTIVE_RULE  true

Ip::Ip() {
    this->src_rule = false;
    this->dst_rule = false;
}

Ip::~Ip() {}


void Ip::edit_rule(GenericString &rule){
    StringArray splitted_rule = rule.split("=");
    splitted_rule.string_array_trim();
    int ip_adress[IP_FIELDS];
    for(int i = 0; i < splitted_rule.get_size(); i++)
    {
        if(strcmp(splitted_rule.get_string_from_array(i)->as_string().get_str(),SRC_NAME) == 0)
        {   
            this->src_rule = true;
            // split adress fields and insert to new int array
            StringArray ip_fields = splitted_rule.get_string_from_array(i + 1)->split("./");
            ip_fields.string_array_trim();
            for(int j = 0; j < IP_FIELDS; j++) {
                ip_adress[j] = ip_fields.get_string_from_array(j)->to_integer();
            }
            this->ip_reformatted = ip_adress[0] << 24 | ip_adress[1] << 16 | ip_adress[2] << 8 | ip_adress[3];
            this->dc_bits = ip_adress[4];
            break;
        }
        if(strcmp(splitted_rule.get_string_from_array(i)->as_string().get_str(),DST_NAME) == 0)
        {
            this->dst_rule = true;
            StringArray ip_fields = splitted_rule.get_string_from_array(i + 1)->split("./");
            ip_fields.string_array_trim();
            for(int j = 0; j < IP_FIELDS; j++) {
                ip_adress[j] = ip_fields.get_string_from_array(j)->to_integer();
            }
            this->ip_reformatted = ip_adress[0] << 24 | ip_adress[1] << 16 | ip_adress[2] << 8 | ip_adress[3];
            this->dc_bits = ip_adress[4];
            break;
        }
    }
}

bool Ip::match(const GenericString &packet) const{
    StringArray packet_splitted = packet.split(",=");
    packet_splitted.string_array_trim();
    int input_ip_as_int[IP_FIELDS];
    unsigned int input_ip_formatted = 0;
    const char *field_to_check;
    if (this->src_rule) {
        field_to_check = SRC_NAME;
    }
    else {
        field_to_check = DST_NAME;
    }
    
    for(int i = 0; i < packet_splitted.get_size(); i++)
    {
        if(strcmp(packet_splitted.get_string_from_array(i)->as_string().get_str(),field_to_check) == 0)
        {
            StringArray input_ip_as_strings = packet_splitted.get_string_from_array(i + 1)->split("./");
            input_ip_as_strings.string_array_trim();
            for(int j = 0; j < input_ip_as_strings.get_size(); j++){
                input_ip_as_int[j] = input_ip_as_strings.get_string_from_array(j)->to_integer();
            }
            input_ip_formatted = input_ip_as_int[0] << 24 | 
                      input_ip_as_int[1] << 16 | 
                      input_ip_as_int[2] << 8 | 
                      input_ip_as_int[3];
        }
    }
    // Create a mask to for left-most dc_bits
    unsigned int mask;
    if (this->dc_bits == 32) {
        mask = 0xFFFFFFFF;
    } else {
        mask = (1U << this->dc_bits) - 1;
        mask <<= (32 - this->dc_bits);
    }
    unsigned int leftMost1 = (this->ip_reformatted & mask) >> (32 - this->dc_bits);
    unsigned int leftMost2 = (input_ip_formatted & mask) >> (32 - this->dc_bits);
    return leftMost1 == leftMost2;
}


