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
public:
	using port_id_t = uint8_t;
private:
	cv::VideoCapture _cam_stream;
	uint8_t _port;
	cv::Size _frame_size;
	uint8_t _fps;
	bool _connected;
	int tegra_width, tegra_height, tegra_fps;
	std::string tegra_pipline; 

public:
	Camera(uint8_t, cv::Size, uint8_t);
	bool GetStatus();
	uint8_t GetPort();
	cv::Mat GetFrame(cv::Mat);
	std::string get_tegra_pipeline();

	static void FillCamVect_Ptr(boost::shared_ptr< std::vector< Camera > >, uint8_t, cv::Size, uint8_t);
	static bool GetStatus_CamVect(boost::shared_ptr< std::vector< Camera > > camvect_ptr);
	static void UpdateFrameVect(boost::shared_ptr< std::vector< Camera > >, boost::shared_ptr< std::vector< cv::Mat > >, boost::mutex&);
	static void ShowFrameVect(boost::shared_ptr< std::vector< cv::Mat > >, boost::shared_ptr< bool >, boost::shared_ptr< bool >, boost::mutex&);
};

#endif