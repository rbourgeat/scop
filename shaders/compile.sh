glslc_path=$(find /home/$USER/ -type f -name glslc -executable | head -n 1)

if [ -n "$glslc_path" ]; then
    echo "Compiling shaders with: $glslc_path"
    $glslc_path shader.vert -o vert.spv
    $glslc_path shader.frag -o frag.spv
    echo "Shaders compiled successfully !"
else
    echo "Error: glslc not found in PATH."
    exit
fi