 #!/bin/bash

#check number of arguments and print error
if [[ $# != 1 ]] 
then
    echo "Wrong number of arguments" >&2
    exit 1
fi 

#verify the course is a 6 digit number
if [[ ${#1} != 6 ]]
then
    echo "Course not found" >&2
    exit 1
fi

#verify the course exists in the directory
if [[ ! -e "$1.txt" ]] 
then
    echo "Course not found" >&2
    exit 1
fi

#removes the course directory, only if it exists
#then creates new course_stat directory
if [[ -d "$1_stat" ]]
then
    rm -r "$1_stat"
fi
mkdir "$1_stat"

#creates histogram using our hist.exe
#and puts it in the requested directory and file
(./hist.exe $1.txt) > $1_stat/histogram.txt

#creates the statistics.txt and fills it
touch ./"$1_stat"/statistics.txt
./mean.exe $1.txt | tr -d '\n' >> "$1_stat"/statistics.txt
(echo -n -e '\t') >> "$1_stat"/statistics.txt
./median.exe $1.txt | tr -d '\n' >> "$1_stat"/statistics.txt
(echo -n -e '\t') >> "$1_stat"/statistics.txt
./min.exe $1.txt | tr -d '\n' >> "$1_stat"/statistics.txt
(echo -n -e '\t') >> "$1_stat"/statistics.txt
./max.exe $1.txt | tr -d '\n' >> "$1_stat"/statistics.txt
(echo -n -e '\t') >> "$1_stat"/statistics.txt
data=$(./hist.exe $1.txt -n_bins 100)

#counts how many grades are 55 and above
grade=0
total=0
total_grades=0
while read line; do
    num_grade=$(echo "$line" | awk '{print $2}')
    total_grades=$(( $total_grades + $num_grade ))
    if (( grade >= 55 )); then
        total=$(( $total + $num_grade ))
    fi
    (( grade++ ))
done < <(echo "$data")

#calculates the rellavant percentage and fills it in place 
percentage=$(( (100*$total)/$total_grades ))
echo "$percentage%" >> "$1_stat"/statistics.txt