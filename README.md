# Rockfell
![CI](https://github.com/IntriguingTiles/rockfell/workflows/CI/badge.svg)

This is a small cross-platform 2D game with a custom engine utilizing SDL2 for rendering.

# Building
Requires SDL2 and SDL2_image to be installed.

```
git clone https://github.com/IntriguingTiles/rockfell.git
cd rockfell
mkdir build
cd build
cmake ..
make
```

# Building for Wii U
Requires devkitPPC. wiiu-sdl2, wiiu-sdl2_image, and wiiu-libromfs must be installed from the [wiiu-fling](https://gitlab.com/QuarkTheAwesome/wiiu-fling) repository as the versions available in the default dkp-libs repository are broken.

```
git clone https://github.com/IntriguingTiles/rockfell.git
cd rockfell
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/wut/share/wut.toolchain.cmake ..
make
```