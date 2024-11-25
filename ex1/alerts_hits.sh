#!/bin/bash

# Fetch the JSON data
json_data=$(wget -qO- "https://alerts-history.oref.org.il/Shared/Ajax/GetAlarmsHistory.aspx?lang=en")

# Get today's date in the format used in the JSON data
today=$(date +"%Y-%m-%d")

# Extract city names for alerts from today and count the number of occurrences
declare -A city_counts

while IFS= read -r city; do
    if [[ -n "$city" ]]; then
        ((city_counts["$city"]++))
    fi
done < <(echo "$json_data" | grep -oP '{[^}]*}' | grep "$today" | grep -oP '"data": *\K"[^"]*"' | tr -d '"')

# Convert the associative array to an array of "count city" and sort it
sorted_cities=($(for city in "${!city_counts[@]}"; do
    echo "${city_counts[$city]} $city"
done | sort -nr))

# Output the sorted array
for entry in "${sorted_cities[@]}"; do
    echo "$entry"
done
