cmake_minimum_required(VERSION 3.31)
project(PhotoDiodeTester)

set(LSL_DIR "${CMAKE_SOURCE_DIR}/liblsl")
include_directories(${LSL_DIR}/include)
link_directories(${LSL_DIR}/lib)


include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

add_executable(PhotoDiodeTester main.cpp)

target_compile_features(PhotoDiodeTester PRIVATE cxx_std_17)

target_link_libraries(PhotoDiodeTester
        PRIVATE SFML::Graphics
        PRIVATE lsl
)

add_custom_command(TARGET PhotoDiodeTester POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LSL_DIR}/bin/lsl.dll"
        $<TARGET_FILE_DIR:PhotoDiodeTester>
)