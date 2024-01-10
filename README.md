# scop

Basic GPU rendering with Vulkan

## Pre-requisites

Install Vulkan from [source](https://vulkan.lunarg.com/).

```bash
# Linux:
sudo apt-get install -y libglfw3 libglfw3-dev libxxf86vm-dev libxi-dev

# MacOS:
brew install glfw
export DYLD_LIBRARY_PATH=/Users/$USER/VulkanSDK/1.3.268.1/macOS/lib/:$DYLD_LIBRARY_PATH
# replace 1.3.268.1 by your VulkanSDK version
```

## Build

```bash
make
```

## Run

```bash
./scop
```

## Sources

- https://vulkan-tutorial.com
