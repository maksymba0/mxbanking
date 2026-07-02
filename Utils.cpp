#include "Utils.h"

#include <random>
#include <string>
#include <format>
#include <chrono>

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

std::string getTime()
{
    auto time = std::chrono::system_clock::now();
    
    auto ms = std::chrono::time_point_cast<std::chrono::seconds>(time);

    std::string result = std::format("[{:%H:%M:%S}]", ms);

    return result;
}