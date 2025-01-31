#include "port.h"

#define SRC_NAME "src-port"
#define DST_NAME "dst-port"
#define ACTIVE_RULE  true

Port::Port() {
    this->dst = false;
    this->max_port = 0;
    this->min_port = 0;
}

Port::~Port(){}

void Port::get_rule(GenericString &rule){
    StringArray ruleArr = rule.split("=");
    ruleArr.trimArray();
    int min_value;
    int max_value;
    if (ruleArr.stringAtIndex(0)->as_string() == SRC_NAME || ruleArr.stringAtIndex(0)->as_string() == DST_NAME) { //##################tried a different approach##################
        if (ruleArr.stringAtIndex(0)->as_string() == DST_NAME) {
            this->dst = true;
        }
        StringArray rangeValues = ruleArr.stringAtIndex(1)->as_string().split("-");
        rangeValues.trimArray();
        min_value = rangeValues.stringAtIndex(0)->to_integer();
        max_value = rangeValues.stringAtIndex(1)->to_integer();
        this->min_port = min_value;
        this->max_port = max_value;
    }
}

bool Port::match(const GenericString &packet) const{//##################tried a different approach##################
    StringArray fields = packet.split(",");
    fields.trimArray();

    int input_port = 0;
    for (int i = 0; i < fields.getSize(); i++) {
        StringArray key_value = fields.stringAtIndex(i)->as_string().split("=");
        String key = key_value.stringAtIndex(0)->as_string();


        if(dst && key == DST_NAME){
            input_port = key_value.stringAtIndex(1)->to_integer();
        }
        else if(!dst && key == SRC_NAME){
            input_port = key_value.stringAtIndex(1)->to_integer();
        }
    }
    if (input_port <= max_port && input_port >= min_port) {
        return true;
    }
    return false;
}


