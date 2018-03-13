#include "Camera.h"
#include "Detection.h"
using namespace std;
std::vector<cv::Mat> Detection::findColors(std::vector< cv::Mat > inputFrameList, std::vector<int> range ,std::vector<cv::Mat> outputFrameList){
	if(!inputFrameList[0].empty()){
		//Resize Vectors
		outputFrameList.resize(inputFrameList.size());
		//cycles through frameList for color detection
		for(int i=0; i<inputFrameList.size();i++){
			//Find colors in green range
			cv::inRange(inputFrameList[i], cv::Scalar(range[0], range[1], range[2]), cv::Scalar(range[3], range[4], range[5]), outputFrameList[i]);
			// Blur Image
			cv::GaussianBlur(outputFrameList[i], outputFrameList[i], cv::Size(9, 9), 2, 2);
		}
		// return a filtered frameList for green things.
		//	anything thing that is green things will be returned as white pixels and non green things will be returned with pixels
		return outputFrameList;
	}
	else{
	    cout<<"Fuck up in " __FILE__ << " Line: " << __LINE__ << " function: " << __FUNCTION__ <<endl;
	}
}
std::vector<cv::Mat> Detection::findColors(std::vector< cv::Mat > inputFrameList, std::vector<int> range1, std::vector<int> range2, std::vector<cv::Mat> v,std::vector< cv::Mat > outputFrameList){
		if(!inputFrameList[0].empty()){
			outputFrameList.resize(inputFrameList.size());
			v.resize(inputFrameList.size());
			//cycles through frameList for color detection
			for(int i=0; i<inputFrameList.size();i++){
				// Mask
				cv::inRange(inputFrameList[i], cv::Scalar(range1[0], range1[1], range1[2]), cv::Scalar(range1[3], range1[4], range1[5]), outputFrameList[i]);
				cv::inRange(inputFrameList[i], cv::Scalar(range2[0], range2[1], range2[2]), cv::Scalar(range2[3], range2[4], range2[5]), v[i]);

				// Combine the above two images
				cv::addWeighted(outputFrameList[i], 1.0, v[i], 1.0, 0.0, outputFrameList[i]);

				// Blur Image
				cv::GaussianBlur(outputFrameList[i], outputFrameList[i], cv::Size(9, 9), 2, 2);
			}
		// return a filtered frameList for red things.
		//	anything thing that is red things will be returned as white pixels and non red things will be returned with pixels
		return outputFrameList;
	}
	else{
		cout<<"Fuck up in " __FILE__ << " Line: " << __LINE__ << " function: " << __FUNCTION__ <<endl;
	}
}
// std::vector<cv::Mat> Detection::findRobots(std::vector<cv::Mat> inputFrameList, std::vector<cv::Mat> outputFrameList)
// {
// 		if(!frameList[0].empty())
// 		{
// 			std::vector<std::vector<cv::Point>> contours;
// 			std::vector<cv::Vec4i> hierarchy;
// 			std::vector<cv::Mat> redRectFrameList= inputFrameList;
// 			std::vector<cv::Mat> blueRectFrameList;
// 			std::vector<cv::Mat> greenRectFrameList;
// 			std::vector<cv::Mat> redFrameList(inputFrameList.size());
// 			std::vector<cv::Mat> blackROIs;
// 			int x = 0;
// 			int y = 0;
// 			int width = 0;
// 			int height = 0;
// 			int inputWidth =0;
// 			int inputHeight =0;
// 			redFrameList=BlobDetector::findColors(inputFrameList);
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
