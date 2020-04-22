#pragma once
#include <string>

#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

// TODO: add your methods here.
extern "C" DLL1_API float* generate_distribution(std::string which_data, const int length, const int rd_seed);
