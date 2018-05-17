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

int main(int argc, char **argv)
{
  // ROS node information
  ros::init(argc, argv, "localization");
  ros::NodeHandle n;

  // Initialize Threading
  XInitThreads();

  // Initialize Pointers for Thread
  boost::shared_ptr< std::vector< cv::Mat > > camStream = boost::make_shared< std::vector< cv::Mat > >();
  boost::shared_ptr< bool > advance = boost::make_shared< bool >(true);
  boost::shared_ptr< bool > capture = boost::make_shared< bool >(false);
  boost::mutex MUTEX;

  // Initialize Cameras
  Camera Cam1("Augustus", 0);
  std::vector< Camera* > CamList = {&Cam1};

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

  // Initialize Detection Instance
  Detection Detect(CamList.size());

  Detect.setRedRobots(&redRobotList);
  Detect.setGreenRobots(&greenRobotList);
  Detect.setWhiteRobots(&whiteRobotList);

  // Check Connection to Cameras
  *advance = Camera::getListStatus(CamList, CamList.size());
  if(!*advance)
  {
    std::cout<<"Connection Error, \n program terminated"<<std::endl;
    return -1;
  }

  //test
  //cv::namedWindow("TEST", CV_WINDOW_AUTOSIZE);

  // // Get Robot Parameters
  Communication::getDetection_XMLData(&Detect);

  // Begin Visualization Thread
  boost::thread workerThread1(&Camera::showFrame, camStream, advance, capture, std::ref(MUTEX));

  // Main Loop
  while(*advance)
  {

    // Get Frame
    Camera::updateFrameList(camStream, CamList, CamList.size(), std::ref(MUTEX));
    std::cout<<" Line: " << __LINE__ <<std::endl;
    Detect.Search(camStream);
    std::cout<<" Line: " << __LINE__ <<std::endl;
    // Detect.showMask();

    //cv::imshow("TEST",Detect.showMask());
  }

  ros::spin();
  return 0;
}
