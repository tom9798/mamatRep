#!/bin/bash

# File name of the binary to debug
BINARY="./vault"

# The answer to the first phase
PHASE1_ANSWER="Wow! Brazil is big."

# Random input for the second phase
PHASE2_INPUT="1 2 3 4 5 6"

# Prepare the initial gdb commands file to find memory addresses
GDB_CMDS="gdb_cmds.txt"
cat <<EOF > $GDB_CMDS
set pagination off
break read_six_numbers
run
continue
# Inspect the stack to find the base address of the passcode numbers
x/24xw \$rsp
EOF

# Create an input file for the program, containing the answers to the first and second phases
echo -e "$PHASE1_ANSWER\n$PHASE2_INPUT" > input.txt

# Run gdb with the initial commands to find the memory addresses and capture the output
gdb -batch -x $GDB_CMDS --args $BINARY < input.txt > gdb_output.txt

# Extract the memory addresses from the gdb output
ADDRESSES=($(grep -A 24 'x/24xw' gdb_output.txt | grep '0x' | awk '{print $1}'))

# Check if the addresses were correctly identified
if [ ${#ADDRESSES[@]} -lt 6 ]; then
    echo "Error: Could not determine the correct memory addresses."
    exit 1
fi

# Only take the first six addresses
ADDRESSES=("${ADDRESSES[@]:0:6}")

# Create a new gdb commands file to set watchpoints and print values
cat <<EOF > $GDB_CMDS
break phase_2
run
continue
EOF

# Add watchpoints for each found address to the gdb commands file
for addr in "${ADDRESSES[@]}"; do
    echo "watch *(int *)($addr)" >> $GDB_CMDS
done

# Add commands to print the values at each address
for addr in "${ADDRESSES[@]}"; do
    echo "print *(int *)($addr)" >> $GDB_CMDS
done

# Add a command to quit gdb
echo "quit" >> $GDB_CMDS

# Run gdb with the new commands file
gdb -batch -x $GDB_CMDS --args $BINARY < input.txt > gdb_final_output.txt

# Extract and display the passcode numbers from the gdb output
echo "Passcode numbers:"
grep "\$" gdb_final_output.txt | awk '{print $NF}'

# Cleanup
rm $GDB_CMDS gdb_output.txt gdb_final_output.txt input.txt
