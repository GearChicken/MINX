#include "MathHelper.h"

using namespace MINX;
using namespace MINX::Math;

int Math::Round(float x)
{
	int wholeNumber = (int)x;
	float dif = x - wholeNumber;
	if(x >= 0.5f)
	{
		return wholeNumber + 1;
	}
	return wholeNumber;
}

int Math::Round(double x)
{
	int wholeNumber = (int)x;
	float dif = x - wholeNumber;
	if(x >= 0.5f)
	{
		return wholeNumber + 1;
	}
	return wholeNumber;
}