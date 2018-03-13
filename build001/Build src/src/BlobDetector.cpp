
#include "Camera.h"
#include "BlobDetector.h"
using namespace cv;
using namespace std;
std::vector<cv::Mat> BlobDetector::findReds(std::vector< cv::Mat > frameList)
{
		if(!frameList[0].empty())
		{
			//Initializations
			std::vector<cv::Mat> hsvFrameList;
			std::vector<cv::Mat> lowerRedHueRange;
			std::vector<cv::Mat> upperRedHueRange;
			std::vector<cv::Mat> redHueImage;

			//Resize Frames
			hsvFrameList.resize(frameList.size());
			lowerRedHueRange.resize(frameList.size());
			upperRedHueRange.resize(frameList.size());
			redHueImage.resize(frameList.size());

			for(int i=0; i<frameList.size();i++)
			{
				// Convert to HSV
				cv::cvtColor(frameList[i], hsvFrameList[i], cv::COLOR_BGR2HSV);

				// Mask
				//Range so far H: 0-7 S: 100-255 V:100-255
				cv::inRange(hsvFrameList[i], cv::Scalar(0, 100, 100), cv::Scalar(7, 255, 255), redHueImage[i]);
				//cv::inRange(hsvFrameList[i], cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), upperRedHueRange[i]);

				// Combine the above two images
				//cv::addWeighted(lowerRedHueRange[i], 1.0, upperRedHueRange[i], 1.0, 0.0, redHueImage[i]);

				// Blur Image
				//cv::GaussianBlur(redHueImage[i], redHueImage[i], cv::Size(9, 9), 2, 2);
			}
		return redHueImage;
	}
	else{
		std::cout<<"Umm how should I put this? \n ... \n You fucked up. \n vector frameList is empty in the first position."<<std::endl;
	}
}

std::vector<cv::Mat> BlobDetector::findGreens(std::vector< cv::Mat > frameList){
		if(!frameList[0].empty()){
		std::vector<cv::Mat> hsvFrameList;
		hsvFrameList.resize(frameList.size());
		std::vector<cv::Mat> greenHueImage;
		greenHueImage.resize(frameList.size());
		for(int i=0; i<frameList.size();i++){
			cv::cvtColor(frameList[i], hsvFrameList[i], cv::COLOR_BGR2HSV);
			cv::inRange(hsvFrameList[i], cv::Scalar(40, 70, 50), cv::Scalar(80, 255, 255), greenHueImage[i]);

			cv::GaussianBlur(greenHueImage[i], greenHueImage[i], cv::Size(9, 9), 2, 2);

			// // Use the Hough transform to detect circles in the combined threshold image
			// std::vector<cv::Vec3f> circles;
			// cv::HoughCircles(redHueImage[i], circles, CV_HOUGH_GRADIENT, 1, redHueImage[i].rows/8, 100, 20, 0, 0);
      //
			// // Loop over all detected circles and outline them on the original image
			// if(circles.size() == 0) std::exit(-1);
			// for(size_t current_circle = 0; current_circle < circles.size(); ++current_circle) {
			// 	cv::Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
			// 	int radius = std::round(circles[current_circle][2]);
			// 	cv::circle(orig_image, center, radius, cv::Scalar(0, 255, 0), 5);
			}
		return greenHueImage;
	}
	else{
		std::cout<<"Umm how should I put this? \n ... \n You fucked up. \n vector frameList is empty in the first position. -findGreens function"<<std::endl;
	}
}
std::vector<cv::Mat> BlobDetector::findWhites(std::vector< cv::Mat > frameList){
		if(!frameList[0].empty()){
		std::vector<cv::Mat> hsvFrameList;
		hsvFrameList.resize(frameList.size());
		std::vector<cv::Mat> whiteHueImage;
		whiteHueImage.resize(frameList.size());
		for(int i=0; i<frameList.size();i++){
			cv::cvtColor(frameList[i], hsvFrameList[i], cv::COLOR_BGR2HSV);
			cv::inRange(hsvFrameList[i], cv::Scalar(0, 0, 215), cv::Scalar(255, 155, 255), whiteHueImage[i]);
			cv::GaussianBlur(whiteHueImage[i], whiteHueImage[i], cv::Size(9, 9), 2, 2);
		}
		return whiteHueImage;
	}
	else{
		std::cout<<"Umm how should I put this? \n ... \n You fucked up. \n vector frameList is empty in the first position. -findReds functions"<<std::endl;
	}
}
std::vector<cv::Mat> BlobDetector::findBlacks(std::vector< cv::Mat > frameList){
		if(!frameList[0].empty()){
		std::vector<cv::Mat> hsvFrameList;
		hsvFrameList.resize(frameList.size());
		std::vector<cv::Mat> blackHueImage;
		blackHueImage.resize(frameList.size());
		for(int i=0; i<frameList.size();i++){
			cv::cvtColor(frameList[i], hsvFrameList[i], cv::COLOR_BGR2HSV);
			cv::inRange(hsvFrameList[i], cv::Scalar(0, 0, 0), cv::Scalar(255, 155, 40), blackHueImage[i]);
			cv::GaussianBlur(blackHueImage[i], blackHueImage[i], cv::Size(9, 9), 2, 2);
		}
		return blackHueImage;
	}
	else{
		std::cout<<"Umm how should I put this? \n ... \n You fucked up. \n vector frameList is empty in the first position. -findReds functions"<<std::endl;
	}
}

std::vector<cv::Mat> BlobDetector::findRobots(std::vector<cv::Mat> frameList)
{
		if(!frameList[0].empty())
		{
			std::vector<std::vector<cv::Point>> contours;
			std::vector<cv::Vec4i> hierarchy;
			std::vector<cv::Mat> ROIs;
			std::vector<cv::Mat> redRectFrameList=frameList;
			std::vector<cv::Mat> blueRectFrameList;
			std::vector<cv::Mat> greenRectFrameList;
			std::vector<cv::Mat> redFrameList(frameList.size());
			std::vector<cv::Mat> blackFrameList(frameList.size());
			std::vector<cv::Mat> whiteFrameList(frameList.size());
			redFrameList=BlobDetector::findReds(frameList);
			whiteFrameList=BlobDetector::findWhites(frameList);
			for(int i=0; i<frameList.size(); i++)
			{
				cv::findContours(redFrameList[i], contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
			}
			std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
			std::vector<cv::Rect> boundRect(contours.size());
			for(size_t i = 0; i<contours.size(); i++)
			{
				cv::approxPolyDP(cv::Mat(contours[i]), contoursPoly[i], 3, true);
				boundRect[i]=cv::boundingRect(Mat(contoursPoly[i]));
			}
			for (size_t i = 0; i< contours.size(); i++)
			{
				for(int j =0; j<frameList.size(); j++)
				{
					if(cv::contourArea(contoursPoly[i])>1000){
						int x = boundRect[i].tl().x-50;
						int y = boundRect[i].tl().y-50;
						int width = boundRect[i].br().x-boundRect[i].tl().x+100;
						int height = boundRect[i].br().y-boundRect[i].tl().y+100;
						Rect tempRec = cv::Rect(x,y,width,height);
						cv::rectangle(redRectFrameList[j], tempRec, Scalar(0,0,255), 2, 8, 0);
						//ROIs.push_back(redRectFrameList[j](tempRec));
					}
				}
			}
			// cout<<"153"<<endl;
			// if(!ROIs[0].empty()){
			// 	blackFrameList=BlobDetector::findBlacks(ROIs);
			// 	for(int i=0; i<frameList.size(); i++)
			// 	{
			// 		cv::findContours(blackFrameList[i], contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
			// 	}
			// 	for(size_t i = 0; i<contours.size(); i++)
			// 	{
			// 			cv::approxPolyDP(cv::Mat(contours[i]), contoursPoly[i],3, true);
			// 			boundRect[i]=cv::boundingRect(Mat(contoursPoly[i]));
			// 	}
			// 	for (size_t i = 0; i< contours.size(); i++)
			// 	{
			// 		for(int j =0; j<frameList.size(); j++)
			// 		{
			// 			if(cv::contourArea(contoursPoly[i])>1000){
			// 				int x = boundRect[i].tl().x-50;
			// 				int y = boundRect[i].tl().y-50;
			// 				int width = boundRect[i].br().x-boundRect[i].tl().x+100;
			// 				int height = boundRect[i].br().y-boundRect[i].tl().y+100;
			// 				Rect tempRec = cv::Rect(x,y,width,height);
			// 				cv::rectangle(blueRectFrameList[j], tempRec, Scalar(255,0,0), 2, 8, 0);
			// 				//ROIs.push_back(blueRectFrameList[j](tempRec));
			// 			}
			// 		}
			// 	}
			// }

			return redRectFrameList;
		}
}
