#!/bin/bash
sed 's#},{#\n#g' $1 | grep $2 | awk -F, '{print$1}' | awk -F: '{print$2}' | sed 's#"##g' | uniq -c | sed 's#   ##g' | sort -nr
