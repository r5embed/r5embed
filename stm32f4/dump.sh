#!/bin/bash

UART=/dev/ttyUSB0
stty -F $UART 115200 cs8 -cstopb -parenb eof \^d
cat $UART
