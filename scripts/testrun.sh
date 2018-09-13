# For running tests in one command
echo "-Running Smelt Tests and Building-"
mkdir -p build
cd build
cmake ..
make
./SmeltLibTests
./SmeltHeaderTests
cd ..
rm -rf build
