@echo off

echo Compiling shaders...
pushd ..\Vulkan\Shaders
set vulkan_path=D:\tools\VulkanSDK\1.3.280.0
%vulkan_path%\Bin\glslc.exe shader.vert -o vert.spv
%vulkan_path%\Bin\glslc.exe shader.frag -o frag.spv
popd

pause