#!/bin/bash 

#missing print in results.csv and spacing 
#pulls the relevant links from the site and saving it in the variable articles
site="https://ynetnews.com/category/3082"
data=$(wget --no-check-certificate -O - $site 2>/dev/null)
articles=$(echo "$data" | \
            grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+")

#prints how many unique articles exsist by sorting and removing doubles
sarticles=$(echo "$articles" | sort -u)
count=$(echo "$sarticles" | wc -l)
(echo " $count ") > results.csv 

#goes through all articles
echo "$sarticles" | while read article; do
    (echo -n "$article,") >> results.csv
    #pulls data from an article and filter all words but the names below
    data_article=$(wget --no-check-certificate -O - $article 2>/dev/null)
    only_name=$(grep -o 'Netanyahu\|Gantz\|Bennett\|Peretz' <<< "$data_article")

    counter=$( echo "$only_name" | wc -w)
    if [[ "$counter" -eq 0 ]]; then #there are no relevant names in the article
         (echo "-") >> results.csv
         else
            #counts how many times each name appears in the article and prints
            # it's name it's count
            for name in Netanyahu Gantz Bennett Peretz; do
                 count_name=$(echo "$only_name" | grep -o "$name" | wc -w)
                 (echo -n "$name,$count_name")  >> results.csv
                 [[ "$name" != "Peretz" ]] && (echo -n ",") >> results.csv
            done
        (echo "") >> results.csv
    fi
 
done









