#include "Robot.h"
#include <boost/thread/mutex.hpp>
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
	uint8_t _num_cams;

	cv::Mat _blur_img, _hsv_img;
	cv::Mat _red_mask;
	cv::Rect _black_roi, _white_roi;
	boost::shared_ptr< std::vector< cv::Rect > > _red_roi_vect_ptr = boost::make_shared< std::vector< cv::Rect > >();
	boost::shared_ptr< std::vector< cv::Rect > > _redrobot_roi_vect_ptr = boost::make_shared< std::vector< cv::Rect > >();

	// Find Contours Containers
	std::vector< cv::Vec4i > _hierarchy;
	std::vector< std::vector< cv::Point > > _red_contours;
	std::vector< std::vector< cv::Point > > _contours;
	std::vector< std::vector< cv::Point > > _red_contours_downsampled;

	std::vector<uint8_t> rtl={0, 100, 100, 10, 255, 255};
	std::vector<uint8_t> rtu={160, 100, 100, 180, 255, 255};
	std::vector<uint8_t> gt={0, 0, 0, 0, 0, 0};
	std::vector<uint8_t> wt={0, 0, 0, 0, 0, 0};
	std::vector<uint8_t> bt={0, 0, 0, 0, 0, 0};


public:
	boost::shared_ptr< std::vector< uint8_t > > _red_thresh_lower_ptr = boost::make_shared< std::vector< uint8_t > >(rtl);
	boost::shared_ptr< std::vector< uint8_t > > _red_thresh_upper_ptr = boost::make_shared< std::vector< uint8_t > >(rtu);
	boost::shared_ptr< std::vector< uint8_t > > _green_thresh_ptr = boost::make_shared< std::vector< uint8_t > >(gt);
	boost::shared_ptr< std::vector< uint8_t > > _white_thresh_ptr = boost::make_shared< std::vector< uint8_t > >(wt);
	boost::shared_ptr< std::vector< uint8_t > > _black_thresh_ptr = boost::make_shared< std::vector< uint8_t > >(bt);

	std::vector< std::vector<cv::Mat*> > a_filterImgList;

	int a_pixelThresh;

	Detection(uint8_t);

	void PrintRedThreshParameters();
	void PrintSearchResults();

	void ApplyFilter(cv::Mat*, cv::Mat*, boost::shared_ptr< std::vector<uint8_t> >);
	void ApplyFilter_Red(cv::Mat* inFrame, cv::Mat* outFrame);

	void GetROIs(cv::Mat*, boost::shared_ptr< std::vector< cv::Rect > >);
	void GetROI_Largest(cv::Mat* mask, cv::Rect* roi);

	void ExtendROI(cv::Rect*);

	void Search(boost::shared_ptr<std::vector<cv::Mat>>);
	void Search_RedRobots(cv::Mat*, boost::shared_ptr< std::vector< cv::Rect > >);

	void DownSampleContours(boost::shared_ptr< std::vector< cv::Rect > >);

	boost::shared_ptr< std::vector< cv::Rect > > GetRedRobotROIs();

	void ClearMembers();

	void DrawRects(boost::shared_ptr< std::vector< cv::Mat > >, boost::mutex&);
};

#endif
