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

    if (rule.size < 2) {
        std::cerr << "Invalid input format: " << std::endl;
        return 1;
    }

//    String name = rule.array[0].trim().as_string();
    String name = (rule.array[0])->trim().as_string();
//    String val = rule.array[1].trim().as_string();

    if (name == "src-ip" || name == "dst-ip") {
        Ip main_ip(name);
        parse_input(main_ip);
    }
    else if (name == "src-port" || name == "dst-port") {
        Port main_port(name);
        parse_input(main_port);
    }
    return 0;
}