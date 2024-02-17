cmake_minimum_required(VERSION 3.15)

project(infs-usermode VERSION 0.1.0 LANGUAGES CXX C DESCRIPTION "Free and open-source external cheetos for CS2" HOMEPAGE_URL https://github.com/vsaint1/cs2-infestation )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

if(MSVC)

    set(CMAKE_GENERATOR_TOOLSET=143)
    set(CMAKE_GENERATOR_PLATFORM=x64)

    add_executable(${PROJECT_NAME}-${CMAKE_PROJECT_VERSION} src/main.cpp ${SOURCES})

    #target_link_libraries(${PROJECT_NAME} PRIVATE ntdll.lib)

else()
    message(FATAL_ERROR "Unsupported build")
endif()