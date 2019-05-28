#!/bin/bash

#
# For a given scale target, run multiple load-byte ttest experiments for
# different numbers of fixed bytes.
#
# Make sure to run this script from $UAS_ROOT to make sure it
# will run properly.
#
# Usage:
#
#   $> ./experiments/memory-bus/bus-width/scale-ttest-all.sh <target> <serial port>
#

TT_NAME=bus-width-10k

# Exit on first failed command.
set -e

#
# Build
make -B build_$1_memory-bus-bus-width

#
# Program
make -B program_$1_memory-bus-bus-width USB_PORT=$2

#
# TTests
# arg 0 - target platform
# arg 1 - number of fixed bytes
# arg 2 - serial port.
function run_ttest {
make -B -f Makefile \
        USB_PORT=$3 \
        TTEST_NAME=${TT_NAME}/$2 \
        TTEST_FLAGS="-k --fixed-byte-len $2 --fixed-value 0x73b2ccfd6a39f20f" \
        TTEST_NUM_TRACES=10000 \
        TTEST_CAPTURE=./experiments/memory-bus/bus-width/ttest.py \
        ttest_$1_memory-bus-bus-width
}

pwd

run_ttest $1 0 $2
run_ttest $1 1 $2
run_ttest $1 2 $2
run_ttest $1 3 $2
run_ttest $1 4 $2
run_ttest $1 5 $2
run_ttest $1 6 $2
run_ttest $1 7 $2

${UAS_ROOT}/experiments/memory-bus/bus-width/ttest_graph.sh $1 ${TT_NAME}

