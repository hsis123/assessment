#ifndef DETECTOR_HPP
#define DETECTOR_HPP
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


struct img_element
{
   cv::Point center_;
   cv::Rect Rect_;
};

struct coordinate
{
   double x;
   double y;
   double z;
};

class Detector
{
 public:
  Detector(cv::Scalar upper1,cv::Scalar lower1,cv::Scalar upper2,cv::Scalar lower2):
  upper1(upper1), lower1(lower1),upper2(upper2), lower2(lower2),MIN_CONTOUR_AREA(100.0){}

 std::vector<img_element> color_detector(const cv::Mat &image);
private:
   cv::Scalar upper1;
   cv::Scalar lower1;
   cv::Scalar upper2;
   cv::Scalar lower2;
   const double MIN_CONTOUR_AREA;


};


class PinholeCamera
{
   public:
   PinholeCamera(const double target_x,const double target_y,const double target_depth,const double center_x,const double center_y):
   center_x_ (center_x),center_y_(center_y),
   target_x_(target_x),target_y_(target_y),target_depth_(target_depth){}

   coordinate CoordinateDetector();
   private : 

   double center_x_ ;
   double center_y_ ;
   double focal_length_x_ = 500.0;
   double focal_length_y_ = 500.0;

   double target_x_;
   double target_y_;
   double target_depth_;
   
};

#endif