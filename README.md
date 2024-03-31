# scop

Basic 3D model viewer made with Vulkan, C++ and GLFW.

![42](https://i.ibb.co/ZcKRgJX/Virtual-Box-ubuntu-12-02-2024-15-19-50.png)

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

- `SPACE` : reset object position/rotation + camera

- `R, G, B, D` : color in red, green, blue or dark (like the subject)

- `T` : change topology

- `1, 2, 3` : increase X, Y, Z model position

- `SHIFT` + `1, 2, 3` : decrease X, Y, Z model position

- `4, 5, 6` : increase X, Y, Z model rotation

- `SHIFT` + `4, 5, 6` : decrease X, Y, Z model rotation

## Sources

- https://vulkan-tutorial.com

## ToDo List

- [ ] Add more material parameters

- [ ] Mipmaps

- [ ] Multisampling

- [ ] https://developer.nvidia.com/vulkan-memory-management
