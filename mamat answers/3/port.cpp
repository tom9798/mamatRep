#include "port.h"

#define SRC_NAME "src-port"
#define DST_NAME "dst-port"
#define ACTIVE_RULE  true

Port::Port() {
    this->dst_rule = false;
    this->src_rule = false;
    this->max_port = 0;
    this->min_port = 0;
}

Port::~Port(){}

void Port::edit_rule(GenericString &rule){
    StringArray splitted_rule = rule.split("=");
    splitted_rule.string_array_trim();
    int min_value;
    int max_value;
    for(int i = 0;i < splitted_rule.get_size();i++)
    {
        if(strcmp(splitted_rule.get_string_from_array(i)->as_string().get_str(),SRC_NAME) == 0) {
            this->src_rule = true;
            StringArray input_values = splitted_rule.get_string_from_array(i + 1)->split("-");
            input_values.string_array_trim();
            min_value = input_values.get_string_from_array(0)->to_integer();
            max_value = input_values.get_string_from_array(1)->to_integer();
            this->min_port = min_value;
            this->max_port = max_value;
            break;
        }
        if(strcmp(splitted_rule.get_string_from_array(i)->as_string().get_str(),DST_NAME) == 0) {
            this->dst_rule = true;
            StringArray input_values = splitted_rule.get_string_from_array(i + 1)->split("-");
            input_values.string_array_trim();
            min_value = input_values.get_string_from_array(0)->to_integer();
            max_value = input_values.get_string_from_array(1)->to_integer();
            this->min_port = min_value;
            this->max_port = max_value;
            break;
        }
    }
}

bool Port::match(const GenericString &packet) const{
    StringArray packet_splitted = packet.split(",=");
    packet_splitted.string_array_trim();
    int input_port = 0;
    const char *field_to_check;
    if(this->src_rule)
        field_to_check = SRC_NAME;
    else
        field_to_check = DST_NAME;
    
    for(int i = 0; i < packet_splitted.get_size(); i++){
        if(strcmp(packet_splitted.get_string_from_array(i)->as_string().get_str(),field_to_check) == 0)
            input_port = packet_splitted.get_string_from_array(i + 1)->to_integer();
    }
    if(input_port <= this->max_port && input_port >= this->min_port)
        return true;
    else
       return false;
}


