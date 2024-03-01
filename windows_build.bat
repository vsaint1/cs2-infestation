@ECHO off
set ARG=%1

if %1 == --release (
conan install ./usermode --output-folder=build --build=missing --settings=build_type=Release

cd build

cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake

cmake --build . --config Release -j 14
)

if %1 == --debug (
conan install ./usermode --output-folder=build --build=missing --settings=build_type=Debug

cd build

cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake

cmake --build . --config Debug -j 14
)