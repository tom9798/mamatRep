#!/bin/bash

# Run a loop to check if the output contains 'BOOM!', if it does, add 1 to the first number in the fourth line of the solution file and run the vault program again
while true; do
  # Run the vault program with solution.txt as an argument
  output=$(./vault solution.txt)
  # Print the output for debugging
  echo "Output: $output"
  # Check if the output contains 'BOOM!'
  if echo "$output" | grep -q 'BOOM!'; then
    # Adding 1 to the first number in the fourth line of the solution file
    awk 'NR==4 {$1=$1+1}1' solution.txt > temp.txt && mv temp.txt solution.txt
    # Print the updated fourth line for debugging
    echo "Updated line: $(awk 'NR==4' solution.txt)"
  else
    echo "$output"
    break
  fi
done