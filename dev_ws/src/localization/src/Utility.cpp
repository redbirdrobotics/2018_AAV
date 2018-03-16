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

std::vector<cv::Mat> Detection::search(std::vector<cv::Mat> filteredFrameList, std::vector<cv::Rect> rects,
  std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy,
  std::vector<std::vector<cv::Point>> contoursPoly, std::vector<cv::Mat> frameList){
  for(int i=0; i<frameList.size(); i++)
  {
    cv::findContours(filteredFrameList[i], contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
  }
  contoursPoly.resize(contours.size());
  rects.resize(contours.size());
  for(size_t i = 0; i<contours.size(); i++)
  {
    cv::approxPolyDP(cv::Mat(contours[i]), contoursPoly[i], 3, true);
    rects[i]=cv::boundingRect(cv::Mat(contoursPoly[i]));
    for(int j =0; j<frameList.size(); j++)
    {
      if(cv::contourArea(contoursPoly[i])>1000){
        rects[i] = cv::Rect(rects[i].tl().x-50, rects[i].tl().y-50, rects[i].br().x-rects[i].tl().x+100, rects[i].br().y-rects[i].tl().y+100);
        cv::rectangle(frameList[j], rects[i], cv::Scalar(127,127,127), 2, 8, 0);
        if(rects[i].x >= 0 && rects[i].y >= 0 && rects[i].width + rects[i].x < frameList[j].cols && rects[i].height + rects[i].y < frameList[j].rows){
          
        }
      }
  }
  return frameList;
}





Utility::applyFilter(cv::Mat* inFrame, cv::Mat* outFrame, std::vector<int> threshold)
{
  cv::inRange(&inframe, cv::Scalar(threshold[0], threshold[1], threshold[2]), cv::Scalar(threshold[3], threshold[4], threshold[5]), &outFrame);
}

Utility::applyAllFilters(std::vector<cv::Mat*> inFrameList, std::vector< std::vector<cv::Mat*> > outFrameList, std::vector< std::vector<int> > threshList)
{
  for(int i=0; i<threshList.size(); i++)
  {
    for(int j=0; j<outFrameList.size(); j++)
    {
      cv::Mat frame;
      outFrameList[j].push_back(frame);
      applyFilter(inFrameList[j], outFrameList[j][i], threshList[i]);
    }
  }
}

Detection::search(std::vector<cv::Mat*> inFrameList, std::vector< std::vector<cv::Mat*> > outFrameList, std::vector<Robot> robotList, std::vector<cv::Rect> rectList)
{
  Utility::applyAllFilters(inFrameList, outFramelist, robotList[0]->thresList);
} 
