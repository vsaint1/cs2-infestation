@ECHO off

ECHO Detecting conan profile

conan profile detect --force

ECHO Installing depencencies

conan install . --build=missing --settings=build_type=Release

ECHO Building in progress

cmake -S . -B ./build

ECHO Building project release build

cmake --build ./build --config Release --target ALL_BUILD -j 14

ECHO Release build done
