# scop

Basic 3D model viewer made with Vulkan, C++ and GLFW.

![example](https://media.discordapp.net/attachments/1192056446389583874/1196157286629003264/Capture_decran_2024-01-14_a_19.21.15.png?ex=65b69b48&is=65a42648&hm=2644aa57d434f771fec8f64c117ebb027b8d09705667ed4eebd19a0bcd10cce8&=&format=webp&quality=lossless)

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

export DYLD_LIBRARY_PATH=/Users/$USER/VulkanSDK/$(ls -1 "/Users/$USER/VulkanSDK" | sort -V | tail -n 1)/macOS/lib/:$DYLD_LIBRARY_PATH
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

## Inputs

- → : rotate right

- ← : rotate left

- R : auto rotate

## Sources

- https://vulkan-tutorial.com

## ToDo List to optimize

- [ ] Add more smooth keyboard rotation
- [ ] https://developer.nvidia.com/vulkan-memory-management
