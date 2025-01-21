/**
 * @file port.h
 * @brief Contains declaration of the Port class and related functionalities.
 */
#ifndef PORT_H
#define PORT_H

#include <stddef.h>
#include <iostream>
#include "generic-field.h"
#include <string>
#include "string.h"

/**
 * @enum PortType
 * @brief Enumeration for identifying Port types.
 */
enum {SRC_P = 0, DST_P};

/**
 * @class Port
 * @brief Represents an Port field and provides related operations.
 */
class Port : public GenericField {
    int min_port;
    int max_port;
    bool is_dst;

public:

    /**
     * @brief Default constructor for the Ip class.
     */
    Port() : min_port(0), max_port(0), is_dst(SRC_P) {};
    
    /**
     * @brief Copy constructor for the Ip class.
     * @param ip The Ip object to be copied.
     */   
     Port(const Port &p) {
        this->min_port = p.min_port;
        this->max_port = p.max_port;
        this->is_dst = p.is_dst;
    };
    /**
     * @brief Destructor for the Ip class.
     */
    ~Port() {};

     /**
     * @brief Get the minimum port value.
     *
     * @return The minimum port value.
     */
    int get_min() const {
        return min_port;
    }
    /**
     * @brief Get the maximum port value.
     *
     * @return The maximum port value.
     */
    int get_max() const {
        return max_port;
    }
    /**
     * @brief Check if the port is a destination port.
     *
     * @return True if the port is a destination port, false if it is a
     *  source port.
     */
    bool get_dst() const {
        return is_dst;
    }

    /**
     * @brief Set the minimum port value.
     *
     * @param min The minimum port value to set.
     */
    void set_min(int min) {
        min_port = min;
    }
    /**
     * @brief Set the maximum port value.
     *
     * @param max The maximum port value to set.
     */
    void set_max(int max) {
        max_port = max;
    }
     /**
     * @brief Set the port as source or destination.
     *
     * @param string The string representing the port type ("src" or "dst").
     */
    void set_dst(const String string) {
        String dst("dst");
        is_dst = (dst.equals(string)) ? DST_P : SRC_P;
    }
     /**
     * @brief Set the minimum and maximum and port values based on the
     *  provided string.
     * This function parses the provided string to extract the minimum and 
     * maximum and port values.
     * The string is expected to be in the format "min-max", where "min" and 
     * "max" are integer values representing the minimum and maximum port values 
     * @param value The string representing the minimum and maximum port values.
     * @return True if the port values were successfully set, false otherwise.
     */
    bool set_value(String value) override;

    /**
     * @brief Check if the provided packet matches the port criteria.
     *
     * This function checks if the provided packet matches the port criteria 
     * defined by the minimum and maximum port values. The packet is expected 
     * to be a string containing multiple commands separated by commas.
     * If a matching command is found in packet, the function extracts the port 
     * number and checks if it falls within the minimum and maximum port values.   
     * @param packet The packet string containing multiple commands.
     * @return True if the packet matches the port criteria, false otherwise.
     */
    bool match(String packet) override;
};

#endif