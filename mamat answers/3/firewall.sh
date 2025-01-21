#!/bin/bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

packets=$(</dev/stdin)
rules_file=$1
all_rules=$(<$rules_file)

# keep packets that passed:
packets_passed="" 
# clean comments and empty lines:
all_rules=$(echo "$all_rules" | awk '{sub(/#.*/, "", $0); if (NF) print}')

while IFS= read -r rule; do
    iter_rule="$rule"
    # split to src-ip, dst-ip, src-port, dst-port
    rule1=$(echo "$iter_rule" | cut -d',' -f1 | tr -d ' ')
    rule2=$(echo "$iter_rule" | cut -d',' -f2 | tr -d ' ') 
    rule3=$(echo "$iter_rule" | cut -d',' -f3 | tr -d ' ') 
    rule4=$(echo "$iter_rule" | cut -d',' -f4 | tr -d ' ') 
	# insert packets file to run with each rule part
   	rule1_passed=$(echo "$packets" | ./firewall.exe "$rule1" | sort | tr -d ' ')
	rule2_passed=$(echo "$packets" | ./firewall.exe "$rule2" | sort | tr -d ' ')
	rule3_passed=$(echo "$packets" | ./firewall.exe "$rule3" | sort | tr -d ' ')
	rule4_passed=$(echo "$packets" | ./firewall.exe "$rule4" | sort | tr -d ' ')  
	# packets that passed all 4
    tmp_passed=$(echo -e "$rule1_passed\n$rule2_passed\n$rule3_passed\n$rule4_passed" | sort | uniq -c | grep -E "^\s*4\s+" | awk '{print $2}') 
    packets_passed+=" $tmp_passed"
    # clean up
    unset rule1 rule2 rule3 rule4 rule1_passed rule2_passed rule3_passed rule4_passed tmp_passed            

done < <(echo "$all_rules" | awk '{sub(/#.*/, "", $0); print}' | awk 'NF')

packets_passed=$(echo "$packets_passed"| tr ' ' '\n' | awk 'NF' | sort | uniq)
echo "$packets_passed"

unset packets all_rules rules_file packets_passed