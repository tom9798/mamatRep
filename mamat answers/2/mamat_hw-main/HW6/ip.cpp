#include "ip.h"

#define  NUM_SEGMENTS 2
#define NUM_FIELDS 4
#define IP_PARTS 6
#define FST_IP_NUM 2
#define LAST_IP_NUM 6

/**
 * @brief Converts a string to a binary string representation.
 *
 * This function takes a string, converts it to an integer, and then converts 
 * the integer to a binary string representation. The resulting binary string 
 * is returned. The input string is expected to represent a number.
 *
 * @param str Pointer to the string to be converted.
 * @return The binary string representation of the input string.
 */
std::string convertToBinaryString(String *str) {
    int number = str->to_integer();
    std::string binary_string = std::bitset<8>(number).to_string();
    binary_string.erase(0, binary_string.find_first_not_of('0'));
    binary_string = std::string(8 -binary_string.length(), '0') + binary_string;
    return binary_string;
}

 bool Ip::set_value(String value) {
    String command = value.trim();
    const char delimiter[] = "/";
    String *output = nullptr;
    size_t size = 0;
    command.split(delimiter, &output, &size); 
    if (size != NUM_SEGMENTS) {
        return false;
    }
    this->msb_ip = output[0];
    this->mask = output[1].to_integer();
    delete[] output;
    return true;
 }

 bool Ip::match(String packet) {
     if (packet.equals("")){
        return false;
    }
    String *commands = nullptr;
    //split the packet into 4 fields and trim 
    char coma[] = ",";
    size_t num = 0;
    packet.split(coma, &commands, &num);
    if (num != NUM_FIELDS) {
        delete[] commands;
        return false;
    }
    for (int i = 0; i < NUM_FIELDS; i++) {
        commands[i] = commands[i].trim();
    }
    //split each field into segments 
    size_t size = 0;
    const char *src_or_dst = (this->get_dst()) ? "dst" : "src";
    char delimiters[] = ".=-"; 
    for(int i = 0; i < NUM_FIELDS; i++) {
        String *segments = nullptr;
        commands[i].split(delimiters, &segments, &size);
        for (size_t k = 0 ; k < size; k++){
            segments[k] = segments[k].trim();
        }
        //check if current field is IP field and if it is src/dst
        if(size != IP_PARTS || !(segments[0].equals(src_or_dst))){
            delete[] segments;
            continue;
        }
        //create binary string for packet ip
        std::string packet_ip_value = "";
        for (int j = FST_IP_NUM; j < LAST_IP_NUM; j++) {
            packet_ip_value += convertToBinaryString(&segments[j]); 
        }
        size_t nsize = 0;
        String *noutput = nullptr;
        const char dot[] = ".";
        (this->msb_ip).split(dot, &noutput, &nsize);
        if (nsize != NUM_FIELDS) {
            delete[] segments;
            delete[] noutput;
            delete[] commands;
            return false;
        }
        //create binary string for this->ip value
        std::string this_ip_value = "";
        for (int j = 0; j < NUM_FIELDS; j++) {
            this_ip_value += convertToBinaryString(&noutput[j]); 
        }
        packet_ip_value.erase(this->mask);
        this_ip_value.erase(this->mask);
        
        if (this_ip_value == packet_ip_value) {
            delete[] segments;
            delete[] noutput;
            delete[] commands;
            return true;
        } else {
            delete[] segments;
            delete[] noutput;
            delete[] commands;
        return false;
        }
    }
    return false;
 }