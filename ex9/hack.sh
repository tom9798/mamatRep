#!/bin/bash

#solution file initial setup:
#Wow! Brazil is big.
#1 3 6 10 15 21
#0 0

#run a loop to check if the output contains 'BOOM!', if it does, add 1 to the second number in the third line of the solution file and run the vault program again
#!/bin/bash

# Run a loop to check if the output contains 'BOOM!', if it does, add 1 to the second number in the third line of the solution file and run the vault program again
while true; do
  # Run the vault program with solution.txt as an argument
  output=$(./vault solution.txt)
  # Check if the output contains 'BOOM!'
  if echo "$output" | grep -q 'BOOM!'; then
    # Adding 1 to the second number in the third line of the solution file
    awk 'NR==3 {$2=$2+1}1' solution.txt > temp.txt && mv temp.txt solution.txt
    #print the third line of the solution file
    sed -n '3p' solution.txt
    #print the output
    echo "$output"
  else
    echo "$output"
    break
  fi
done

## Run the vault program with solution.txt as an argument
#output=$(./vault solution.txt)
#
## Check if the output contains 'BOOM!'
#if echo "$output" | grep -q 'BOOM!'; then
#  #adding 1 to the second number in the third line of the solution file
#  sed -i '3s/0/1/' solution.txt
#  # Run the vault program with solution.txt as an argument
#  output=$(./vault solution.txt)
#  # Check if the output contains 'BOOM!'
#fi