# scop

Basic 3D model viewer made with Vulkan, C++ and GLFW.

![example](https://media.discordapp.net/attachments/859094290667143168/1195341166397374537/VirtualBox_ubuntu_12_01_2024_13_18_15.png?ex=65b3a336&is=65a12e36&hm=445ea2cc7007832f52a95a4d099e3ad104840f3e9cf34ff39c9882d1e993d26c&=&format=webp&quality=lossless)

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

## ToDo List to optimize

- [ ] https://developer.nvidia.com/vulkan-memory-management
