cmake_minimum_required(VERSION 2.8)

project(memory-pool)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/include)

add_library(memory-pool SHARED src/Chunk.cpp)

install(TARGETS memory-pool DESTINATION /usr/lib)
install(FILES Pool.h DESTINATION /usr/include/MemoryPool)
install(FILES Allocator.h DESTINATION /usr/include/MemoryPool)