#include "Detection.h"
#include "Utility.h"

Detection::Detection(uint8_t _num_cams)
:_num_cams(_num_cams)
{}

void Detection::ApplyFilter(cv::Mat* in_frame, cv::Mat* out_frame, boost::shared_ptr< std::vector<uint8_t> > threshold_ptr)
{
 	cv::inRange((*in_frame), cv::Scalar((*threshold_ptr)[0], (*threshold_ptr)[1], (*threshold_ptr)[2]), cv::Scalar((*threshold_ptr)[3], (*threshold_ptr)[4], (*threshold_ptr)[5]), (*out_frame));
}


void Detection::ApplyFilter_Red(cv::Mat* inFrame, cv::Mat* outFrame)
{
	cv::Mat frame1, frame2;
	// Red1
	cv::inRange((*inFrame), cv::Scalar((*_red_thresh_lower_ptr)[0], (*_red_thresh_lower_ptr)[1], (*_red_thresh_lower_ptr)[2]), cv::Scalar((*_red_thresh_lower_ptr)[3], (*_red_thresh_lower_ptr)[4], (*_red_thresh_lower_ptr)[5]), frame1);

	// Red2
	cv::inRange((*inFrame), cv::Scalar((*_red_thresh_upper_ptr)[0], (*_red_thresh_upper_ptr)[1], (*_red_thresh_upper_ptr)[2]), cv::Scalar((*_red_thresh_upper_ptr)[3], (*_red_thresh_upper_ptr)[4], (*_red_thresh_upper_ptr)[5]), frame2);

	// Add Red1 and Red2 (upper and lower)
	cv::addWeighted(frame1, 1, frame2, 1, 0.0, (*outFrame));
}

void Detection::ExtendROI(cv::Rect* roi)
{
	(*roi).height += 100;
}

void Detection::DownSampleContours(boost::shared_ptr< std::vector< cv::Rect > > roi_vect_ptr)
{	
	std::vector< std::vector< cv::Point > > contours_downsampled;
	contours_downsampled.resize(_red_contours.size());

	for(uint8_t i=0; i<_red_contours.size(); i++)
	{
		cv::approxPolyDP(_red_contours[i], contours_downsampled[i], 3, true);

		if(cv::contourArea(contours_downsampled[i]) > 10)
		{
			cv::Rect roi = cv::boundingRect(contours_downsampled[i]);
			ExtendROI(&roi);
			roi_vect_ptr->push_back(roi);
		}
	}
}

void Detection::GetROIs(cv::Mat* mask, boost::shared_ptr< std::vector< cv::Rect > > roi_vect)
{
	cv::findContours((*mask), _red_contours, _hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
	if(_red_contours.empty()) {std::cout<<"No red contours found"<<std::endl; return;}
	DownSampleContours(roi_vect);
}

void Detection::GetROI_Largest(cv::Mat* mask, cv::Rect* roi)
{
	std::vector< cv::Point > largest_contour;

	cv::findContours((*mask), _contours, _hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

	if(_contours.empty()) {std::cout<<"No contours found"<<std::endl; return;}

	largest_contour = _contours[0];
	for(uint8_t i=1; i<_contours.size(); i++)
	{
		largest_contour = cv::contourArea(largest_contour) > cv::contourArea(_contours[i]) ? largest_contour : _contours[i];
	}
	(*roi) = cv::boundingRect(cv::Mat(largest_contour));	
}

// Search for red robots
void Detection::Search_RedRobots(cv::Mat* hsv_img, boost::shared_ptr< std::vector< cv::Rect > > redrobot_roi_vect_ptr)
{
	// Apply red mask
	ApplyFilter_Red(hsv_img, &_red_mask);

	// Find contours of red shapes and place a bounding box around each
	GetROIs(&_red_mask, _red_roi_vect_ptr);

	if(_red_roi_vect_ptr->empty()) return;

	// For each red bounding box
	for(uint8_t i=0; i<_red_roi_vect_ptr->size(); i++)
	{
		cv::Mat black_mask, white_mask;
		cv::Rect black_roi, white_roi;
		cv::Mat red_roi = (*hsv_img)((*_red_roi_vect_ptr)[i]);

		// Look for a black section (shadow + sensor lens)
		ApplyFilter(&red_roi, &black_mask, _black_thresh_ptr);

		// Apply a box around largest black section
		GetROI_Largest(&black_mask, &black_roi);

		// If no black region was found in any red ROIs, iterate to next red rect
		if(black_roi.empty()) continue;
		std::cout<<"found black region\n";
		// Apply white mask to Red ROI
		ApplyFilter(&red_roi, &white_mask, _white_thresh_ptr);

		// Apply a box around largest white region
		GetROI_Largest(&white_mask, &white_roi);

		if(white_roi.empty()) continue;
		std::cout<<"found white region\n";

		redrobot_roi_vect_ptr->push_back((*_red_roi_vect_ptr)[i]);
	}
}

void Detection::Search(boost::shared_ptr< std::vector< cv::Mat> > imgvect_ptr)
{
	if(imgvect_ptr->empty()) return;

	for(int i=0; i<_num_cams; i++)
	{
		if((*imgvect_ptr)[i].empty()) {std::cout<<"Empty Frame"<<std::endl; return;}

		cv::GaussianBlur((*imgvect_ptr)[i], _blur_img, cv::Size(5, 5), 0);
		cv::cvtColor(_blur_img, _hsv_img, CV_BGR2HSV);

		Search_RedRobots(&_hsv_img, _redrobot_roi_vect_ptr);
	}
}

boost::shared_ptr< std::vector< cv::Rect > > Detection::GetRedRobotROIs() {return (_redrobot_roi_vect_ptr);}

void Detection::ClearMembers()
{
	_blur_img.release(); 
	_hsv_img.release();
	_red_mask.release();
	_red_contours.clear();
	_contours.clear();
	_hierarchy.clear();
	_red_roi_vect_ptr->clear();
	_redrobot_roi_vect_ptr->clear();
}

void Detection::DrawRects(boost::shared_ptr< std::vector< cv::Mat > > imgvect_ptr, boost::mutex& MUTEX)
{
	boost::lock_guard<boost::mutex> guard(MUTEX);
	(*imgvect_ptr)[0].copyTo((*imgvect_ptr)[1]);
	for(int i=0; i<_redrobot_roi_vect_ptr->size(); i++)
	{
		std::cout<<(*_redrobot_roi_vect_ptr)[i].width<<" "<<(*_redrobot_roi_vect_ptr)[i].height<<"\n";
		cv::rectangle((*imgvect_ptr)[1], (*_redrobot_roi_vect_ptr)[i], cv::Scalar(0,0,255));
	}
}

void Detection::PrintRedThreshParameters()
{
	std::cout<<"\n###########################\nRed Threshold Parameters\n###########################\n";
	std::cout<<"red lower: "<<(int)(*_red_thresh_lower_ptr)[0]<<", "<<(int)(*_red_thresh_lower_ptr)[1]<<", "<<(int)(*_red_thresh_lower_ptr)[2]<<", "<<(int)(*_red_thresh_lower_ptr)[3]<<", "<<(int)(*_red_thresh_lower_ptr)[4]<<", "<<(int)(*_red_thresh_lower_ptr)[5]<<std::endl;
	std::cout<<"red upper: "<<(int)(*_red_thresh_upper_ptr)[0]<<", "<<(int)(*_red_thresh_upper_ptr)[1]<<", "<<(int)(*_red_thresh_upper_ptr)[2]<<", "<<(int)(*_red_thresh_upper_ptr)[3]<<", "<<(int)(*_red_thresh_upper_ptr)[4]<<", "<<(int)(*_red_thresh_upper_ptr)[5]<<std::endl;
	std::cout<<"\n";
}

void Detection::PrintSearchResults()
{
	std::cout<<"\n###########################\nRed Search Results\n###########################\n";
	std::cout<<"Number of found red contours: "<<_red_contours.size()<<"\n";
	std::cout<<"Number of viable red contours: "<<_red_roi_vect_ptr->size()<<"\n";
	std::cout<<"Number of confirmed redrobots: "<<_redrobot_roi_vect_ptr->size()<<"\n";
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

// void Detection::populateRedRobots(){
// 	for(size_t i=0; i< a_whiteRectList.size(); i++){
// 		(*a_pRedRobotList)[i]->a_coordinates = a_whiteRectList[i].tl();
// 	}
// }

