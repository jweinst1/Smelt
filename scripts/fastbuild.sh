
# For running in one command
mkdir -p build
cd build
cmake ..
make
./SmeltTests
cd ..
rm -rf build
