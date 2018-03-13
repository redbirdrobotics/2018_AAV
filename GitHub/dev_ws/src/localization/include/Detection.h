#include <iostream>
//#include <boost/make_shared.hpp>
//#include <boost/thread/mutex.hpp>
#include "opencv2/opencv.hpp"
//#include <X11/Xlib.h>
//#include <boost/thread.hpp>
#include "opencv2/features2d.hpp"
#include "Camera.h"

#ifndef DETECTION_CLASS
#define DETECTION_CLASS

class Detection{
private:

public:
	static std::vector<cv::Mat> findColors(std::vector<cv::Mat>, std::vector<int>, std::vector<cv::Mat>);
	static std::vector<cv::Mat> findColors(std::vector<cv::Mat>, std::vector<int>, std::vector<int>, std::vector<cv::Mat>, std::vector< cv::Mat >);
	static std::vector<cv::Mat> findRobots(std::vector<cv::Mat>, std::vector<cv::Mat>);
};

#endif