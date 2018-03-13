#ifndef ROBOT_CLASS
#define ROBOT_CLASS

class ROBOT
{
private:
	int a_color;
	int a_confidence;
	float x, y;
	float a_radius;
	std::vector<int> a_thresh1 (6,0); 
	std::vector<int> a_thresh2 (6,0);

public:
	ROBOT(int color);

};

#endif