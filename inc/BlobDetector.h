#include <iostream>
//#include <boost/make_shared.hpp>
//#include <boost/thread/mutex.hpp>
#include "opencv2/opencv.hpp"
//#include <X11/Xlib.h>
//#include <boost/thread.hpp>
#include "opencv2/features2d.hpp"
#include "Camera.h"

#ifndef BLOBDETECTOR_CLASS
#define BLOBDETECTOR_CLASS

class BlobDetector{
private:

public:
	static std::vector<cv::Mat> findReds(std::vector<cv::Mat>);
	static std::vector<cv::Mat> findGreens(std::vector<cv::Mat>);
	static std::vector<cv::Mat> findWhites(std::vector<cv::Mat>);
	static std::vector<cv::Mat> findBlacks(std::vector<cv::Mat>); //thats racist
	static std::vector<cv::Mat> findRobots(std::vector<cv::Mat>);
};

#endif
