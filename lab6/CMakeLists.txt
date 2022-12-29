cmake_minimum_required(VERSION 3.24)
project(lab6 C)

set(CMAKE_C_STANDARD 11)

add_executable(server server/run.c server/server.c)
