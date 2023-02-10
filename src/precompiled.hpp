#pragma once

#include <cassert>
#include <cstdlib>
#include <cstddef>

#include <iostream>
#include <fstream>
#include <istream>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <random>
#include <ctime>
#include <source_location>

#include <comdef.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <Windows.h>
#include <filesystem>

#include "Utils/ErrorChecking.hpp"
#include "Utils/Constants.hpp"
#include "Utils/D3DSafeRelease.hpp"

#include "Singletons/D3D/D3D.hpp"