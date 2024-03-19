#pragma once

#include <random>

static const float GetRandomFloatNumber(float minValue, float maxValue)
{
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<float> distribution(minValue, maxValue); 

	return distribution(gen);
}

static const int GetRandomIntNumber(int minValue, int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(minValue, maxValue);

	return distribution(gen);
}

