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

  // Check Connection to Cameras
  *advance = Camera::getListStatus(CamList, CamList.size());
  if(!*advance)
  {
    std::cout<<"Connection Error, \n program terminated"<<std::endl;
    return -1;
  }

  // Begin Visualization Thread
  boost::thread workerThread1 (&Camera::showFrame, camStream, advance, capture, std::ref(MUTEX));

  // Main Loop
  while(*advance)
  {  
    // Get Frame
    Camera::updateFrameList(camStream, CamList, CamList.size(), std::ref(MUTEX));

    
  }


  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}