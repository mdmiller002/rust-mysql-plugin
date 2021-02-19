#!/bin/bash

echo "----- Building -----"
cargo build

MYSQL_ARGS="-DMYSQL_DYNAMIC_PLUGIN -DMYSQL_ABI_CHECK -fpic"
LIBS="-lpthread -ldl"
INCLUDES="-I /usr/include/mysql"
gcc $MYSQL_ARGS -shared -o libauth_simple.so \
$INCLUDES \
src/cpp/plugin.c \
target/debug/librust_mysql_plugin.a \
$LIBS

echo
echo "----- Uninstalling plugin in MySQL -----"
mysql -e "UNINSTALL PLUGIN auth_simple" || true

echo "----- Copying libraries -----"
cp libauth_simple.so /usr/lib/mysql/plugin

echo "----- Now installing the plugin -----"
mysql -e "INSTALL PLUGIN auth_simple SONAME \"libauth_simple.so\""
