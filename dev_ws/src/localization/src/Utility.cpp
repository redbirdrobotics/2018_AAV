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
std::vector<cv::Mat> Utility::combineFilters(std::vector<cv::Mat> RedFrameList, std::vector<cv::Mat> GreenFrameList, std::vector<cv::Mat> WhiteFrameList, std::vector<cv::Mat> output){
  if(!RedFrameList[0].empty() && !GreenFrameList[0].empty() && !WhiteFrameList[0].empty()){
    output.resize(RedFrameList.size()+GreenFrameList.size()+WhiteFrameList.size());
    for (size_t i = 0; i < output.size(); i++) {
      if(i<RedFrameList.size()){
        output[i]=RedFrameList[i];
      }
      if((i>RedFrameList.size())&&(i-RedFrameList.size())<GreenFrameList.size()){
        output[i]=GreenFrameList[(i-RedFrameList.size())];
      }
      if((i > (RedFrameList.size()+GreenFrameList.size() )) && (i-(RedFrameList.size()+GreenFrameList.size()))< WhiteFrameList.size()) {
        output[i]=WhiteFrameList[ (i-(RedFrameList.size()+GreenFrameList.size())) ];
      }
    }
    return output;
  }
  else{
    cout<<"Fuck up in " __FILE__ << " Line: " << __LINE__ << " function: " << __FUNCTION__ <<endl;
  }
}
