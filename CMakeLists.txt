cmake_minimum_required(VERSION 3.15)
project(stm32c5_fdcan_anti_inversion C)

set(CMAKE_C_STANDARD 11)

# Library Sources
add_library(fdcan_anti_inversion
    Src/stm32c5_fdcan_anti_inversion.c
    Inc/stm32c5_fdcan_anti_inversion.h
)

target_include_directories(fdcan_anti_inversion PUBLIC
    Inc
)

# Enable strict compilation warnings for embedded safety practices
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(fdcan_anti_inversion PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
