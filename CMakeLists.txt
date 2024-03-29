cmake_minimum_required(VERSION 3.17)
project(da_proj)

set(GCC_FLAGS_NORMAL "-pthread -Wall")
set(GCC_FLAGS_OPTIMIZE "-Ofast -fno-signed-zeros -fno-trapping-math -frename-registers -funroll-loops")
set(GCC_FLAGS_PARANOID "-g -pedantic -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport  -Winit-self  -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings") # -Weffc++ -Wpadded

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)

include_directories("algorithms/include" "structures/include" "utils/include" "controller/include" "view/include")
file(GLOB SRC "algorithms/src/*.cpp" "structures/src/*.cpp" "utils/src/*.cpp")
file(GLOB SRC_UI "controller/src/*.cpp" "view/src/*.cpp")
file(GLOB SRC_TEST "test/*.cpp")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("Detected GNU GCC, adding some compilation flags for da_proj")
    set(CMAKE_CXX_FLAGS "${GCC_FLAGS_NORMAL}")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 ${GCC_FLAGS_PARANOID}")
    set(CMAKE_CXX_FLAGS_RELEASE "${GCC_FLAGS_OPTIMIZE}")
endif ()

find_library(SFML_LIB NAMES sfml-graphics sfml-window sfml-system)
if(NOT SFML_LIB)
    message("DID NOT FIND SFML, COMPILING IT")
    add_subdirectory(lib/SFML)
    include_directories(lib/SFML/include)
endif()

include_directories(lib/earcut.hpp/include)

# ################ MAIN ################
add_executable(da_proj ${SRC} ${SRC_UI} "src/main.cpp")
target_link_libraries(da_proj sfml-graphics sfml-window sfml-system)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("Detected Linux, linking some libraries for project to work")
    target_link_libraries(da_proj pthread)
    target_link_libraries(da_proj X11)
endif()

# ################ TESTS ################
add_subdirectory("test/Catch2")
include_directories("test/Catch2/src")
add_executable(tests ${SRC_TEST} ${SRC})
target_link_libraries(tests PRIVATE Catch2WithMain)
include(CTest)
include(test/Catch2/extras/Catch.cmake)
catch_discover_tests(tests)

# ################ EVAL ################
add_executable(eval ${SRC} "eval/eval.cpp")
