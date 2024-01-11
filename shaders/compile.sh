glslc_path=$(find /home/$USER/ -type f -name glslc -executable | head -n 1)

if [ -n "$glslc_path" ]; then
    $glslc_path shader.vert -o vert.spv
    $glslc_path shader.frag -o frag.spv
else
    echo "Error: glslc not found in PATH."
    exit 1
fi