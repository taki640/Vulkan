#pragma once

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

#ifdef NDEBUG
#define RELEASE
#else
#define DEBUG
#endif

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
