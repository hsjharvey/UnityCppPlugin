#pragma once
#include <string>

#define DLL1_API __declspec(dllexport)

// TODO: add your methods here.
extern "C" DLL1_API float* generate_distribution(const char* which_data, const char* which_arm, const float mean_adjustment, const int length, const int rd_seed);
extern "C" DLL1_API int ReleaseMemory(int* pArray);