cmake_minimum_required(VERSION 3.0)
project(rvld)

# Get version by git commit id
set(VERSION "0.1.0")
execute_process(
    COMMAND git rev-list -1 HEAD
    OUTPUT_VARIABLE COMMIT_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions(-DVERSION="${VERSION}" -DCOMMIT_ID="${COMMIT_ID}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions("-Wall -g")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=mold")

add_definitions( -DDEBUG )
# add_definitions( -D_GLIBCXX_DEBUG )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Src)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)