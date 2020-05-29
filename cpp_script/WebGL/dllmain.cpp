// dllmain.cpp : Defines the entry point for the DLL application.
#include <array>
#include <random>
#include "Header.h"  // comment this out if this dllmain.cpp is included in Asset/Plugins/WebGL/


#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this

// ------------------------------------------------------------------------
// Plugin itself


// Link following functions C-style (required for plugins)
extern "C"
{
    float* generate_distribution(const char* which_data, const char* which_arm, const float mean_adjustment, const int length, const int rd_seed) {
        // in this case array are float pointers
        // so one cannot perform operations (addition, etc.) on array[i]
        // mathematical operation for distribution adjustment must be conducted in float numbers
        // before assigning into array[i]
        float* array = new float[length];
        std::default_random_engine rd_generator_optimal;
        std::default_random_engine rd_generator_suboptimal;

        rd_generator_optimal.seed(rd_seed);
        rd_generator_suboptimal.seed(rd_seed + 5231);

        if (strcmp(which_data, "gaussian") == 0) {
            std::normal_distribution<float> n_dist(0.0f, 1.0f);

            if (strcmp(which_arm, "optimal") == 0) {
                for (int i = 0; i < length; i++) {
                    float n_rd = n_dist(rd_generator_optimal) + mean_adjustment;
                    array[i] = n_rd;
                }
            }
            else if (strcmp(which_arm, "suboptimal") == 0) {
                for (int i = 0; i < length; i++) {
                    float n_rd = n_dist(rd_generator_suboptimal) + mean_adjustment;
                    array[i] = n_rd;
                }
            }
        }

        else if (strcmp(which_data, "exponential") == 0) {
            std::exponential_distribution<float> e_dist(1.0f);

            if (strcmp(which_arm, "optimal") == 0) {
                for (int i = 0; i < length; i++) {
                    float e_rd = -e_dist(rd_generator_optimal) + 1.0f + mean_adjustment;
                    array[i] = e_rd;
                }
            }
            else if (strcmp(which_arm, "suboptimal") == 0) {
                for (int i = 0; i < length; i++) {
                    float e_rd = e_dist(rd_generator_suboptimal) - 1.0f + mean_adjustment;
                    array[i] = e_rd;
                }
            }
        }

        else if (strcmp(which_data, "student_t") == 0) {
            std::student_t_distribution<float> t_dist(2.1f);

            if (strcmp(which_arm, "optimal") == 0) {
                for (int i = 0; i < length; i++) {
                    float t_rd = t_dist(rd_generator_optimal) + mean_adjustment;
                    array[i] = t_rd;
                }
            }
            else if (strcmp(which_arm, "suboptimal") == 0) {
                for (int i = 0; i < length; i++) {
                    float t_rd = t_dist(rd_generator_suboptimal) + mean_adjustment;
                    array[i] = t_rd;
                }
            }
        }

        return array;
    }

    int ReleaseMemory(int* pArray)
    {
        delete[] pArray;
        return 0;
    }

} // end of export C block extern "C"