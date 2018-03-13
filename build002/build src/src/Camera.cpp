#include "Camera.h"
using namespace std;
Camera::Camera(std::string name, uint32_t port) : a_connect(false), a_ID(name)
{
	a_stream.open(port);
	if(a_stream.isOpened())
	{
		std::cout<< a_ID <<" Connected"<<std::endl;
		a_connect = true;
	}
}

bool Camera::getStatus() {return a_connect;}

std::string Camera::getID() {return a_ID;}

// boost::shared_ptr< cv::Mat > Camera::getFrame(boost::shared_ptr< cv::Mat > frame)
// {
// 	a_stream.read(*frame);
// 	if(frame->empty())
// 	{
// 		std::cout<<"empty frame"<<std::endl;
// 	}
// 	return frame;
// }

cv::Mat Camera::getFrame(cv::Mat frame, bool add)
{
	a_stream.read(frame);
	if(frame.empty())
	{
		std::cout<<"empty frame"<<std::endl;
	}
	if(add == true)
	{
		a_frameList.push_back(frame);
	}
	return frame;
}

bool Camera::getListStatus(std::vector< Camera > CamList, int size)
{
	bool totalConnect = true;
	for(int i=0; i<size; i++)
	{
		if(!CamList[i].getStatus())
		{
			std::cout<<"Camera "<<i<<" is not connected"<<std::endl;
			totalConnect = false;
		}
	}
	return totalConnect;
}

std::vector< cv::Mat> Camera::updateFrameList(std::vector< cv::Mat> frameList, std::vector< Camera > CamList, int size)
{
	if(frameList.empty())
	{
		for(int i=0; i<size; i++)
		{
			cv::Mat frame;
			frame = CamList[i].getFrame(frame);
			frameList.push_back(frame);
		}
	}

	else
	{
		for(int i=0; i<size; i++)
		{
			cv::Mat* pMat = new cv::Mat;
			frameList[i]=CamList[i].getFrame(*pMat);
		}
	}
return frameList;
}

// void Camera::updateFrameList(boost::shared_ptr< std::vector< cv::Mat > > frameList, std::vector< Camera > CamList, int size, boost::mutex& MUTEX)
// {
// 	//boost::lock_guard<boost::mutex> guard(MUTEX);
// 	//std::cout<<"Grabbing "<<size<<" Frames"<<std::endl;

// 	if(frameList->empty())
// 	{
// 		for(int i=0; i<size; i++)
// 		{
// 			cv::Mat* pMat = new cv::Mat;
// 			frameList->push_back(*pMat);
// 		}
// 	}

// 	for(int i=0; i<size; i++)
// 	{
// 		cv::Mat* pMat = new cv::Mat;
// 		(*frameList)[i]=CamList[i].getFrame(*pMat);
// 	}
// }

//void Camera::getFrame()

/*void Camera::showFrame(std::string window, boost::shared_ptr< std::vector< cv::Mat > > frameList, boost::shared_ptr< bool > connected, boost::mutex& MUTEX)
{
	int size = frameList->size();
	while(*connected == true)
	{
		for(int i=0; i<size; i++)
		{
			if(! (*frameList)[i].empty() )
			{
				cv::imshow(window+std::to_string(i), (*frameList)[i]);
			}
		}
		if(cv::waitKey(30) >= 0)
		{
			*connected = false;
			//cv::destroyWindow(window);
			return;
		}
	}
}*/

void Camera::showFrame(std::vector< Camera > camList, std::vector< cv::Mat > frameList, bool connected)
{
	if(!frameList[0].empty())
	{
		cv::imshow(camList[0].getID(), frameList[0]);
		//Turn on when I get second camera
		//cv::imshow(camList[1].getID(), frameList[0]);
	}
	// if(!frameList[1].empty())
	// {
	// 	cv::imshow(camList[1].getID(), frameList[1]);
	// }
	if(cv::waitKey(30) >= 0)
	{
		connected = false;
		return;
	}
}

void Camera::showFrame(std::vector< Camera > camList, std::string a, std::vector< cv::Mat > frameList, bool connected)
{
	if(!frameList[0].empty())
	{
		cv::imshow(camList[0].getID()+a, frameList[0]);
		//Turn on when I get second camera
		//cv::imshow(camList[1].getID(), frameList[0]);
	}
	// if(!frameList[1].empty())
	// {
	// 	cv::imshow(camList[1].getID(), frameList[1]);
	// }
	if(cv::waitKey(30) >= 0)
	{
		connected = false;
		return;
	}
}

// void Camera::showFrame(std::string window, boost::shared_ptr< std::vector< cv::Mat > > frameList, boost::shared_ptr< bool > connected, boost::mutex& MUTEX)
// {
// 	//boost::lock_guard<boost::mutex> guard(MUTEX);
// 	while(*connected == true)
// 	{
// 		int size = frameList->size();

// 		if(! (*frameList)[0].empty() )
// 		{
// 			cv::imshow(window, (*frameList)[0]);
// 		}

// 		if(! (*frameList)[1].empty() )
// 		{
// 			cv::imshow(window+std::to_string(1), (*frameList)[1]);
// 		}

// 		if(cv::waitKey(30) >= 0)
// 		{
// 			*connected = false;
// 			//cv::destroyWindow(window);
// 			return;
// 		}

// 		else
// 		{
// 			//std::cerr<<"empty frame\n";
// 		}
// 	}
// }

std::vector<cv::Mat> Camera::blobDetection(std::vector< cv::Mat > frameList, std::vector<Camera> camList){
		if(!frameList[0].empty()){
		// Setup SimpleBlobDetector parameters.
		cv::SimpleBlobDetector::Params params;

		// Change thresholds
		params.minThreshold = 10;
		params.maxThreshold = 200;

		// Filter by Area.
		params.filterByArea = true;
		params.minArea = 1500;

		// Filter by Circularity
		params.filterByCircularity = true;
		params.minCircularity = 0.1;

		// Filter by Convexity
		params.filterByConvexity = false;
		params.minConvexity = 0.87;

		// Filter by Inertia
		params.filterByInertia = false;
		params.minInertiaRatio = 0.01;

		//Filter by Color
		// params.filterByColor = 1;
		// params.blobColor = 100;
	  // Set up detector with params
		cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
		  // SimpleBlobDetector::create creates a smart pointer.
		std::vector<cv::KeyPoint> keyPoints;
		std::vector<cv::Mat> frameListWithKeyPoints;
		frameListWithKeyPoints.resize(frameList.size());
		for(int i=0;i<frameList.size();i++){
			detector->detect(frameList[i], keyPoints);
			cv::drawKeypoints( frameList[i], keyPoints, frameListWithKeyPoints[i], cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		}
    return frameListWithKeyPoints;
	}
	else{
		std::cout<<"Umm how should I put this? \n ... \n You fucked up. \n vector frameList is empty in the first position."<<std::endl;
	}
}
