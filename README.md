# scop

Basic 3D model viewer made with Vulkan, C++ and GLFW.

![example](https://media.discordapp.net/attachments/859094290667143168/1197530824971669514/VirtualBox_ubuntu_18_01_2024_14_19_04.png?ex=65bb9a7d&is=65a9257d&hm=62842d5a7221fa80a88fde016bf39588d2557c06a2fdd7fa1336ee9acad8fcdc&=&format=webp)

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
./scop "path/to/file.obj"
```

## Inputs

- `MOUSE` : rotate 3D object

- `SPACE` : reset position + rotation

- `R, G, B` : color in red, green or blue

- `1, 2, 3` : increase X, Y, Z model position

- `SHIFT` + `1, 2, 3` : decrease X, Y, Z model position

- `4, 5, 6` : increase X, Y, Z model rotation

- `SHIFT` + `4, 5, 6` : decrease X, Y, Z model rotation

## Sources

- https://vulkan-tutorial.com

## ToDo List to optimize

- [ ] Add more material parameters
- [ ] https://developer.nvidia.com/vulkan-memory-management
