#!/bin/bash

# this is a god awful hack (just sums up sizes of all relevant functions)

echo "ibase=16;" `arm-none-eabi-objdump -x r5test.elf | grep ".text" | \
	grep -e "r5_" -e "crypto_" -e "xe" -e "ct_" | \
	colrm 1 24 | colrm 9 | tr 'a-f\n' 'A-F+'` 0 | bc


