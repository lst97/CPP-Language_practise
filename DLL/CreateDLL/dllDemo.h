#pragma once
#include "windows.h"

void Init();
void Destroy();
extern "C" _declspec(dllexport) void ExportFunction();
