# WORK IN PROGRESS
# May not need to use cmake -- we might not get anything out of it
# since we're simply linking a small C file against a rust library

cmake_minimum_required(VERSION 3.10)
project(rust-mysql-plugin)

# Compile options
set(MYSQL_OPTS -DMYSQL_DYNAMIC_PLUGIN -DMYSQL_ABI_CHECK -fpic)

# Shared library target to be built
add_library(auth_simple SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/plugin.c
)

target_compile_options(auth_simple PUBLIC "$<$<CONFIG:DEBUG>:${MYSQL_OPTS}>")
target_compile_options(auth_simple PUBLIC "$<$<CONFIG:RELEASE>:${MYSQL_OPTS}>")

target_link_libraries(auth_simple PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/target/debug/librust_mysql_plugin.a
  pthread
  dl
)
target_include_directories(auth_simple PUBLIC
  /usr/include/mysql
)

# Run cargo build before building the auth_simple target
add_custom_target(lib_rust_funcs
  COMMAND cargo build
)
add_dependencies(auth_simple lib_rust_funcs)
