#!/bin/bash

# Set build options and flags
Opts="-DCLOVIX_SLOW=1 -DCLOVIX_DEBUG=1"
CommonCompileFlags="-g -O0 -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-missing-braces"
CommonIncludes="" 
CommonLibs="-lm -lpthread -lSDL3 -ldl -lvulkan -lXi -lX11 -lXxf86vm -lXrandr"

mkdir -p ../build
pushd ../build
rm -f *.o

clang++ $CommonCompileFlags $CommonIncludes $Opts ../code/entry_VulkanTest.cpp $CommonLibs -o "VulkanTest.out"

# Check for compilation success
if [ $? -ne 0 ]; then
    echo "==================="
    echo "Compilation Failure"
    echo "==================="
    exit 1
fi

# Return to the original directory
popd || exit 1

echo "===================="
echo "Compilation Complete"
echo "===================="

