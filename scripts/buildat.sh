# Builds in specific directory
cd $1
echo "Build in" $1
cmake ..
make
./SmeltTests