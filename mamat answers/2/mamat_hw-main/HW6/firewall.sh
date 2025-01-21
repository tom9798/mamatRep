#!/bin/bash

#getting rules file and packet file
rules_file="$1"
packets=$(cat)

# deleting all comments and lines starting with '#'
rules=$(sed -e 's/#.*//' -e '/^$/d' "$rules_file") #echo "$rules"

IFS=, #coma is a delimiter
while read -r rule1 rule2 rule3 rule4 ; do
    {
        #funneling only matching packets to the next rule
        funnel=$(echo "$packets" | ./firewall.exe "$(echo "$rule1")")
        funnel=$(echo "$funnel" | ./firewall.exe "$rule2")
        funnel=$(echo "$funnel" | ./firewall.exe "$rule3")
        funnel=$(echo "$funnel" | ./firewall.exe "$rule4")
        all_match_packets="$all_match_packets\n$funnel"


    }
done <<< "$rules"

#removing all spaces and empty lines, sort, then prints the final value
all_match_packets="${all_match_packets// /}"
echo -e "$all_match_packets" | sed "s/ //g ; /^$/d" | sort -u