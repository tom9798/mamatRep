#!/bin/bash

# File name of the binary to debug
BINARY="./vault"

# The answer to the first phase
PHASE1_ANSWER="Wow! Brazil is big."

# Addresses where the passcodes are stored
ADDRESSES=(
    "0x7fffffffdc00"
    "0x7fffffffdc04"
    "0x7fffffffdc08"
    "0x7fffffffdc0c"
    "0x7fffffffdc10"
    "0x7fffffffdc14"
)

# Prepare the gdb commands file
GDB_CMDS="gdb_cmds.txt"
cat <<EOF > $GDB_CMDS
break phase_2
run
EOF

# Add watchpoints for each address to the gdb commands file
for addr in "${ADDRESSES[@]}"; do
    echo "watch *(int *)($addr)" >> $GDB_CMDS
done

# Add commands to print the values at each address
for addr in "${ADDRESSES[@]}"; do
    echo "print *(int *)($addr)" >> $GDB_CMDS
done

# Add a command to quit gdb
echo "quit" >> $GDB_CMDS

# Create an input file for the program, containing the answer to the first phase
echo "$PHASE1_ANSWER" > input.txt

# Run gdb with the prepared commands file
gdb -batch -x $GDB_CMDS --args $BINARY < input.txt > gdb_output.txt

# Extract and display the passcode numbers from the gdb output
echo "Passcode numbers:"
grep "\$" gdb_output.txt | awk '{print $NF}'

# Cleanup
rm $GDB_CMDS gdb_output.txt input.txt
