#include <iostream>
#include "port.h"
#include "string.h"
#include "ip.h"
#include "input.h"

int main(int argc,char* argv[]){
    String *Rule = make_string(argv[1]);
    StringArray Type_Rule = Rule->split("=");
    Type_Rule.trimArray();
    String *type = Type_Rule.stringAtIndex(0)->as_string();

    //port
    if (*type == "src-port" || *type == "dst-port"){
        Port PortRule;
        PortRule.get_rule(*Rule);
        parse_input(PortRule);
    }

    //ip
    else if (*type == "src-ip" || *type == "dst-ip") {
        Ip IpRule;
        IpRule.get_rule(*Rule);
        parse_input(IpRule);
    }

    delete Rule;
}


//// check if ip or port
//GenericString *rule = make_string(argv[1]);
//StringArray rule_type = rule->split("-.=");
//rule_type.string_array_trim();
//bool valid_input = false; // true when valid input is approved
//for (int i = 0; i < rule_type.get_size(); i++) {
//// check if ip
//if(strcmp(rule_type.get_string_from_array(i)->as_string().get_str(),IP_RULE) == 0) {
//valid_input = true;
//Ip ip_rule;
//ip_rule.edit_rule(*rule);
//parse_input(ip_rule);
//break;
//}
//// check if port
//if(strcmp(rule_type.get_string_from_array(i)->as_string().get_str(),PORT_RULE) == 0){
//valid_input = true;
//Port port_rule;
//port_rule.edit_rule(*rule);
//parse_input(port_rule);
//break;
//}
//}
//delete rule;
//if(!valid_input){
//cerr << "Invalid inputaa \n";
//return 1;
//}
//return 0;