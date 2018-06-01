#include "ros/ros.h"
#include "std_msgs/String.h"
#include "opencv2/opencv.hpp"
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>
#include <X11/Xlib.h>
#include "Camera.h"
#include "Robot.h"
#include "Communication.h"
#include "Detection.h"
#include "Calibration.h"
#include "Constants.h"
#include "talk.h"

int main(int argc, char **argv)
{
  //Test MSG
  int x=5;
  int y=6;

  // ROS node information
  ros::init(argc, argv, "localization");
  ros::NodeHandle n;

  // Initialize Threading
  XInitThreads();

  // Initialize Pointers for Thread
  boost::shared_ptr< std::vector< cv::Mat > > imgvect_ptr = boost::make_shared< std::vector< cv::Mat > >();
  boost::shared_ptr< bool > advance = boost::make_shared< bool >(true);
  boost::shared_ptr< bool > capture = boost::make_shared< bool >(false);
  boost::mutex MUTEX;

  // Initialize Cameras
  boost::shared_ptr< std::vector< Camera > > camvect_ptr = boost::make_shared< std::vector< Camera > >();
  Camera::FillCamVect_Ptr(camvect_ptr, 1, cv::Size(640, 480), 15);

  // Initialize Robots
  // Red
  Robot daredevil(0);
  Robot deadpool(0);
  Robot elmo(0);
  Robot hellboy(0);
  Robot flash(0);

  // Green
  Robot hulk(1);
  Robot yoshi(1);
  Robot yoda(1);
  Robot arrow(1);
  Robot beastboy(1);

  // Obstacle (White)
  Robot baymax(2);
  Robot stayPuft(2);
  Robot kingBoo(2);
  Robot rorschach(2);

  // Initialize Robot Vector
  std::vector<Robot> redRobotList = {daredevil, deadpool, elmo, hellboy, flash};
  std::vector<Robot> greenRobotList = {hulk, yoshi, yoda, arrow, beastboy};
  std::vector<Robot> whiteRobotList = {baymax, stayPuft, kingBoo, rorschach};

  boost::shared_ptr< std::vector< Robot > > pRedRobotList2 = boost::make_shared< std::vector< Robot > >(redRobotList);
  boost::shared_ptr< std::vector< Robot > > pGreenRobotList = boost::make_shared< std::vector< Robot > >(greenRobotList);
  boost::shared_ptr< std::vector< Robot > > pWhiteRobotList = boost::make_shared< std::vector< Robot > >(whiteRobotList);
  std::cout<<"Robots Initialized"<<std::endl;

  // Initialize Detection Instance
  Detection Detect(cam_consts::_NUM_CAMS_, cam_consts::_FRAME_SIZE_);

  // Check Connection to Cameras
  *advance = Camera::GetStatus_CamVect(camvect_ptr);
  if(!*advance)
  {
    std::cout<<"Connection Error, \n program terminated"<<std::endl;
    return -1;
  }

  // Get Detection Parameters
  Communication::getDetection_XMLData(&Detect);
  //Detect.PrintRedThreshParameters();

  Calibration Calib(cam_consts::_NUM_CAMS_, cam_consts::_FRAME_SIZE_, cam_consts::_FOV_);

  // Begin Visualization Thread
  boost::thread workerThread1(&Camera::ShowFrameVect, imgvect_ptr, advance, capture, std::ref(MUTEX));

  // Main Loop
  while(*advance)
  {
    // Get Frame
    Camera::UpdateFrameVect(camvect_ptr, imgvect_ptr, std::ref(MUTEX));

    Detect.Search(imgvect_ptr);

    Detect.PrintSearchResults();

    Detect.DrawRects(imgvect_ptr, std::ref(MUTEX));

    talk::Talker(n,x,y);

    Detect.ClearMembers();
  }

  ros::spin();
  return 0;
}
