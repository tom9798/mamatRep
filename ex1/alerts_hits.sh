#!/bin/bash
if ! command -v wget &> /dev/null; then 
	echo "no wget"
	exit 1
fi
json_data=$(wget -qO- "https://alerts-history.oref.org.il/Shared/Ajax/GetAlarmsHistory.aspx?lang=en")
today=$(date +"%Y-%m-%d")
declare -A city_counts
while IFS= read -r city; do
    if [[ -n "$city" ]]; then
	city="${city//\'/\\\'}"
        ((city_counts["$city"]++))
    fi
done < <(echo "$json_data" | grep -oP '{[^}]*}' | grep "$today" | grep -oP '"data": *\K"[^"]*"' | tr -d '"')
for city in "${!city_counts[@]}"; do
    echo "${city_counts[$city]} $city"
done | sort -nr
