## derelict engine
# Yet Another Rendering Engine, Why?
This is actually my 4 or 5th attemp at writing a rendering engine. The reason for building another rendering engine, despite there being countless others, is because I want to know how game engines/modeling/animation software work. I thought this would be a good way to learn how they at least do the rendering portion of it.

The aim of this project is to first get the engine to a state where I can draw 2D shapes (it can already do this if you run the project), later on... 3D shapes, and all the other bells and whistles that come with a rendering engine such as scene loading, model loading, lighting, etc.

## How to Run it
So far I've tested this only on macOS that supports OpenGL 4.1, so ymmv on other operating systems, I'm taking advantage of CMake, the dependencies of the project also use CMake (thankfully), so building should be relatively simple and straightforward. The general build steps would be like this:
1. Clone the repo.
```
git clone --recursive https://github.com/zenitopires/derelict
```
2. Generate the build files.
```
cd derelict
cmake -S . -B build
```
2. Then build the library and the example executable.
```
cmake --build build
```
3. Finally run the example.
```
cd build/examples
./derelict_example
```
If all goes well. You should see a colorful rectangle drawn on your screen.

# Libraries
Check out the dependencies of the project [here](docs/libraries.md)!
