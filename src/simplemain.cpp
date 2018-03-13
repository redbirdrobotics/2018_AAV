#include <iostream>
#include "opencv2/opencv.hpp"
#include "Camera.h"
#include "BlobDetector.h"
#include "Test.h"
using namespace cv;
using namespace std;
int main()
{
	try{
	//*** INITIALIZE CAMERA INSTANCES ***//
	Camera Cam0("Augustus", 0);
	// Camera Cam1("Tiberius", 1);
	//std::vector< Camera > CamList = {Cam0, Cam1, Cam2, Cam3, Cam4, Cam5, Cam6, Cam7, Cam8, Cam9};
	std::vector< Camera > CamList = {Cam0};

	//*** INITIALIZE VARIABLES ***//
	bool connected;
	std::vector< cv::Mat> frameList;
	std::vector< cv::Mat> blobList, testList;
	//*** CHECK CONNECTION TO CAMERAS ***//

	//***            TEST             ***//
	// cv::VideoCapture capture("/home/ghost/Videos/Webcam/red_plate_test_vid.mp4");
  //
  // int totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
  //
  // cv::Mat currentFrame;
  //
  // for(int i=0; i < totalFrameNumber; i++)
  // {
  //    capture>>currentFrame;
  //    frameList.push_back(currentFrame.clone());
	// }

	connected = Camera::getListStatus(CamList, CamList.size());
	if(!connected)
	{
		std::cout<<"connection error"<<std::endl;
		return -1;
	}

	while(connected)
	{
		connected = Camera::getListStatus(CamList, CamList.size());
		frameList = Camera::updateFrameList(frameList, CamList, CamList.size());
		cout<<__LINE__<<endl;
		blobList = BlobDetector::findRobots(frameList);
		//testList=Test::testColor(frameList);
		Camera::showFrame(CamList, blobList, connected);
		//Camera::showFrame(CamList," - test Detection", testList, connected);
	}}
	catch(const std::exception& e){
		std::cerr<< e.what() << std::endl;
		return -1;
	}
}
