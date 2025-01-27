##!/bin/bash
#export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
#
#packets=$(</dev/stdin)
#rules_file=$1
#all_rules=$(<$rules_file)
#
## keep packets that passed:
#packets_passed=""
## clean comments and empty lines:
#all_rules=$(echo "$all_rules" | awk '{sub(/#.*/, "", $0); if (NF) print}')
#
#while IFS= read -r rule; do
#    iter_rule="$rule"
#    # split to src-ip, dst-ip, src-port, dst-port
#    rule1=$(echo "$iter_rule" | cut -d',' -f1 | tr -d ' ')
#    rule2=$(echo "$iter_rule" | cut -d',' -f2 | tr -d ' ')
#    rule3=$(echo "$iter_rule" | cut -d',' -f3 | tr -d ' ')
#    rule4=$(echo "$iter_rule" | cut -d',' -f4 | tr -d ' ')
#	# insert packets file to run with each rule part
#   	rule1_passed=$(echo "$packets" | ./firewall.exe "$rule1" | sort | tr -d ' ')
#	rule2_passed=$(echo "$packets" | ./firewall.exe "$rule2" | sort | tr -d ' ')
#	rule3_passed=$(echo "$packets" | ./firewall.exe "$rule3" | sort | tr -d ' ')
#	rule4_passed=$(echo "$packets" | ./firewall.exe "$rule4" | sort | tr -d ' ')
#	# packets that passed all 4
#    tmp_passed=$(echo -e "$rule1_passed\n$rule2_passed\n$rule3_passed\n$rule4_passed" | sort | uniq -c | grep -E "^\s*4\s+" | awk '{print $2}')
#    packets_passed+=" $tmp_passed"
#    # clean up
#    unset rule1 rule2 rule3 rule4 rule1_passed rule2_passed rule3_passed rule4_passed tmp_passed
#
#done < <(echo "$all_rules" | awk '{sub(/#.*/, "", $0); print}' | awk 'NF')
#
#packets_passed=$(echo "$packets_passed"| tr ' ' '\n' | awk 'NF' | sort | uniq)
#echo "$packets_passed"

##unset packets all_rules rules_file packets_passed
#!/bin/bash

# Setting up the environment
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

# Reading input files and packets
rules_file="$1"
packets=$(cat)  # Reading packets from standard input
#packets=$(</dev/stdin)  # Reading packets from standard input
all_rules=$(grep -vE '^#|^$' "$rules_file")  # Filter out comments and empty lines directly

# Variable to collect packets that passed
passed_packets=""

# Loop to process each rule
while IFS=',' read -r src_ip dst_ip src_port dst_port; do
    # Removing unnecessary spaces
    src_ip=$(echo "$src_ip" | tr -d ' ')
    dst_ip=$(echo "$dst_ip" | tr -d ' ')
    src_port=$(echo "$src_port" | tr -d ' ')
    dst_port=$(echo "$dst_port" | tr -d ' ')

    # Processing each rule using firewall.exe
    matching_packets=$(echo "$packets" | ./firewall.exe "$src_ip" | \
                        ./firewall.exe "$dst_ip" | \
                        ./firewall.exe "$src_port" | \
                        ./firewall.exe "$dst_port")

    # Adding the packets that passed to the variable
    passed_packets+="$matching_packets"$'\n'

done <<< "$all_rules"
