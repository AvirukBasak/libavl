cmake_minimum_required(VERSION 3.10)
project(avl)

# Set the path to your source and include directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Collect all the source files
file(GLOB SRC_FILES ${SRC_DIR}/*.c)

# Add the library target for avl.a
add_library(avl STATIC ${SRC_FILES})
target_include_directories(avl PUBLIC ${INC_DIR})

# Specify the output directory for avl.a
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/target")

# Copy include/libavl.h to the target directory
file(COPY ${INC_DIR}/libavl.h DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/build/target")

# Add the executable for your tests/test.c
add_executable(run_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.c)
target_include_directories(run_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/build/target)

# Link the run_test with avl.a
target_link_libraries(run_test PUBLIC avl)

# Optionally, if you want to create a single target for both the library and the test program
# add_executable(avl ${SRC_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.c)
# target_include_directories(avl PUBLIC ${INC_DIR})

