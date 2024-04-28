cmake_minimum_required(VERSION 3.10)

project(DesktopPet)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_SOURCE_DIR}/bin)

include_directories(/mingw64/include)
link_directories(/mingw64/lib)

file(GLOB SRC_FILES "src/*.cpp")
add_executable(DesktopPet ${SRC_FILES})
target_link_libraries(DesktopPet SDL2 SDL2_image)
