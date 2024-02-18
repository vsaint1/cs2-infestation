@ECHO off

ECHO Installing depencencies

conan install . --build=missing

ECHO Building in progress

cmake -S . -B ./build

ECHO Building project release build

cmake --build ./build --config Release --target ALL_BUILD -j 14

ECHO Release build done
