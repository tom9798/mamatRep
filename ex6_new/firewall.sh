

#!/bin/bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
packets=$(</dev/stdin)
rules_file=$1
all_rules=$(<$rules_file)
packets_passed=""
all_rules=$(awk '{sub(/#.*/, ""); if (NF) print}' "$rules_file")
while IFS= read -r rule; do
  iter_rule="$rule"
  IFS=',' read -r src_ip dst_ip src_port dst_port <<< "$iter_rule"
  src_ip=${src_ip// /}
  dst_ip=${dst_ip// /}
  src_port=${src_port// /}
  dst_port=${dst_port// /}
  # process packets with all rules in one go
  out=$(echo "$packets" | ./firewall.exe "$src_ip" | ./firewall.exe "$dst_ip" | ./firewall.exe "$src_port" | ./firewall.exe "$dst_port" | tr -d ' ' | sort)
  packets_passed+=" $out"
    unset rule1 rule2 rule3 rule4 out
done <<< "$all_rules"
packets_passed=$(echo "$packets_passed" | tr ' ' '\n' | awk 'NF' | sort)
echo "$packets_passed"




###!/bin/bash
#export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
#packets=$(</dev/stdin)
#rules_file=$1
#all_rules=$(<$rules_file)
#packets_passed=""
#all_rules=$(awk '{sub(/#.*/, ""); if (NF) print}' "$rules_file")
#while IFS= read -r rule; do
#    iter_rule="$rule"
#    IFS=',' read -r rule1 rule2 rule3 rule4 <<< "$iter_rule"
#    rule1=${rule1// /}
#    rule2=${rule2// /}
#    rule3=${rule3// /}
#    rule4=${rule4// /}
#    # process packets with all rules in one go
#    out=$(echo "$packets" | ./firewall.exe "$rule1" | ./firewall.exe "$rule2" | ./firewall.exe "$rule3" | ./firewall.exe "$rule4" | sort | tr -d ' ')
#   packets_passed+=" $out"
#    unset rule1 rule2 rule3 rule4 out
#done <<< "$all_rules"
#packets_passed=$(echo "$packets_passed"| tr ' ' '\n' | awk 'NF' | sort)
#echo "$packets_passed"