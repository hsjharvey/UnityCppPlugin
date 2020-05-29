// dllmain.cpp : Defines the entry point for the DLL application.
#include <string>
#include "framework.h"
#include <array>
#include <random>


#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

// ------------------------------------------------------------------------
// Plugin itself


// Link following functions C-style (required for plugins)
extern "C"
{

	// The functions we will call from Unity.
	//
	EXPORT_API const char* PrintHello() {
		return "Hello";
	}

	EXPORT_API int PrintANumber() {
		return 5;
	}

	EXPORT_API int AddTwoIntegers(int a, int b) {
		return a + b;
	}

	EXPORT_API float AddTwoFloats(float a, float b) {
		return a + b;   
	}

	EXPORT_API float* generate_distribution(const char* which_data, const int length, const int rd_seed) {
        using namespace std;
        float* array = new float[length];
        default_random_engine rd_generator;
        rd_generator.seed(rd_seed);


        // initialize distribution
        normal_distribution<float> n_dist(0.0, 1.0);
        student_t_distribution<float> t_dist(1.1);
        exponential_distribution<float> e_dist(1);

        if (strcmp(which_data, "gaussian") == 1) {
            for (int i = 0; i < length; i++) {
                float n_rd = n_dist(rd_generator);
                array[i] = n_rd;
            }
        }
        else if (strcmp(which_data, "student_t") == 1) {
            for (int i = 0; i < length; i++) {
                float t_rd = t_dist(rd_generator);
                array[i] = t_rd;
            }
        }
        else if (strcmp(which_data, "exponential") == 1) {
            for (int i = 0; i < length; i++) {
                float e_rd = e_dist(rd_generator);
                array[i] = e_rd;
            }

        }

        return array;
    }

    EXPORT_API int* test()
    {
        int len = 5;
        int* arr = new int[len + 1];
        arr[0] = len;
        arr[1] = 1;
        arr[2] = 2;
        arr[3] = 3;
        arr[4] = 4;
        arr[5] = 5;
        return arr;
    }

    EXPORT_API int ReleaseMemory(int* pArray)
    {
        delete[] pArray;
        return 0;
    }

} // end of export C block