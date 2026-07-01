#include "Utils.h"

#include <random>
double RandomDouble(double min, double max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distrib(min, max);
    return distrib(gen);

}
float RandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);

}
int RandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);

}