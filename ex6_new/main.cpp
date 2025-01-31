#include <iostream>
#include "port.h"
#include "string.h"
#include "ip.h"
#include "input.h"

int main(int argc,char* argv[]){
    GenericString *Rule = make_string(argv[1]);
    StringArray Type_Rule = Rule->split("=");
    Type_Rule.trimArray();
    String type = Type_Rule.stringAtIndex(0)->as_string();

    //port
    if (type == "src-port" || type == "dst-port"){
        Port PortRule;
        PortRule.get_rule(*Rule);
        parse_input(PortRule);
    }

    //ip
    else if (type == "src-ip" || type == "dst-ip") {
        Ip IpRule;
        IpRule.get_rule(*Rule);
        parse_input(IpRule);
    }

    delete Rule;
    return 0;
}