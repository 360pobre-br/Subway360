cmake_minimum_required(VERSION 3.25)
project(Subway360 C)

add_executable(Subway360 src/main.c)
set_target_properties(Subway360 PROPERTIES C_STANDARD 17 C_EXTENSIONS ON)
target_compile_options(Subway360 PRIVATE -Wall -Wextra -Werror)

# xsdk generates the Xbox 360 .xex from this native title.
xsdk_add_xex(Subway360 TITLE_ID 0x53554231 NAME "Subway360" VERSION 1.0.0.0)
