cmake_minimum_required(VERSION 3.10)
project(avl)

# Set the path to your source and include directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Collect all the source files
file(GLOB SRC_FILES ${SRC_DIR}/*.c)

# Add the executable for your tests/test.c
add_executable(test_program ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.c)
target_include_directories(test_program PUBLIC ${INC_DIR})

# Add the library target for avl.a
add_library(avl STATIC ${SRC_FILES})
target_include_directories(avl PUBLIC ${INC_DIR})

# Link the test_program with avl.a
target_link_libraries(test_program PUBLIC avl)

# Specify the output directory for avl.a
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/target")

# Copy include/avl.h to the target directory
file(COPY ${INC_DIR}/avl.h DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/target")

# Optionally, if you want to create a single target for both the library and the test program
# add_executable(avl ${SRC_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.c)
# target_include_directories(avl PUBLIC ${INC_DIR})

