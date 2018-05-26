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
	std::vector< cv::Vec4i > _hierarchy;
	std::vector< std::vector< cv::Point > > _contours;
	std::vector< std::vector< cv::Point > > _contours_downsample;

	//Level 2 Search
	std::vector<cv::Rect> a_rect, a_rectList2;
	std::vector< std::vector< cv::Point > > a_contours2;
	std::vector< std::vector< cv::Point > > a_contoursPoly2;

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

	Detection(uint8_t);

	void PrintRedThreshParameters();
	void ApplyFilter(cv::Mat&, cv::Mat&, boost::shared_ptr< std::vector<uint8_t> >);
	void ApplyFilter_Red(cv::Mat& inFrame, cv::Mat& outFrame);

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

void Detection::DownSampleContours()
{	
	std::vector< std::vector< cv::Point > > contours_downsampled;
	contours_downsampled.resize(_contours.size());

	//a_rect.resize(a_contours1.size());

	for(uint8_t i=0; i<_contours.size(); i++)
	{
		cv::approxPolyDP((_contours[i]), contours_downsample[i], 3, true);

		if(cv::contourArea(contours_downsample[i]) > 500)
		{
			_roi_vect.push_back(cv::boundingRect(cv::Mat(contours_downsample[i])));
			//Detection::addROIBuffer(a_rect[i]);
		}
	}
}

void Detection::GetROIs(cv::Mat& mask, std::vector< cv::Rect > >& roi_vect)
{
	cv::findContours(mask, _contours, _hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
	if(_contours.empty()) {std::cout"No contours found"std::endl; return;}
	downSampleContours(roi_vect);
}

void Detection::GetROI_Largest(cv::Mat& mask, cv::Rect& roi)
{
	cv::findContours(mask, _contours, _hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

	if(_contours.empty()) {std::cout"No contours found"std::endl; return;}

	_largestcontour = _contours[0];
	for(uint8_t i=1; i<a_contours1.size(); i++)
	{
		_largestcontour = cv::contourArea(_largestcontour) > cv::contourArea(_contours[i]) ? _largestcontour : _contours[i];
	}
	roi = cv::boundingRect(cv::Mat(_largestcontour));	
}

void Detection::ClearMembers()
{
	_contours.clear();
	_hierarchy.clear();
	_largestcontour.clear();
}

// Search for red robots
void Detection::search_for_redrobots()
{
	cv::Mat red_mask
	std::vector<cv::Rect> red_roi_vect;

	// Apply red mask
	ApplyFilter_Red(&_hsv_img, &red_mask);

	// Find contours of red shapes and place a bounding box around each
	GetROIs(&red_mask, &red_roi_vect);

	// For each red bounding box
	for(uint8_t i=0; i<red_roi_vect.size(); i++)
	{
		cv::Mat black_mask, white_mask;
		cv::Mat red_roi = img(red_roi_vect[i]);

		// Look for a black section (shadow + sensor lens)
		ApplyFilter(red_roi, black_mask, _blackthresh);

		// Apply a box around largest black section
		GetROI_Largest(black_mask, _black_roi);

		// If no black region was found in any red ROIs, iterate to next red rect
		if(_black_roi.empty()) continue;

		// Apply white mask to Red ROI
		ApplyFilter(red_roi, white_mask, _whitethresh);

		// Apply a box around largest white region
		GetROI_Largest(white_mask, _white_roi);

		if(_white_roi.empty()) continue;

		_redrobot_roi_vect->push_back(red_roi_vect[i]);
	}
}

void Detection::Search(boost::shared_ptr< std::vector< cv::Mat> > imgvect_ptr)
{
	if(imgvect_ptr->empty()) return;

	for(int i=0; i<imgvect_ptr->size(); i++)
	{
		if((*imgvect_ptr)[i]->empty()) {std::cout<<"Empty Frame"<<std::endl; return;}

		cv::GaussianBlur((*imglist)[i], _blur_img, Size(5, 5), 0);
		cv::cvtColor(_blur_img, _hsv_img, CV_BGR2HSV);

		Search_RedRobots();
	}
}

// Need to add a_buffer, a_imgSz to header
// void Detection::addROIBuffer(cv::Rect rect) //explain
// {
// 	//IDEA: remove the 50s? I say we make it 10% of a_pixelThresh
// 	rect = cv::Rect(rect.tl().x-50, rect.tl().y-50, rect.br().x-rect.tl().x+100, rect.br().y-rect.tl().y+100);
//
// 	if(rect.tl.x < 0) rect.tl.x = 0;
// 	if(rect.tl.y < 0) rect.tl.y = 0;
// 	if(rect.br.x > imgSz.x) rect.br.x = imgSz.x;
// 	if(rect.br.y > imgSz.y) rect.br.y = imgSz.y;
// }

void Detection::populateRedRobots(){
	for(size_t i=0; i< a_whiteRectList.size(); i++){
		(*a_pRedRobotList)[i]->a_coordinates = a_whiteRectList[i].tl();
	}
}