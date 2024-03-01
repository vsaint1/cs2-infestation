conan install ./usermode --output-folder=build --build=missing --settings=build_type=Release

cmake -S . -B ./build -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake

cd build

cmake --build . --config Release -j 14