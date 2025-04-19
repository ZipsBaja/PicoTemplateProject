# Pico Template Project
This repo sums up a lot of work for you while programming on the Raspberry Pi Pico family controllers.

### How to Use
---
Clone this repo:
```
git clone https://github.com/ZipsBaja/PicoTemplateProject.git
```
and update the submodules with the following:
```
git submodule init && git submodule update
```
By default, the standard RP2040 Pico is selected, and if you are using the Pico W, Pico 2, or Pico 2 W, you'll need to swap lines in the `CMakeLists.txt` file.

This is found in the file:
```
# Comment these lines accordingly based on the board you are using!
set(PICO_BOARD pico)
# set(PICO_BOARD pico2)
# set(PICO_BOARD pico_w)
# set(PICO_BOARD pico2_w)
```
### Compiling
---
Use the standard compile procedure for CMake projects.
```
mkdir build
cd build
cmake ..
make
```
If you are compiling many items, use the `-jx` option in `make` to allocate more processor threads, where `x` is the number of threads. For the fastest compile time for your system, use `make -j$(nproc)`. 
### I/O
---
Upon building the project with CMake, two script files will be generated. The first is `flash.sh`, used to automatically mount the Pico board and copy the binary UF2 file, and the second script `tty.sh` is used to connect to the board's serial output. You can flash manually instead if you like, but it requires a manual mount and copy. These two scripts require root access because of device look-up tables and mount procedures.

Note: When running `flash.sh`, make sure the board is reset by holding the BOOTSEL button, and repowering at the same time.

## Legacy on Windows 10/11
If using Windows through a docker container, copying the binary file must be done with `docker cp`. Find the correct UF2 file from your container, and copy it to your Pico flash directory. For example, using a Windows terminal:
```
docker cp pico-sdk:/mnt/MyProject/build/MyProject.uf2 E:/MyProject.uf2
```
Mounting is done automatically in Windows.
If you want to see the standard serial output, use a tool like <i>Putty</i> to connect to the serial device that appears in Device Manager when serial print is enabled.