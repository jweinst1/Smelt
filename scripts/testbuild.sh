# For running tests in one command
mkdir -p build
cd build
cmake ..
make
./SmeltLibTests
./SmeltHeaderTests
cd ..
rm -rf build
