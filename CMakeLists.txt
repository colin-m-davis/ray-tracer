cmake_minimum_required(VERSION 3.0.0)
project(stash VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_executable(main src/main.cpp)

foreach(target main)
    target_compile_options(${target} PRIVATE -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wunused)
endforeach()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
