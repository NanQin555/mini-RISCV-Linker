#!/bin/bash

test_name=$(basename "$0" .sh)
target_dir=out/$test_name
source_dir=tests

cp ./build/rvld ./build/ld

mkdir -p "$target_dir"
riscv64-linux-gnu-gcc -o "$target_dir"/test.o -c "$source_dir"/test.c
riscv64-linux-gnu-gcc -B./build -static -o "$target_dir"/test "$target_dir"/test.o