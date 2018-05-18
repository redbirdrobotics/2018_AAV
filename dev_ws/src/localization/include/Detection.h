#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"

#ifndef DETECTION_CLASS
#define DETECTION_CLASS

// Author: Lukas Armstrong & Alex Rickert
// Date: 3/15/18
// Description:
// Class which is used to set up and utilize detectors on images

/*
	Container Descriptions:
		a_rects:
		ROI coordinates which contain possible objects of interest
		a_contours:
		Group of contours calculated from an image
		a_contoursPoly:
		A simpler, sparse representation of the previously calculated contours
		a_hierarchy:
		LOOK THIS UP

	Function Descriptions

*/


class Detection
{
private:
	// Find Contours Containers
	// Level 1 Search
	std::vector<cv::Rect> a_rectList;
	std::vector< std::vector< cv::Point > > a_contours1, a_contours2;
	std::vector< cv::Vec4i > a_hierarchy;
	std::vector< std::vector< cv::Point > > a_contoursPoly1;

	//Level 2 Search
	std::vector<cv::Rect> a_rectList2;
	std::vector< std::vector< cv::Point > > a_contours2;
	std::vector< std::vector< cv::Point > > a_contoursPoly2;


	// Connected Components Containers


	// Read from XML
	// CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE

public:
	std::vector<int> a_redThresh1 = {0,0,0,0,0,0};
	std::vector<int> a_redThresh2 = {0,0,0,0,0,0};
	std::vector<int> a_greenThresh = {0,0,0,0,0,0};
	std::vector<int> a_whiteThresh = {0,0,0,0,0,0};
	std::vector<int> a_blackThresh = {0,0,0,0,0,0};

	std::vector< std::vector< int > > a_threshList = {a_redThresh1, a_redThresh2, a_greenThresh, a_whiteThresh, a_blackThresh};
	std::vector< std::vector< int > > a_redRobotThresh = {a_redThresh1, a_redThresh2, a_blackThresh, a_whiteThresh};

	cv::Mat* a_pHSVImg;
	cv::Mat* a_pMask;

	std::vector< std::vector<cv::Mat*> > a_filterImgList;

	int a_pixelThresh;

	Detection(int);
	// static std::vector<cv::Mat> findColors(std::vector<cv::Mat>, std::vector<int>, std::vector<cv::Mat>);
	// static std::vector<cv::Mat> findColors(std::vector<cv::Mat>, std::vector<int>, std::vector<int>, std::vector<cv::Mat>, std::vector< cv::Mat >);

	void applyFilter(cv::Mat*, cv::Mat*, std::vector<int>);
	void applyAllFilters(std::vector<cv::Mat*>, std::vector< std::vector<cv::Mat*> >, std::vector< std::vector<int> >);

	static std::vector<cv::Mat> findRobots(std::vector<cv::Mat>, std::vector<cv::Mat>);
	//static std::vector<cv::Mat> search(std::vector<cv:, std::vector<cv::Rect>, std::vector<std::vector<cv::Point>>, std::vector<cv::Vec4i>, std::vector<std::vector<cv::Point>>, std::vector<cv::Mat>);

};

#endif
