# ccom
Console drawing program (will be a library) with compositing.
Provides a friendly object-oriented C++17 interface for drawing in console.
Work in progress, the project is not yet ready

## Building
### Using Meson
**Prerequisites**: [Meson build system](https://mesonbuild.com/), [Ninja](https://ninja-build.org/), C++ compiler supporting C++17

```sh
# Create a build directory
mkdir build

# Run Meson
meson build

# Build project with ninja
ninja -C build

# Executable file: build/main
```

### Using sh3
**Prerequisites**: [sh3](https://github.com/kodo-pp/sh3/), C++ compiler supporting C++17

```sh
# Run sh3
sh3 build

# Executable file: ./main
```
