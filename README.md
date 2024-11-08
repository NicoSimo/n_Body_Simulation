# N-BODY SIMULATION

## About this project 

N-Body Simulation for the CMDA4634 class at Virginia TECH during the Fall '24 semester.
The purpose of this project is to apply C++ and CUDA while learning about physics simulators.

## How to run the project
``` bash
mkdir build
```

Move inside the new build directory
``` bash
cd build
``` 

Build a Makefile using cmake.
``` bash
cmake ..
```

Compile the program using the Makefile.
``` bash
make
```

Run the compiled program following this structure:
``` bash
./nbody_simulation number_of_bodies
```

### Requirements 

**macOS**

- **CMake**
    ``` bash
    brew install cmake 
    ```

- **GLFW**
    ``` bash
    brew install glfw
    ```

- **GLM**
    ``` bash
    brew install glm
    ```
