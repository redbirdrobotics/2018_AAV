#include "Detection.h"
#include "Utility.h"
using namespace std;

Detection::Detection(int camNum)
{
	a_filterImgList.resize(camNum);
	a_pixelThresh = 500;
}

void Detection::setRedRobots(std::vector<Robot*>* redBots){
	a_pRedRobotList = redBots;
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
    cv::rectangle(*img, rectList[i], cv::Scalar(180,105,255));
		cout<<"Rectangle: "<<i<<endl;
  }
}
// std::vector<cv::Mat> Detection::findColors(std::vector< cv::Mat > inputFrameList, std::vector<int> range ,std::vector<cv::Mat> outputFrameList){
// 	if(!inputFrameList[0].empty()){
// 		//Resize Vectors
// 		outputFrameList.resize(inputFrameList.size());
// 		//cycles through frameList for color detection
// 		for(int i=0; i<inputFrameList.size();i++){
// 			//Find colors in green range
// 			cv::inRange(inputFrameList[i], cv::Scalar(range[0], range[1], range[2]), cv::Scalar(range[3], range[4], range[5]), outputFrameList[i]);
// 			// Blur Image
// 			cv::GaussianBlur(outputFrameList[i], outputFrameList[i], cv::Size(9, 9), 2, 2);
// 		}
// 		// return a filtered frameList for green things.
// 		//	anything thing that is green things will be returned as white pixels and non green things will be returned with pixels
// 		return outputFrameList;
// 	}
// 	else{
// 	    cout<<"Fuck up in " __FILE__ << " Line: " << __LINE__ << " function: " << __FUNCTION__ <<endl;
// 	}
// }
// std::vector<cv::Mat> Detection::findColors(std::vector< cv::Mat > inputFrameList, std::vector<int> range1, std::vector<int> range2, std::vector<cv::Mat> v,std::vector< cv::Mat > outputFrameList){
// 		if(!inputFrameList[0].empty()){
// 			outputFrameList.resize(inputFrameList.size());
// 			v.resize(inputFrameList.size());
// 			//cycles through frameList for color detection
// 			for(int i=0; i<inputFrameList.size();i++){
// 				// Mask
// 				cv::inRange(inputFrameList[i], cv::Scalar(range1[0], range1[1], range1[2]), cv::Scalar(range1[3], range1[4], range1[5]), outputFrameList[i]);
// 				cv::inRange(inputFrameList[i], cv::Scalar(range2[0], range2[1], range2[2]), cv::Scalar(range2[3], range2[4], range2[5]), v[i]);
//
// 				// Combine the above two images
// 				cv::addWeighted(outputFrameList[i], 1.0, v[i], 1.0, 0.0, outputFrameList[i]);
//
// 				// Blur Image
// 				cv::GaussianBlur(outputFrameList[i], outputFrameList[i], cv::Size(9, 9), 2, 2);
// 			}
// 		// return a filtered frameList for red things.
// 		//	anything thing that is red things will be returned as white pixels and non red things will be returned with pixels
// 		return outputFrameList;
// 	}
// 	else{
// 		cout<<"Fuck up in " __FILE__ << " Line: " << __LINE__ << " function: " << __FUNCTION__ <<endl;
// 	}
// }

// void Detection::findContours()
// {
// 	// Cameras
// 	for(int i=0; i<a_filterImgList.size(); i++)
// 	{
// 		// Frames
// 		for(int j=0; j<a_threshList.size(); j++)
// 		{
// 			cv::findContours(a_filterImgList[i][j], a_contours, a_hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
// 		}

// 		a_contoursPoly.resize(a_contours.size());
// 		a_rects.resize(contours.size());

// 		for(uint8_t i = 0; i<contours.size(); i++)
// 		{
// 			// ARGS should be set from XML
// 			// epsilon [dbl] closed [bool]
// 			cv::approxPolyDP(cv::Mat(contours[i]), contoursPoly[i], 3, true);

// 			rects[i]=cv::boundingRect(cv::Mat(contoursPoly[i]));

// 			// Should Be its own function
// 			for(int k=0; k<a_filterImgList.size(); k++)
// 			{
// 				if(cv::contourArea(contoursPoly[i])>1000)
// 				{
// 					rects[i] = cv::Rect(rects[i].tl().x-50, rects[i].tl().y-50, rects[i].br().x-rects[i].tl().x+100, rects[i].br().y-rects[i].tl().y+100);
// 					if(rects[i].x >= 0 && rects[i].y >= 0 && rects[i].width + rects[i].x < frameList[j].cols && rects[i].height + rects[i].y < frameList[j].rows)
// 					{
// 						cv::Mat filteredROI = cv::Mat(filteredFrameList[j])(rects[i]);
// 					}
// 				}
// 			}
// 		}
// 	}
// }

//LUKAS HOLD OFF ON EDITING, MY CODE IS UNINTELLIGABLE ATM BUT WILL BE FIXED SOON

// void Detection::applyAllFilters(std::vector<cv::Mat*> inFrameList, std::vector< std::vector<cv::Mat*> > outFrameList, std::vector< std::vector<int> > threshList)
// {
//   for(int i=0; i<threshList.size(); i++)
//   {
//     for(int j=0; j<outFrameList.size(); j++)
//     {
//       cv::Mat* frame;
//       outFrameList[j].push_back(frame);
//       applyFilter(inFrameList[j], outFrameList[j][i], threshList[i]);
//     }
//   }
// }

void Detection::applyRedFilter(cv::Mat inFrame, cv::Mat* outFrame, std::vector<int> lower, std::vector<int> upper)
{
	cv::Mat frame1, frame2;
	// Red1
	applyFilter(inFrame, &frame1, lower);
	// Red2
	applyFilter(inFrame, &frame2, upper);
	// Add Red1 and Red2 (upper and lower)
	cv::addWeighted(frame1, 1, frame2, 1, 0.0, *outFrame);
}

void Detection::getRedThreshParameters(){
	for(int i=0; i< a_redThresh1.size();i++){
		cout<<i<<": "<<a_redThresh1[i];
	}
	cout<<endl;
	for(int i=0; i< a_redThresh2.size();i++){
		cout<<i<<": "<<a_redThresh2[i];
	}
	cout<<endl;
}
cv::Mat Detection::showMask(){
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

void Detection::Search(boost::shared_ptr< std::vector< cv::Mat> > pImgList)
{
	if(!pImgList->empty()){
		// Cameras
		for(int i=0; i<pImgList->size(); i++)
		{
			if((*pImgList)[i].rows>0 && (*pImgList)[i].cols>0){

				// Convert to HSV
				cv::cvtColor((*pImgList)[i], (*a_pHSVImg), CV_BGR2HSV);

				// For Red / Green / White Robots
		    std::cout<<" Line: " << __LINE__ <<std::endl;

				// Troubleshooting
				cv::Mat temp;
				applyRedFilter(*a_pHSVImg, &temp, a_redRobotThresh[0], a_redRobotThresh[1]);
				(*pImgList)[0]=temp;
				// if(pImgList->size() == 1)
				// {
				//  	pImgList->push_back(temp);
				// }
				// else {(*pImgList)[1]=temp;}


				// RedSearch()
				// redRobotSearch(a_pHSVImg);

		    std::cout<<" Line: " << __LINE__ <<std::endl;
				//Detection::drawRect(&((*pImgList)[i]),a_redRectList);
				// green search
				// white search
				}
		}
	}
}

void Detection::redRobotSearch(cv::Mat* img)
{
	applyRedFilter(*img, a_pMask, a_redRobotThresh[0], a_redRobotThresh[1]);
	getContoursToBoxes(a_redRectList);
	cout<< "a_redRectList size: "<<a_redRectList.size()<<endl;
	for(int i=0; i<a_redRectList.size(); i++)
	{
		applyFilter((*img)(a_redRectList[i]), a_pMask, a_blackThresh);
		getContoursToBoxes(a_blackRectList);
	}
	if(!a_blackRectList.empty()){

		for(int i=0; i<a_blackRectList.size(); i++){
		applyFilter((*img)(a_redRectList[i]), a_pMask, a_whiteThresh);
		getContoursToBoxes(a_whiteRectList);
		}
	}
	if(!a_whiteRectList.empty() && a_whiteRectList.size()<6){

		populateRedRobots();
	}
}


// Takes Mask stored in a_pMask
// Finds contours associated with mask
// Down-samples and populates a_rectList with bounding rectangles
void Detection::getContoursToBoxes(std::vector<cv::Rect> type){
	//TODO: add clearing function for counterlists and hierarchy
	cv::findContours(*a_pMask, a_contours1, a_hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
	//a_imgSz,
	cout<<"a_contours1 size: " << a_contours1.size()<<endl;
	downSampleContours(type);
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
			cout<<"push_back successful"<<endl;
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


// void Detection::findContours()
// {
// 	// Cameras
// 	for(int i=0; i<a_filterImgList.size(); i++)
// 	{
// 		// Frames
// 		for(int j=0; j<a_threshList.size(); j++)
// 		{
// 			cv::connectedComponentsWithStats(a_filterImgList[i][j], )
// 		}
// }




// std::vector<cv::Mat> Detection::findRobots(std::vector<cv::Mat> inputFrameList, std::vector<cv::Mat> outputFrameList){
// 		if(!frameList[0].empty()){
// 			std::vector<cv::Mat> redRectFrameList=frameList;
// 			std::vector<cv::Mat> blueRectFrameList;
// 			std::vector<cv::Mat> greenRectFrameList;
// 			std::vector<cv::Mat> redFrameList(frameList.size());
// 			std::vector<cv::Mat> blackROIs;
// 			int x {0}, y{0}, width{0}, height{0}, inputWidth{0}, inputHeight{0};
// 			redFrameList=BlobDetector::findReds(frameList);
// 			cout<<__LINE__<<endl;
// 			for(int i=0; i<frameList.size(); i++)
// 			{
// 				cv::findContours(redFrameList[i], contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
// 			}
// 			std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
// 			std::vector<cv::Rect> boundRect(contours.size());
// 			std::vector<cv::Mat> ROIs;
// 			cout<<__LINE__<<endl;
// 			for(size_t i = 0; i<contours.size(); i++)
// 			{
// 				cv::approxPolyDP(cv::Mat(contours[i]), contoursPoly[i], 3, true);
// 				boundRect[i]=cv::boundingRect(Mat(contoursPoly[i]));
// 			}
// 			cout<<__LINE__<<endl;
// 			for (size_t i = 0; i< contours.size(); i++)
// 			{
// 				cout<<__LINE__<<endl;
// 				for(int j =0; j<frameList.size(); j++)
// 				{
// 					cout<<__LINE__<<endl;
// 					if(cv::contourArea(contoursPoly[i])>1000){
// 						x = boundRect[i].tl().x-50;
// 						y = boundRect[i].tl().y-50;
// 						width = boundRect[i].br().x-boundRect[i].tl().x+100;
// 						height = boundRect[i].br().y-boundRect[i].tl().y+100;
// 						Rect roiRec = cv::Rect(x,y,width,height);
// 						cv::rectangle(redRectFrameList[j], roiRec, Scalar(0,0,255), 2, 8, 0);
// 						cout<<__LINE__<<endl;
// 						inputWidth = frameList[j].cols;
// 						inputHeight = frameList[j].rows;
// 						if(roiRec.x >= 0 && roiRec.y >= 0 && roiRec.width + roiRec.x < inputWidth && roiRec.height + roiRec.y < inputHeight){
// 							cv::Mat tempImage = cv::Mat(frameList[j])(roiRec);
// 							namedWindow("red - ROIs", WINDOW_AUTOSIZE);
// 							imshow("red - ROIs",tempImage);
// 							ROIs.push_back(tempImage);
// 							cout<<__LINE__<<endl;
// 						}
// 					}
// 				}
// 			}
// 			cout<<__LINE__<<endl;
// 			if(!ROIs.empty())
// 			{
// 				cout<<__LINE__<<endl;
// 				greenRectFrameList=redRectFrameList;
// 				blackROIs=BlobDetector::findBlacks(ROIs);
// 				std::vector<int> countWhite(frameList.size(),0);
// 				cout<<__LINE__<<endl;
// 				for(int i=0; i<blackROIs.size(); i++)
// 				{
// 					for(int y =0; y< blackROIs[i].rows; y++)
// 					{
// 						for(int x=0; x< blackROIs[i].cols; x++)
// 						{
// 							if(cv::Mat(blackROIs[i]).at<cv::Vec3b>(y,x) == cv::Vec3b(255, 255, 255))
// 							{
// 								countWhite[i]+=1;
// 							}
// 						}
// 					}
// 				}
// 				cout<<__LINE__<<endl;
// 				for(int i=0; i< countWhite.size(); i++)
// 				{
// 					cout<<__LINE__<<endl;
// 					if(countWhite[i]>1000)
// 					{
// 						cout<<__LINE__<<endl;
// 						std::vector<cv::Mat> whiteROIs;
// 						whiteROIs = BlobDetector::findWhites(ROIs);
// 						contours.clear();
// 						boundRect.clear();
// 						hierarchy.clear();
// 						cout<<__LINE__<<endl;
// 						for(size_t i=0; i<contoursPoly.size(); i++)
// 						{
// 								contoursPoly[i].clear();
// 						}
// 						cout<<__LINE__<<endl;
// 						for(int i=0; i<frameList.size(); i++)
// 						{
// 							cv::findContours(whiteROIs[i], contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
// 						}
// 						std::vector<std::vector<cv::Point>> whiteContoursPoly(contours.size());
// 						boundRect.resize(contours.size());
// 						cout<<__LINE__<<endl;
// 						for(size_t i = 0; i<contours.size(); i++)
// 						{
// 								cv::approxPolyDP(cv::Mat(contours[i]), whiteContoursPoly[i],3, true);
// 								boundRect[i]=cv::boundingRect(Mat(whiteContoursPoly[i]));
// 						}
// 						cout<<__LINE__<<endl;
// 						for (size_t i = 0; i< contours.size(); i++)
// 						{
// 							cout<<__LINE__<<endl;
// 							for(int j =0; j<frameList.size(); j++)
// 							{
// 								cout<<__LINE__<<endl;
// 								if(cv::contourArea(whiteContoursPoly[i])>500)
// 								{
// 									cout<<__LINE__<<endl;
// 									x += boundRect[i].tl().x;
// 									cout<<__LINE__<<endl;
// 									y += boundRect[i].tl().y;
// 									width  = boundRect[i].br().x-boundRect[i].tl().x;
// 									height = boundRect[i].br().y-boundRect[i].tl().y;
// 									Rect roiRec = cv::Rect(x,y,width,height);
// 									cv::rectangle(greenRectFrameList[j], roiRec, Scalar(0,0,255), 2, 8, 0);
// 									if(roiRec.x >= 0 && roiRec.y >= 0 && roiRec.width + roiRec.x < inputWidth && roiRec.height + roiRec.y < inputHeight)
// 									{
// 										cv::Mat tempImage = cv::Mat(frameList[j])(roiRec);
// 										namedWindow("greenHueImage - ROIs", WINDOW_AUTOSIZE);
// 										imshow("green - ROIs",tempImage);
// 										//ROIs.push_back(tempImage);
// 										//coordinates[i].push_back(j);
// 										cout<<__LINE__<<endl;
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 				return greenRectFrameList;
// 			}
// 			else{
// 				return redRectFrameList;
// 			}
// 		}
// }
