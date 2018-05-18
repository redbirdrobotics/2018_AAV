#include <iostream>
#include <vector>

#ifndef ROBOT_CLASS
#define ROBOT_CLASS

class Robot
{
private:
	int a_color;
	int a_confidence;
	float x, y;
	float a_radius;

public:
	Robot(int color);
};

#endif