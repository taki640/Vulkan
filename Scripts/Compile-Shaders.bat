@echo off

echo Compiling shaders...
pushd ..\Vulkan\Shaders

%VULKAN_SDK%\Bin\glslc.exe shader.vert -o vert.spv
%VULKAN_SDK%\Bin\glslc.exe shader.frag -o frag.spv

popd

pause