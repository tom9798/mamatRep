#!/bin/bash
today=$2
sed 's#},{#\n#g' $1 | grep $today | awk -F, '{print$1}' | awk -F: '{print$2}' | sed 's#"##g' | uniq -c | sort -nr
