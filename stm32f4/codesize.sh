#!/bin/bash

# this is a god awful hack

echo "ibase=16;" `objdump -x r5test.elf | grep text | grep -e "r5_" -e "crypto_" -e "xe" | colrm 1 24 | colrm 9 | tr 'a-f\n' 'A-F+'` 0 | bc

