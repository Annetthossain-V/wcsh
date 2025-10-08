cmake_minimum_required(VERSION 3.20)
project(wcsh CXX)

file(GLOB SRCS "src/*.cxx" "src/core/*.cxx" "src/format/*.cxx" "src/var/*.cxx" )

add_executable(${PROJECT_NAME} ${SRCS})

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE
  -I/home/annetthossain/include/
  $<$<CONFIG:Debug>: -g -O0 -Wall -Wextra>
  $<$<CONFIG:Release>: -O3 -DNDEBUG -fstack-protector -mtune=native -march=x86-64-v2>
)

target_link_options(${PROJECT_NAME} PRIVATE
  -L/usr/local/lib/
  -L/home/annetthossain/lib/
  $<$<CONFIG:Debug>: -fsanitize=address>
  $<$<CONFIG:Release>: -Wl,-O2 -flto>
)

target_link_libraries(${PROJECT_NAME} PRIVATE readline extr)
