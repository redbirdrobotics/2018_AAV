#include "Detection.h"
#include "Utility.h"
using namespace std;

class 

class ros_adapter {
 public:
  send_robots(const robots& r) {

  }
};

Detection::Detection(int camNum)
{
	a_filterImgList.resize(camNum);
	a_pixelThresh = 500;
}

void Detection::setRedRobots(std::vector<Robot*>* redBots){
	a_pRedRobotList = redBots;
	std::array<T, 4>
}
void Detection::setGreenRobots(std::vector<Robot*>* greenBots){
	a_pGreenRobotList = greenBots;
}
void Detection::setWhiteRobots(std::vector<Robot*>* whiteBots){
	a_pWhiteRobotList = whiteBots;
}
void Detection::drawRect(cv::Mat* img, std::vector<cv::Rect> rectList)
{
  for(int i=0; i<rectList.size(); i++)
  {
  	//make constant _RECTANGLE_COLOR
    cv::rectangle(*img, rectList[i], cv::Scalar(180,105,255));
	cout<<"Rectangle: "<<i<<endl;
  }
}

// void Detection::applyRedFilter(cv::Mat inFrame, cv::Mat* outFrame, std::vector<int> lower, std::vector<int> upper)
// {
// 	cv::Mat frame1, frame2;
// 	// Red1
// 	applyFilter(inFrame, &frame1, lower);
// 	// Red2
// 	applyFilter(inFrame, &frame2, upper);
// 	// Add Red1 and Red2 (upper and lower)
// 	cv::addWeighted(frame1, 1, frame2, 1, 0.0, *outFrame);
// }

void Detection::getRedThreshParameters()
{
	for(int i=0; i< a_redThresh1.size();i++)
	{
		cout<<i<<": "<<a_redThresh1[i];
	}
	cout<<endl;
	for(int i=0; i< a_redThresh2.size();i++)
	{
		cout<<i<<": "<<a_redThresh2[i];
	}
	cout<<endl;
}

cv::Mat Detection::showMask()
{
	return *a_pMask;
}

// Get imglist

// Get Img
// Apply filter
// Get contours
// Get Bounding Box
// Apply filter to new boxed image
// Get contours
// Get Bounding Box
// ...
// Cameras

// void Detection::Search(boost::shared_ptr< std::vector< cv::Mat> > pImgList)
// {
// 	if(!pImgList->empty()){
// 		// Cameras
// 		for(int i=0; i<pImgList->size(); i++)
// 		{
// 			if((*pImgList)[i].rows>0 && (*pImgList)[i].cols>0){

// 				// Convert to HSV
// 				cv::cvtColor((*pImgList)[i], (*a_pHSVImg), CV_BGR2HSV);


// 				// For Red / Green / White Robots
// 		    std::cout<<" Line: " << __LINE__ <<std::endl;

// 				// Troubleshooting
// 				cv::Mat temp;
// 				applyRedFilter(*a_pHSVImg, &temp, a_redRobotThresh[0], a_redRobotThresh[1]);
// 				(*pImgList)[0]=temp;
// 				// if(pImgList->size() == 1)
// 				// {
// 				//  	pImgList->push_back(temp);
// 				// }
// 				// else {(*pImgList)[1]=temp;}


// 				// RedSearch()
// 				// redRobotSearch(a_pHSVImg);

// 		    std::cout<<" Line: " << __LINE__ <<std::endl;
// 				//Detection::drawRect(&((*pImgList)[i]),a_redRectList);
// 				// green search
// 				// white search
// 				}
// 		}
// 	}
// }

void Detection::search_imgs(boost::shared_ptr< std::vector< cv::Mat> > imglist)
{
	if(imglist->empty()) return;

	for(int i=0; i<imglist->size(); i++)
	{
		if((*imglist)[i]->empty()) {std::cout<<"Empty Frame"<<std::endl; return;}

		cv::GaussianBlur((*imglist)[i], _blur_img, Size(5, 5), 0);
		cv::cvtColor(_blur_img, _hsv_img, CV_BGR2HSV);

		
	}
}

// Search for red robots
void Detection::search_for_redrobots(cv::Mat img)
{
	cv::Mat mask;

	// Apply red mask
	apply_redfilter(img, mask, _redrobot_thresh[0], a_redrobot_thresh[1]);

	// Find contours of red shapes and place a bounding box around each
	get_boxes_from_mask(mask, _redrect_list);

	// For each red bounding box
	for(int i=0; i<_redrect_list.size(); i++)
	{
		// Look for a black section (shadow + sensor lens)
		apply_filter(img(_redrect_list[i]), _mask, _blackthresh);

		// Apply a box around black section, if found
		getContoursToBoxes(a_blackRectList);

		// If no black region was found in any red ROIs, iterate to next red rect
		if(!a_blackRectList.empty()) continue;

		// Apply white mask to Red ROI
		applyFilter((img)(_redrect_list[i]), _mask, _whitethresh);

		get_largest_contourbox(_);

			// Apply box around white section, if found
			getContoursToBoxes(a_whiteRectList);
		}

	}

	if(!a_whiteRectList.empty() && a_whiteRectList.size()<6)
	{

		populateRedRobots();
	}
}

void Detection::applyRedFilter(cv::Mat inFrame, cv::Mat outFrame)
{
	cv::Mat frame1, frame2;
	// Red1
	cv::inRange(inFrame, cv::Scalar(_red_lower[0], _red_lower[1], _red_lower[2]), cv::Scalar(_red_lower[3], _red_lower[4], _red_lower[5]), frame1);

	// Red2
	cv::inRange(inFrame, cv::Scalar(_red_upper[0], _red_upper[1], _red_upper[2]), cv::Scalar(_red_upper[3], _red_upper[4], _red_upper[5]), frame2);

	// Add Red1 and Red2 (upper and lower)
	cv::addWeighted(frame1, 1, frame2, 1, 0.0, outFrame);
}

describe_masked_regions(cv::Mat* img) {
	std::vector<rectangle> r{};
	for (all the regions)
		r.add(the rectangle)

	return r;
}

// Takes Mask stored in a_pMask
// Finds contours associated with mask
// Down-samples and populates a_rectList with bounding rectangles
void Detection::get_boxes_from_mask(std::vector<cv::Rect> type)
{
	//TODO: add clearing function for counterlists and hierarchy
	cv::findContours(*a_pMask, a_contours1, a_hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
	//a_imgSz,
	cout<<"contour size: " << a_contours1.size()<<endl;
	downSampleContours(type);
}

void Detection::get_largest_box_from_mask(std::vector<cv::Rect> contours)
{
	cv::findContours(*a_pMask, a_contours1, a_hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
	_largestcontour = _contours[0];
	for(uint8_t i=1; i<a_contours1.size(); i++)
	{
		_largestcontour = _largestcontour > _contours[i] ? _largestcontour : _contours[i];
	}
	cv::boundingRect(cv::Mat(_largestcontour));
}

void Detection::applyFilter(cv::Mat inFrame, cv::Mat* outFrame, std::vector<int> threshold)
{
  cv::inRange(inFrame, cv::Scalar(threshold[0], threshold[1], threshold[2]), cv::Scalar(threshold[3], threshold[4], threshold[5]), *outFrame);
}

// pixThresh should be different for each threshold, ie less green than white, more white than black, less black than green
// could be accomplished with a thresh struct

void Detection::downSampleContours(std::vector<cv::Rect> type)
{
	a_contoursPoly.resize(a_contours1.size());
	a_rect.resize(a_contours1.size());

	for(uint8_t i=0; i<a_contours1.size(); i++)
	{
		cv::approxPolyDP(cv::Mat(a_contours1[i]), a_contoursPoly[i], 3, true);

		if(cv::contourArea(a_contoursPoly[i]) > 500)
		{
			type.push_back(cv::boundingRect(cv::Mat(a_contoursPoly[i])));
			//TODO:change to pass in associated rectlist in each if
			//Detection::addROIBuffer(a_rect[i]);
		}
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

