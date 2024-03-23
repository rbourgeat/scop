if command -v glslc &> /dev/null; then
    glslc_path=$(command -v glslc)
else
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux
        glslc_path=$(find /home/$USER/ -type f -name glslc -executable | head -n 1)
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        # Mac OSX
        glslc_path=$(find /Users/$USER/ -type f -name glslc -executable | head -n 1)
    fi
fi

if [ -n "$glslc_path" ]; then
    $glslc_path shader.vert -o vert.spv
    $glslc_path shader.frag -o frag.spv
else
    echo "Error: glslc not found in PATH or in specified directory."
    exit 1
fi
