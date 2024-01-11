# scop

Basic 3D model viewer made with Vulkan, C++ and GLFW.

## Pre-requisites

Install Vulkan from [source](https://vulkan.lunarg.com/).

Linux:

```bash
sudo apt-get install -y libglfw3 libglfw3-dev libxxf86vm-dev libxi-dev
# For debug:
sudo apt-get install -y libvulkan-dev vulkan-validationlayers
```

Macos:

```bash
brew install glfw
# replace 1.3.268.1 by your VulkanSDK version
export DYLD_LIBRARY_PATH=/Users/$USER/VulkanSDK/1.3.268.1/macOS/lib/:$DYLD_LIBRARY_PATH
```

## Build

Normal:

```bash
make
```

Re-build:

```bash
make re
```

Build in debug mode:

```bash
make debug
```

## Run

```bash
./scop
```

## Sources

- https://vulkan-tutorial.com
