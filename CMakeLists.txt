cmake_minimum_required(VERSION 3.10)
project(ObjektinisProg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CONTAINER "vector" CACHE STRING "Container type to use (vector, list, deque)")
set_property(CACHE CONTAINER PROPERTY STRINGS vector list deque)

string(TOUPPER ${CONTAINER} CONTAINER_UPPER)

set(SOURCES
    src/main.cpp
    src/mylib.cpp
)

add_executable(${CONTAINER} ${SOURCES})
target_include_directories(${CONTAINER} PRIVATE src)
target_compile_definitions(${CONTAINER} PRIVATE USE_${CONTAINER_UPPER})

add_executable(test test/main.cpp)
target_include_directories(test PRIVATE src)

install(TARGETS ${CONTAINER} test
    RUNTIME DESTINATION bin
)