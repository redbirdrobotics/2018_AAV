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
	std::vector<int> a_redThresh1 = {0,0,0,0,0,0}; 
	std::vector<int> a_redThresh2 = {0,0,0,0,0,0};
	std::vector<int> a_greenThresh = {0,0,0,0,0,0};
	std::vector<int> a_whiteThresh = {0,0,0,0,0,0};
	std::vector<int> a_blackThresh = {0,0,0,0,0,0};
};

#endif