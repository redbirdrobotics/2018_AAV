#include "Utility.h"

using namespace std;

std::vector<cv::Mat> Utility::toHSV(std::vector<cv::Mat> inputFrameList, std::vector<cv::Mat> outputFrameList){
  if(!inputFrameList[0].empty())
  {
    std::vector<cv::Mat> outputFrameList(inputFrameList.size());
    for (size_t i = 0; i < inputFrameList.size(); i++) {
      cv::cvtColor(inputFrameList[i], outputFrameList[i], cv::COLOR_BGR2HSV);
    }
    return outputFrameList;
  }
  else{
    cout<<"Fuck up in " __FILE__ << " Line: " << __LINE__ << " function: " << __FUNCTION__ <<endl;
  }
}
