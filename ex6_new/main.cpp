#include "string.h"
#include "ip.h"
#include "port.h"
#include "input.h"
#include <iostream>

int main(int argc,char* argv[]){
    // check if ip or port
    GenericString *rule = make_string(argv[1]);
    StringArray ipORport = rule->split("=");
    bool valid_input = false; // true when valid input is approved
    // check if ip or port
    if(strcmp(ipORport.array[0]->as_string()->str,"ip-src") == 0 || strcmp(ipORport.array[0]->as_string()->str,"ip-dst") == 0) {
        valid_input = true;
        Ip ip_rule;
        ip_rule.edit_rule(*rule);
        parse_input(ip_rule);
    }
    if(strcmp(ipORport.array[0]->as_string()->str,"port-src") == 0 || strcmp(ipORport.array[0]->as_string()->str,"port-dst") == 0){
        valid_input = true;
        Port port_rule;
        port_rule.edit_rule(*rule);
        parse_input(port_rule);
    }
    delete rule;
    if(!valid_input){
        cerr << "Invalid input \n";
        return 1;
    }
    return 0;
}