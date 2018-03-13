
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
			cout<<__LINE__<<endl;
			std::vector<std::vector<cv::Point>> contours;
			std::vector<cv::Vec4i> hierarchy;
			std::vector<cv::Mat> redRectFrameList=frameList;
			std::vector<cv::Mat> blueRectFrameList;
			std::vector<cv::Mat> greenRectFrameList;
			std::vector<cv::Mat> redFrameList(frameList.size());
			std::vector<cv::Mat> blackROIs;
			int x = 0;
			int y = 0;
			int width = 0;
			int height = 0;
			int inputWidth =0;
			int inputHeight =0;
			redFrameList=BlobDetector::findReds(frameList);
			cout<<__LINE__<<endl;
			for(int i=0; i<frameList.size(); i++)
			{
				cv::findContours(redFrameList[i], contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
			}
			std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
			std::vector<cv::Rect> boundRect(contours.size());
			std::vector<cv::Mat> ROIs;
			cout<<__LINE__<<endl;
			for(size_t i = 0; i<contours.size(); i++)
			{
				cv::approxPolyDP(cv::Mat(contours[i]), contoursPoly[i], 3, true);
				boundRect[i]=cv::boundingRect(Mat(contoursPoly[i]));
			}
			cout<<__LINE__<<endl;
			for (size_t i = 0; i< contours.size(); i++)
			{
				cout<<__LINE__<<endl;
				for(int j =0; j<frameList.size(); j++)
				{
					cout<<__LINE__<<endl;
					if(cv::contourArea(contoursPoly[i])>1000){
						x = boundRect[i].tl().x-50;
						y = boundRect[i].tl().y-50;
						width = boundRect[i].br().x-boundRect[i].tl().x+100;
						height = boundRect[i].br().y-boundRect[i].tl().y+100;
						Rect roiRec = cv::Rect(x,y,width,height);
						cv::rectangle(redRectFrameList[j], roiRec, Scalar(0,0,255), 2, 8, 0);
						cout<<__LINE__<<endl;
						inputWidth = frameList[j].cols;
						inputHeight = frameList[j].rows;
						if(roiRec.x >= 0 && roiRec.y >= 0 && roiRec.width + roiRec.x < inputWidth && roiRec.height + roiRec.y < inputHeight){
							cv::Mat tempImage = cv::Mat(frameList[j])(roiRec);
							namedWindow("red - ROIs", WINDOW_AUTOSIZE);
							imshow("red - ROIs",tempImage);
							ROIs.push_back(tempImage);
							cout<<__LINE__<<endl;
						}
					}
				}
			}
			cout<<__LINE__<<endl;
			if(!ROIs.empty())
			{
				cout<<__LINE__<<endl;
				greenRectFrameList=redRectFrameList;
				blackROIs=BlobDetector::findBlacks(ROIs);
				std::vector<int> countWhite(frameList.size(),0);
				cout<<__LINE__<<endl;
				for(int i=0; i<blackROIs.size(); i++)
				{
					for(int y =0; y< blackROIs[i].rows; y++)
					{
						for(int x=0; x< blackROIs[i].cols; x++)
						{
							if(cv::Mat(blackROIs[i]).at<cv::Vec3b>(y,x) == cv::Vec3b(255, 255, 255))
							{
								countWhite[i]+=1;
							}
						}
					}
				}
				cout<<__LINE__<<endl;
				for(int i=0; i< countWhite.size(); i++)
				{
					cout<<__LINE__<<endl;
					if(countWhite[i]>1000)
					{
						cout<<__LINE__<<endl;
						std::vector<cv::Mat> whiteROIs;
						whiteROIs = BlobDetector::findWhites(ROIs);
						contours.clear();
						boundRect.clear();
						hierarchy.clear();
						cout<<__LINE__<<endl;
						for(size_t i=0; i<contoursPoly.size(); i++)
						{
								contoursPoly[i].clear();
						}
						cout<<__LINE__<<endl;
						for(int i=0; i<frameList.size(); i++)
						{
							cv::findContours(whiteROIs[i], contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
						}
						std::vector<std::vector<cv::Point>> whiteContoursPoly(contours.size());
						boundRect.resize(contours.size());
						cout<<__LINE__<<endl;
						for(size_t i = 0; i<contours.size(); i++)
						{
								cv::approxPolyDP(cv::Mat(contours[i]), whiteContoursPoly[i],3, true);
								boundRect[i]=cv::boundingRect(Mat(whiteContoursPoly[i]));
						}
						cout<<__LINE__<<endl;
						for (size_t i = 0; i< contours.size(); i++)
						{
							cout<<__LINE__<<endl;
							for(int j =0; j<frameList.size(); j++)
							{
								cout<<__LINE__<<endl;
								if(cv::contourArea(whiteContoursPoly[i])>500)
								{
									cout<<__LINE__<<endl;
									x += boundRect[i].tl().x;
									cout<<__LINE__<<endl;
									y += boundRect[i].tl().y;
									width  = boundRect[i].br().x-boundRect[i].tl().x;
									height = boundRect[i].br().y-boundRect[i].tl().y;
									Rect roiRec = cv::Rect(x,y,width,height);
									cv::rectangle(greenRectFrameList[j], roiRec, Scalar(0,0,255), 2, 8, 0);
									if(roiRec.x >= 0 && roiRec.y >= 0 && roiRec.width + roiRec.x < inputWidth && roiRec.height + roiRec.y < inputHeight)
									{
										cv::Mat tempImage = cv::Mat(frameList[j])(roiRec);
										namedWindow("greenHueImage - ROIs", WINDOW_AUTOSIZE);
										imshow("green - ROIs",tempImage);
										//ROIs.push_back(tempImage);
										//coordinates[i].push_back(j);
										cout<<__LINE__<<endl;
									}
								}
							}
						}
					}
				}
				return greenRectFrameList;
			}
			else{
				return redRectFrameList;
			}
		}
}
