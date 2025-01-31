#!/bin/bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

packets=$(</dev/stdin)
rules_file=$1
all_rules=$(<$rules_file)
packets_passed=""
all_rules=$(awk '{sub(/#.*/, ""); if (NF) print}' "$rules_file")

while IFS= read -r rule; do
    IFS=',' read -r rule1 rule2 rule3 rule4 <<< "${rule// /}"
    out=$(echo "$packets" | ./firewall.exe "$rule1" | ./firewall.exe "$rule2" | ./firewall.exe "$rule3" | ./firewall.exe "$rule4" | tr -d ' ')
    packets_passed+=" $out"
done <<< "$all_rules"

packets_passed=$(echo "$packets_passed"| tr ' ' '\n' | awk 'NF' | sort)
echo "$packets_passed"