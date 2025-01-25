#!/bin/bash

# Function to update only the sixth row in the solution file
update_sixth_row() {
  local number=$1
  printf -v formatted_number "%06d" $number
  awk -v new_row="${formatted_number:0:1} ${formatted_number:1:1} ${formatted_number:2:1} ${formatted_number:3:1} ${formatted_number:4:1} ${formatted_number:5:1}" 'NR==6 {$0=new_row}1' solution.txt > temp.txt && mv temp.txt solution.txt
}

# Initialize the number
number=0

# Loop through all combinations of the six integers
while [ $number -le 999999 ]; do
  # Update the sixth row in the solution file
  update_sixth_row $number

  # Run the vault program with solution.txt as an argument
  output=$(./vault solution.txt)
  # Print the output for debugging
#  echo "Output: $output"

  # Check if the output contains 'BOOM!'
  if echo "$output" | grep -q 'BOOM!'; then
    # Increment the number
    number=$((number + 1))
  else
    echo "SUCCESS"
    break
  fi
done