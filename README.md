k4megat Tutorial
-------------------------------------------------------------------------------

This repo serves both as a tutorial/guide for using and writing k4megat components and 
as a temporary repo to host your own components without polluting the official k4megat
repo.

# Prerequisite #
Follow official [k4megat](https://github.com/MegMev/k4megat/tree/sim-dev) to install it.
Don't forget `source` to setup k4megat running environment.

# Build #
```bash
git clone https://github.com/MegMev/mgtut && cd mgtut
mkdir build && cd build
cmake ..
make -j10
```

**NOTE**
No need to `make install`.
This repo is designed for developing or prototyping your algorithm, tool etc.
The running environment can be configured in *build* directory directly.

# Run a job option #
There is a script named *run* and *mgtutenv.sh* under *build* directory if compilation succeed.

## Method 1 ##
One-time execution:
```bash
# under build directory
./run k4run ../examples/options/tut_rdm.py
```

## Method 2 ##
Session execution:
```bash
# under build directory
source mgtutenv.sh
k4run ../examples/options/tut_rdm.py
source 
```
# Use it as temporary development repo #
You can fork this repo into your own account then add a new algorithm either under *examples/component*
directly. Or better, make a new directory with similar structure as *examples* (or just copy and rename it
as a starting point).

Don't forget add the new directory into top CMakeList.txt as follows:
```cmake
add_subdirectory(YOUR_NEW_DIRECTORY)
```

Then, you are ready to go, just build as usual. 
