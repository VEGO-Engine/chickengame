This game serves as a sample for using the [VEGO-Engine](https://github.com/VEGO-Engine/Engine).

### Usage

The game compiles to an executable, for which the following prerequisites need to be met:

- A C++ compiler, for example GCC
  - On Windows you can use GCC via [MinGW](https://www.mingw-w64.org/)
- CMake

The game can then be cloned and compiled with the following commands:

```sh
git clone --recurse-submodules -j8 https://github.com/VEGO-Engine/chickengame.git
cmake -S . -B build
cmake --build build
```

Depending on the system, you might need to specify which generator to use, for example on a Windows system using MinGW:

```sh
git clone --recurse-submodules -j8 https://github.com/VEGO-Engine/chickengame.git
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

Compiling the whole game might take a while, since SDL and the engine also have to be compile first. Once it is done, the executable can be found in `build/chickengame.exe`
