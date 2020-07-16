# Prerequisites

## CMake
This project uses CMake version 3.10. Download CMake for whatever platform and toolchain you're building with. 

## Prerequisites for Linux, cygwin, or WSL (gcc)
Download the following development libraries using `apt-get` or the cygwin installer:
- SDL2
- libGL
- GLEW

If you're building this on Windows using cygwin or WSL, you will need Xming.

## Prerequisites for Windows (MinGW)
You need the following libraries
- SDL2
- opengl32
- GLEW

You will have to compile GLEW from source using MinGW, as the binaries they provide are
for VisualStudio. IIRC, there was a small issue compiling GLEW with MinGW that was solved by adding this
after line 157 in the GLEW Makefile:
```
ifeq ($(filter-out mingw% cygwin,$(SYSTEM)),)
BIN.LIBS := $(BIN.LIBS:-nostdlib=)
endif
```

Once the libraries are built, copy the library files like so:
- *.h files go in MinGW/include
- lib*.a files go in MinGW/lib
- *.dll files go in MinGW/bin

## Prequisites for Windows (MSVC)
TBW

# Building

## Building on linux, cygwin, or WSL (gcc)
To compile it do the following:
```shell script
mkdir build
cd build
cmake ..
make game
```

The 'game' (or 'game.exe') executable be created in the build/ directory.

**Important Note**: If you're building with cygwin or WSL, you have to execute the binary from a cygwin or WSL
terminal. You can't just click on it and run it. Make sure Xming is running or it will say something like "No available
video device"

## Building on Windows (MinGW)
To compile it do the following:
```shell script
mkdir build
cd build
cmake -DMINGW=1 -G "CodeBlocks - MinGW Makefiles" ..
mingw32-make game
```

You can click to run the game. It currently opens a console window, which I'm not sure how to fix right now, but w/e.

## Building on Windows (MSVC)
TBW

#TODOS
- Normals not being calculated correctly in OBJs
- Accepting input
- Scene Management