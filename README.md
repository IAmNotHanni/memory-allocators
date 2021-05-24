My experimental playground for allocators based on C++17.
This could be of potential interest for the [Inexor project](https://github.com/inexorgame/vulkan-renderer).
Thanks to [Iceflower](https://github.com/IceflowRE) and [yeetari](https://github.com/yeetari) for the CMake+conan setup.


## How to build

On Windows, use Visual Studio 2019 and [CMake UI](https://cmake.org/runningcmake/).

On Ubuntu, use `cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Debug` and `cmake --build build`.
