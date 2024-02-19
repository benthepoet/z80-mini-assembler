cmake_minimum_required(VERSION 3.0)

project(z80-mini-assembler LANGUAGES C)

add_executable(z80-mini-assembler main.c)

install(TARGETS z80-mini-assembler RUNTIME DESTINATION bin)
