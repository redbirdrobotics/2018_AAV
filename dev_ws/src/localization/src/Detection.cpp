#include "Detection.h"
#include "Utility.h"

Detection::Detection(uint8_t cam_num)
:_cam_num(cam_num)
{}

void Detection::drawRect(cv::Mat* img, std::vector<cv::Rect> rectList)
{
  for(int i=0; i<rectList.size(); i++)
  {
    cv::rectangle(*img, rectList[i], cv::Scalar(180,105,255));
  }
}

void Detection::PrintRedThreshParameters()
{
	for(uint8_t i=0; i< _redThresh1.size();i++)
	{
		std::cout<<i<<" "<<"red lower: "<<_redThresh1[i]<<"  red upper: "<<_redThresh2[i]<<std::endl;
	}
}

void Detection::ApplyFilter(cv::Mat& inFrame, cv::Mat& outFrame, boost::shared_ptr< std::vector<uint8_t> > threshold)
{
 	cv::inRange(inFrame, cv::Scalar((*threshold)[0], (*threshold)[1], (*threshold)[2]), cv::Scalar((*threshold)[3], (*threshold)[4], (*threshold)[5]), outFrame);
}


void Detection::ApplyFilter_Red(cv::Mat& inFrame, cv::Mat& outFrame)
{
	cv::Mat frame1, frame2;
	// Red1
	cv::inRange(inFrame, cv::Scalar(_red_lower[0], _red_lower[1], _red_lower[2]), cv::Scalar(_red_lower[3], _red_lower[4], _red_lower[5]), frame1);

	// Red2
	cv::inRange(inFrame, cv::Scalar(_red_upper[0], _red_upper[1], _red_upper[2]), cv::Scalar(_red_upper[3], _red_upper[4], _red_upper[5]), frame2);

	// Add Red1 and Red2 (upper and lower)
	cv::addWeighted(frame1, 1, frame2, 1, 0.0, outFrame);
}

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
	DownSampleContours(roi_vect);
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
void Detection::search_for_redrobots(boost::shared_ptr< std::vector< cv::Rect > > red_roi_vect)
{
	cv::Mat red_mask

	// Apply red mask
	ApplyFilter_Red(&_hsv_img, &red_mask);

	// Find contours of red shapes and place a bounding box around each
	GetROIs(&red_mask, red_roi_vect);

	// For each red bounding box
	for(uint8_t i=0; i<red_roi_vect->size(); i++)
	{
		cv::Mat black_mask, white_mask;
		cv::Mat red_roi = img((*red_roi_vect)[i]);

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

		_redrobot_roi_vect->push_back((*red_roi_vect)[i]);
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

