#pragma once
#include <string>
#include <vector> 
double RandomDouble(double min, double max);
float RandomFloat(float min, float max);
int RandomInt(int min, int max);

std::string getTime();

 
 
template <typename T>
T* VectorGetByIndex(std::vector<T>& vec, int Index)
{
    if (Index < 0 || Index >= vec.size())
    {
        return nullptr;
    }
    return &vec[Index];
}