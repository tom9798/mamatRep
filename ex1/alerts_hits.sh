#!/bin/bash
alarmsJson=$(wget -qO- "https://alerts-history.oref.org.il/Shared/Ajax/GetAlarmsHistory.aspx?lang=en")
declare -A city_counts
while IFS=read -r city; do
	if [[ -n "$city"]]; then
		((city_counts["$city"]++))
	fi
done < <(echo "$alarmsJson" | grep -oP '"data": *\k"' | tr -d '"')
sorted_cities=($(for city in 
array= (echo -e $alarmsJson|)
echo $array
