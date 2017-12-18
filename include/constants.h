#ifndef CRS_PORR_CONSTANTS_H
#define CRS_PORR_CONSTANTS_H

class Constants{
    public:

        static inline constexpr int NUMBER_OF_THREADS[5] = {2, 4, 8, 16, 32};
        static inline constexpr int N_ARRAY[5] = {2, 10, 20, 50, 100};
        static inline constexpr double EPSILON[4] = {1e-2, 1e-4, 1e-6, 1e-8};
};

#endif //CRS_PORR_CONSTANTS_H
