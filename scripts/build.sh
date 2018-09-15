# Builds libraries and header
echo "Building Smelt Binaries, library and header"
mkdir -p build
cd build
cmake ..
make
cp ../include/Smelt.h Smelt.h
echo "Copied Smelt header to build/Smelt.h"
cp ../include/LibSmelt.h LibSmelt.h
echo "Copied Smelt lib header to build/LibSmelt.h"
cd ..
echo "Finished build."