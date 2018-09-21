#!/bin/bash
gcc -I$TLPI_HDR -I$LIB $1 -lcrypt $TLPI_LIB -o `echo $1 | cut -d. -f1`
