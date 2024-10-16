#!/bin/bash

test_name=$(basename "$0" .sh)
target_dir=out/$test_name
source_dir=tests

mkdir -p "$target_dir"

riscv64-linux-gnu-gcc -o "$target_dir"/test.o -c "$source_dir"/test.c

./build/Linker "$target_dir"/test.o