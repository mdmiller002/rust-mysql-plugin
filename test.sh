#!/bin/bash

cargo build
gcc -g src/cpp/test.c target/debug/librust_mysql_plugin.a -o call_rust.out -lpthread -ldl
echo
echo "*** Built, now calling ***"
./call_rust.out
