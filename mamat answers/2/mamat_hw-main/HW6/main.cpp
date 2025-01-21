#include <iostream>
#include "string.h"
#include "generic-field.h"
#include "input.h"
#include "port.h"
#include "ip.h"

enum {SUCCESS = 0, FAIL};

#define SRC_IP "src-ip"
#define DST_IP "dst-ip"
#define SRC_PORT "src-port"
#define DST_PORT "dst-port"

int main(int argc, char *argv[]) {

    if (check_args(argc, argv)) {
        return FAIL;
    }
    String dst("dst");
    String src("src");
    String arg1(argv[1]);
    char equal_delimiter[] = "=";
    String *partition = nullptr;
    size_t size = 0;
    arg1.split(equal_delimiter, &partition, &size);
    for (size_t i = 0; i < size; i++)
    {
        partition[i] = partition[i].trim();
    }
    
    if (partition[0].equals(SRC_IP) || partition[0].equals(DST_IP)) {
        // so the rule is ip
        Ip ip_rule;
        if (partition[0].equals(SRC_IP)) {
            ip_rule.set_dst(src);
        } else {
            ip_rule.set_dst(dst);
        }
        ip_rule.set_value(partition[1]);
        parse_input(ip_rule);
    }
    else {
        // so the rule is port
        Port port_rule;
        if (partition[0].equals(SRC_PORT)) {
            port_rule.set_dst(src);
        } else {
            port_rule.set_dst(dst);
        }
        port_rule.set_value(partition[1]);
        parse_input(port_rule);
    }
    delete[] partition;
    return 0;
}
