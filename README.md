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
make -j4
```
### I/O
---
Upon building the project with CMake, two script files will be generated. The first is `flash.sh`, used to automatically mount the Pico board and copy the binary UF2 file, and the second script `tty.sh` is used to connect to the board's serial output. You can do this manually instead if you like, but it requires a manual mount and copy. These two scripts require root access because of device look-up tables.

Note: When running `flash.sh`, make sure the board is reset by holding the BOOTSEL button, and repowering at the same time.