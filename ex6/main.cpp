#include <iostream>
#include "string.h"
#include "string-array.h"
#include "port.h"
#include "ip.h"
#include "input.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return 1;
    }

    String input(argv[1]);
    StringArray rule = input.split("=");

    if (rule.getSize() < 2) {
        std::cerr << "Invalid input format: " << std::endl;
        return 1;
    }

    String name = rule[0].trim().as_string();
    String val = rule[1].trim().as_string();

    if (name == "src-ip" || name == "dst-ip") {
        ip main_ip(name);
        main_ip.set_value(val);
        parse_input(main_ip);
    }
    else if (name == "src-port" || name == "dst-port") {
        port main_port(name);
        main_port.set_value(val);
        parse_input(main_port);
    }
    return 0;
}