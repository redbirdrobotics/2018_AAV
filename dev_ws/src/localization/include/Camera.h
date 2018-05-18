#include <iostream>
#include "opencv2/opencv.hpp"
#include <boost/make_shared.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <X11/Xlib.h>

#ifndef CAMERA_CLASS
#define CAMERA_CLASS

class Camera
{
private:
	cv::VideoCapture a_stream;
	uint32_t a_port;
	std::string a_ID;
	bool a_connect;
	std::vector< cv::Mat > a_frameList;
	int tegra_width, tegra_height, tegra_fps;
	std::string = tegra_pipline; 

public:
	Camera(std::string, uint32_t);
	bool getStatus();
	std::string getID();
	cv::Mat getFrame(cv::Mat, bool = false);
	std::string get_tegra_pipeline();

	static bool getListStatus(std::vector< Camera* >, int);
	static void updateFrameList(boost::shared_ptr< std::vector< cv::Mat > >, std::vector< Camera* >, int, boost::mutex&);
	static void updateFrameList(boost::shared_ptr< std::vector< std::vector< cv::Mat > > >, std::vector< Camera* >, int, boost::mutex&);
	static void showFrame(boost::shared_ptr< std::vector< cv::Mat > >, boost::shared_ptr< bool >, boost::shared_ptr< bool >, boost::mutex&);
};

#endif