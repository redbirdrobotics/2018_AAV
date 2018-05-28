#include "Camera.h"

Camera::Camera(uint8_t port, cv::Size frame_size, uint8_t fps) 
: _connected(false), _port(port), _frame_size(frame_size), _fps(fps)
{
	_cam_stream.open(port);
	if(_cam_stream.isOpened())
	{
		_cam_stream.set(CV_CAP_PROP_FRAME_WIDTH, frame_size.width);
		_cam_stream.set(CV_CAP_PROP_FRAME_HEIGHT, frame_size.height);
		_cam_stream.set(CV_CAP_PROP_FPS, fps);
		_connected = true;
	}
}

void Camera::FillCamVect_Ptr(boost::shared_ptr< std::vector< Camera > > camvect_ptr, uint8_t num_cams, cv::Size frame_size, uint8_t fps)
{
	for(uint8_t i=0; i<num_cams; i++)
	{
		Camera cam(i, frame_size, fps);
		camvect_ptr->push_back(cam);
	}
}

uint8_t Camera::GetPort() {return _port;}

bool Camera::GetStatus() {return _connected;}

bool Camera::GetStatus_CamVect(boost::shared_ptr< std::vector< Camera > > camvect_ptr)
{
	bool total_connect = true;
	for(uint8_t i=0; i<camvect_ptr->size(); i++)
	{
		if(!(*camvect_ptr)[i].GetStatus())
		{
			std::cout<<"Camera "<<(int)i<<": Not Connected"<<std::endl;
			total_connect = false;
		}
		std::cout<< "Camera " <<(int)i<< ": Connected" <<std::endl;
	}
	return total_connect;
}

cv::Mat Camera::GetFrame(cv::Mat frame)
{
	_cam_stream.read(frame);
	if(frame.empty())
	{
		std::cout<<"empty frame"<<std::endl;
	}
	return frame;
}

// Used to populate an image vector which will be displayed in another thread
void Camera::UpdateFrameVect(boost::shared_ptr< std::vector< Camera > > camvect_ptr, boost::shared_ptr< std::vector< cv::Mat > > framevect_ptr, boost::mutex& MUTEX)
{
	boost::lock_guard<boost::mutex> guard(MUTEX);
	if(framevect_ptr->empty())
	{
		// framevect_ptr
		for(uint8_t i=0; i<2; i++)
		{
			cv::Mat displayimgs;
			framevect_ptr->push_back(displayimgs);
		}
	}

	for(uint8_t i=0; i<camvect_ptr->size(); i++)
	{
		(*framevect_ptr)[i] = (*camvect_ptr)[i].GetFrame((*framevect_ptr)[i]);
	}
}

// void Camera::UpdateFrameList(boost::shared_ptr< std::vector< Camera > camvect_ptr, boost::shared_ptr< std::vector< std::vector< cv::Mat > > > frameList, int size, boost::mutex& MUTEX)
// {
// 	if(frameList->empty())
// 	{
// 		std::cout<<"Creating 2 Containers for "<<size<<" Frames"<<std::endl;
// 		std::vector<cv::Mat> row1, row2;
// 		(*frameList).push_back(row1);
// 		(*frameList).push_back(row2);
// 	}

// 	for(int i=0; i<2; i++)
// 	{
// 		cv::Mat* pMat = new cv::Mat;

// 		(*frameList)[i].push_back(CamList[i]->getFrame(*pMat));
// 	}

// 	std::printf( "%d Pictures Captured! \n", (int)((*frameList)[0].size()) );
// }

void Camera::ShowFrameVect(boost::shared_ptr< std::vector< cv::Mat > > framevect_ptr, boost::shared_ptr< bool > connected, boost::shared_ptr< bool > capture, boost::mutex& MUTEX)
{
	uint8_t key;
	bool toggle = true;

	while(*connected == true)
	{
		if(framevect_ptr->empty()) continue;

		key = cv::waitKey(30);

		// Close program (esc)
		if(key == 27)
		{
			*connected = false;
			return;
		}

		// Capture image (space)
		else if(key == 32)
		{
			*capture = true;
		}

		// Toggle display (t)
		if(key == 116)
		{
			toggle = !toggle;
			if(toggle == false)
			{
				cv::destroyAllWindows();
			}
		}

	 	if(toggle == true)
		{
			boost::lock_guard<boost::mutex> guard(MUTEX);

	 		if(! (*framevect_ptr)[0].empty() )
			{
	 			cv::imshow("window1", (*framevect_ptr)[0]);
			}

			if(! (*framevect_ptr)[1].empty() )
			{
				cv::imshow("window2", (*framevect_ptr)[1]);
			}
		}
	}
}

std:: string Camera::get_tegra_pipeline() 
{
    return "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(tegra_width) + ", height=(int)" +
           std::to_string(tegra_height) + ", format=(string)I420, framerate=(fraction)" + std::to_string(tegra_fps) +
           "/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}
