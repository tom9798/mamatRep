#!/bin/bash
today=$2
json_data=$(awk -F, '{print$1}' $1)
declare -A city_counts
echo $json_data
while IFS= read -r city; do
    if [[ -n "$city" ]]; then
	city="${city//\'/\\\'}"
        ((city_counts["$city"]++))
    fi
done < <(echo "$json_data" | grep -oP '{[^}]*}' | grep "$today" | grep -oP '"data": *\K"[^"]*"' | tr -d '"')
for city in "${!city_counts[@]}"; do
    echo "${city_counts[$city]} $city"
done | sort -nr
