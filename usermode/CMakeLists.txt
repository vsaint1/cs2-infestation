project(infestation VERSION 1.5.0 LANGUAGES CXX C DESCRIPTION "Free and open-source external cheetos for CS2" HOMEPAGE_URL https://github.com/vsaint1/cs2-infestation)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/build/generators/conan_toolchain.cmake)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


if (MSVC)

    set(CMAKE_GENERATOR_TOOLSET=v143)

elseif (LINUX)

    message(FATAL_ERROR "Unsupported linux build system")

else ()

    message(FATAL_ERROR "Unsupported unix build system")

endif ()

find_package(ZLIB REQUIRED)
find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE IMGUI  ${CMAKE_CURRENT_SOURCE_DIR}/external/include/imgui/*.cpp)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES} ${IMGUI})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/include)

target_link_libraries(${PROJECT_NAME} spdlog::spdlog ZLIB::ZLIB glfw OpenGl32 )
