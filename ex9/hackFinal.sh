#!/bin/bash

# Function to update the sixth row in the solution file
update_sixth_row() {
  local number=$1
  printf -v formatted_number "%06d" $number
  echo "Wow! Brazil is big." > solution.txt
  echo "1 3 6 10 15 21" >> solution.txt
  echo "0 749" >> solution.txt
  echo "132 4" >> solution.txt
  echo "5 115" >> solution.txt
  echo "${formatted_number:0:1} ${formatted_number:1:1} ${formatted_number:2:1} ${formatted_number:3:1} ${formatted_number:4:1} ${formatted_number:5:1}" >> solution.txt
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
  echo "Output: $output"

  # Check if the output contains 'BOOM!'
  if echo "$output" | grep -q 'BOOM!'; then
    # Increment the number
    number=$((number + 1))
  else
    echo "SUCCESS"
    break
  fi
done