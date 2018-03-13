#include <iostream>
//#include <boost/make_shared.hpp>
//#include <boost/thread/mutex.hpp>
#include "opencv2/opencv.hpp"
//#include <X11/Xlib.h>
//#include <boost/thread.hpp>
#include "opencv2/features2d.hpp"


#ifndef CAMERA_CLASS
#define CAMERA_CLASS

class Camera
{
private:
	cv::VideoCapture a_stream;
	uint32_t a_port;
	std::string a_ID;
	bool a_connect;
	std::vector< cv::Mat > a_frameList;

public:
	// ##### INITIALIZER:
	// Description:		Make an instance of Camera
	// Arguments:
	// ID (string) 		This is just a unique string to identify the camera by something other than its port
	// Port (uint32_t) 	This is the port that the camera is plugged into. I think 0 is default and most
	// 					computers just increment the port as you plug in more cameras. For cameras which are
	//					built into computer sometimes those are default but sometimes not, play around a bit!

	// ##### GETSTATUS:
	// Description:		Returns Status attribute (whether successfully connected) of Camera instance.
	// Notes: 			Most porgrams will have 2 generic types of functions, Getters and Setters. Getters
	//					"get" private variables and Setters "set" private variables. As a precaution, some
	//					functions will check if a camera is connected before it performs any actions.  This
	//					saves you from strange error messages further down the line.

	// ##### GETID:
	// Description:		Returns the ID atrribute of the camera instance
	// Notes:			This is helpful when I am storing photos on the computer. I make A folder with the
	//					unique camera name and then each photo from that camera goes in its corresponding folder

	// ##### GETFRAME:
	// Description:		Gets a frame from the camera passed into it.  If you pass "true" in as second variable it
	//					will add the frame to a vector of frames which is an attribute of this class
	// Notes:			Bool argument is default false, which means it will not add the frame to a vector of frames.
	//					I think I use the second argument more in my Stereoscopic Class, so we will eventually get
	//					there.

	// ##### GETFRAME:
	// Disclaimer:		I wont use this for this tutorial
	// Description:		Gets a frame from camera and stores it in a matrix which is shared between threads.
	// Arguments:
	// Shared Matrix (boost::shared_ptr< cv::Mat >)		This is a matrix which is shared between threads. Why? Good
	//													question. In the future you may find yourself making a
	//													Graphical User Interphase (GUI) which needs to be asyncronous
	//													from your main loop.
	//													Anyways, a boost::shared_ptr is just a way to transport/share
	//													the data, in this case a matrix, with another thread

	// ##### GETLISTSTATUS:
	// Desription:		Get status of whole vector of cameras.
	// Arguments:
	// vector of Cameras (vector<Camera>) 	Exactly what it says it is. I should actually make this a const read only
	//										In the interest of getting this to you quickly I will just note my errors.
	//
	// number of Cameras (int)				instead of determining inside function, just pass it
	//
	// Notes:			Notice that it only returns a single boolean instead of a vector of booleans. This is because
	//					in the code I "and" all the statuses together. Basically it only takes one of the cameras not
	//					being connected to return a false

	// ##### UPDATEFRAMELIST:
	// Description:		Pulls one image from each camera, which is then stored in a vector which is shared between
	//					threads.
	// Arguments:
	// MUTEX (boost::mutex&) 	This is the name of the genetic marker which identifies mutants in Xmen.  JK. This is
	//							skipping ahead abit but basically, you could think of it as something that locks
	//							a particular variable into one thread.  Lets say I have 2 threads A and B and in
	//							threadA I want to store an image in a matrix and in threadB I want to show what ever
	//							is stored in the matrix at anytime.  They both cannot access the data at the same
	//							time. Which ever function has the active mutex is the one who owns the variable.
	//							So in threadA I lock the matrix with the mutex store the new frame, unlock and threadB
	//							now has access to show the frame again

	// ##### SHOWFRAME:
	// Description:		Displays a vector of frames in separate thread
	// Arguments:
	// Window Name (string):	The title of the window which the frames are displayed in.
	// Shared Matrix:			We already covered
	// Shared Boolean:			If the connection status changes, we need to communicate that to the other thread, so
	//							we pass it a boolean
	// Mutex:					Covered it.
	//
	// Notes:			This function has some errors, it works but its janky.  It should be a vector of strings.
	//					function is a little misleading. It looks like it is dynamic in how many cameras you could pass
	//					it, but it only handles 2.  I wanted this in the future to handle as many as you pass in BUT,
	//					you make it work first, then trick it out later.

	Camera(std::string, uint32_t);
	bool getStatus();
	std::string getID();
	cv::Mat getFrame(cv::Mat, bool = false);
	//boost::shared_ptr< cv::Mat > getFrame(boost::shared_ptr< cv::Mat >);
	static bool getListStatus(std::vector< Camera >, int);
	static std::vector< cv::Mat> updateFrameList(std::vector< cv::Mat>, std::vector< Camera>, int);
	//static void updateFrameList(boost::shared_ptr< std::vector< cv::Mat > >, std::vector< Camera >, int, boost::mutex&);
	static void showFrame(std::vector< Camera>, std::vector< cv::Mat>, bool);
	//For testing pruposes
	static void showFrame(std::vector< Camera > camList, std::string a, std::vector< cv::Mat > frameList, bool connected);
	//static void showFrame(std::string, boost::shared_ptr< std::vector< cv::Mat > >, boost::shared_ptr< bool >, boost::mutex&);
	//********** Lukas' Code **********//
	static std::vector< cv::Mat>  blobDetection(std::vector<cv::Mat>, std::vector<Camera>);
};

#endif
