#pragma once
#include "TinyNPY/TinyNPY.h"
#include <iostream>

NpyArray::npz_t getAllNumpyArray(const char* file);
NpyArray getSelectedNumpyArray(const char* layer, const char* file);
