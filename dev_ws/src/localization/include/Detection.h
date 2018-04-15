#include "Robot.h"
#include <boost/make_shared.hpp>

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
	std::vector<cv::Rect> a_greenRectList;
	std::vector<cv::Rect> a_redRectList;
	std::vector<cv::Rect> a_blackRectList;
	std::vector<cv::Rect> a_whiteRectList;
	std::vector< std::vector< cv::Point > > a_contours1;
	std::vector< cv::Vec4i > a_hierarchy;
	std::vector< std::vector< cv::Point > > a_contoursPoly;

	//Level 2 Search
	std::vector<cv::Rect> a_rect, a_rectList2;
	std::vector< std::vector< cv::Point > > a_contours2;
	std::vector< std::vector< cv::Point > > a_contoursPoly2;


	// Connected Components Containers


	// Read from XML
	// CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE

public:
	std::vector<int> a_redThresh1 = {0, 100, 100, 10, 255, 255};
	std::vector<int> a_redThresh2 = {160, 100, 100, 180, 255, 255};
	std::vector<int> a_greenThresh = {0,0,0,0,0,0};
	std::vector<int> a_whiteThresh = {0,0,0,0,0,0};
	std::vector<int> a_blackThresh = {0,0,0,0,0,0};
	std::vector<cv::Mat> a_maskVector;

	std::vector< std::vector< int > > a_threshList = {a_redThresh1, a_redThresh2, a_greenThresh, a_whiteThresh, a_blackThresh};
	std::vector< std::vector< int > > a_redRobotThresh = {a_redThresh1, a_redThresh2, a_blackThresh, a_whiteThresh};

	cv::Mat* a_pHSVImg = new cv::Mat;
	cv::Mat* a_pMask = new cv::Mat;

	std::vector< std::vector<cv::Mat*> > a_filterImgList;

	std::vector<Robot*>* a_pRedRobotList;
	std::vector<Robot*>* a_pGreenRobotList;
	std::vector<Robot*>* a_pWhiteRobotList;
	int a_pixelThresh;

	Detection(int);
	// static std::vector<cv::Mat> findColors(std::vector<cv::Mat>, std::vector<int>, std::vector<cv::Mat>);
	// static std::vector<cv::Mat> findColors(std::vector<cv::Mat>, std::vector<int>, std::vector<int>, std::vector<cv::Mat>, std::vector< cv::Mat >);

	void getRedThreshParameters();
	void applyAllFilters(std::vector<cv::Mat*>, std::vector< std::vector<cv::Mat*> >, std::vector< std::vector<int> >);
	void applyFilter(cv::Mat, cv::Mat*, std::vector<int>);
	void applyRedFilter(cv::Mat, cv::Mat*, std::vector<int>, std::vector<int>);
	void redRobotSearch(cv::Mat*);
	void Search(boost::shared_ptr<std::vector<cv::Mat>>);
	void getContoursToBoxes(std::vector<cv::Rect>);
	void downSampleContours(std::vector<cv::Rect>);
	void addROIBuffer(cv::Rect);
	void populateRedRobots();
	void setRedRobots(std::vector<Robot*>*);
	void setGreenRobots(std::vector<Robot*>*);
	void setWhiteRobots(std::vector<Robot*>*);
	std::vector<cv::Mat> findRobots(std::vector<cv::Mat>, std::vector<cv::Mat>);
	static void drawRect(cv::Mat*, std::vector<cv::Rect>);
	cv::Mat showMask();
	//static std::vector<cv::Mat> search(std::vector<cv:, std::vector<cv::Rect>, std::vector<std::vector<cv::Point>>, std::vector<cv::Vec4i>, std::vector<std::vector<cv::Point>>, std::vector<cv::Mat>);

};

#endif
