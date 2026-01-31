#include "vision_detector/detector.hpp"

std::vector<img_element> Detector::color_detector(const cv::Mat &image){
  cv::Mat hsvimg ;
  cv::cvtColor(image,hsvimg,cv::COLOR_BGR2HSV);
  cv::Mat gauss;
  cv::GaussianBlur(hsvimg,gauss,cv::Size(5,5),1);
  cv::Mat mask1,mask2;
  cv::inRange(gauss,lower1,upper1,mask1);
  cv::inRange(gauss,lower2,upper2,mask2);
  cv::Mat mask = mask1|mask2;
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
  cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
  cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(mask,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);
  
  std::vector<img_element> targets;
  for(const auto &contour:contours){
    double area = cv::contourArea(contour);
    if(area < MIN_CONTOUR_AREA)
    {
       continue;
    }
    cv::Rect rect = cv::boundingRect(contour);
    cv::Point center(rect.x+rect.width/2,rect.y+rect.height/2);
    img_element target;
    target.center_ = center;
    target.Rect_ = rect;
    targets.push_back(target);
  }
  return targets;
}  