#include <iostream>
#include <opencv2/opencv.hpp>

#ifndef CONSTANTS
#define CONSTANTS

namespace cam_consts
{
	uint8_t _NUM_CAMS_ = 1;
	cv::Size _FRAME_SIZE_ = cv::Size(640, 480);
	cv::Size _FOV_ = cv::Size(162,154);
}

namespace calib_consts
{
	cv::Size _BOARD_SIZE_ = cv::Size(1, 1);
	cv::Size _SEARCH_WIN_SIZE_ = cv::Size(5, 5);
	cv::Size _ZERO_ZONE_SIZE_ = cv::Size(-1, -1);
	int _NUM_IMGS_ = 30;
	int _MAX_ITERATIONS_ = 30;
	float _EPSILON_ = 0.1;
}

#endif