#include "HelloTriangleApp.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
    HelloTriangleApp app;

    try
    {
        app.Run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << "\n";
        return 1;
    }

    return 0;
}