#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "sensor_msgs/msg/image.hpp"
#include <cv_bridge/cv_bridge.h>
#include "vision_detector/detector.hpp"
#include "rm_interfaces/msg/target_info.hpp"

class VisionDetectorNode : public rclcpp::Node
{
public:
VisionDetectorNode() : Node("vision_detector")
{
int lower_h_1 = this->declare_parameter("lower_h_1",0);
int lower_s_1 = this->declare_parameter("lower_s_1",100);
int lower_v_1 = this->declare_parameter("lower_v_1",100);
int upper_h_1 = this->declare_parameter("upper_h_1",10);
int upper_s_1 = this->declare_parameter("upper_s_1",255);
int upper_v_1 = this->declare_parameter("upper_v_1",255);
int lower_h_2 = this->declare_parameter("lower_h_2",156);
int lower_s_2 = this->declare_parameter("lower_s_2",100);
int lower_v_2 = this->declare_parameter("lower_v_2",100);
int upper_h_2 = this->declare_parameter("upper_h_2",180);
int upper_s_2 = this->declare_parameter("upper_s_2",255);
int upper_v_2 = this->declare_parameter("upper_v_2",255);

detector_ = std::make_shared<Detector>(
  cv::Scalar(upper_h_1,upper_s_1,upper_v_1),
  cv::Scalar(lower_h_1,lower_s_1,lower_v_1),
  cv::Scalar(upper_h_2,upper_s_2,upper_v_2),
  cv::Scalar(lower_h_2,lower_s_2,lower_v_2)
  );
vision_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/image_processed",10);
targetinfo_publisher_  = this->create_publisher<rm_interfaces::msg::TargetInfo>("target_in_camera",10);
vision_subscricption = this->create_subscription<sensor_msgs::msg::Image>("/image_raw",10,
    std::bind(&VisionDetectorNode::img_callback,this,std::placeholders::_1));
 
    RCLCPP_INFO(this->get_logger(), "VisionDetectorNode 启动成功！");
    RCLCPP_INFO(this->get_logger(), "颜色范围1 HSV:[%d,%d,%d] ~ [%d,%d,%d]",
                lower_h_1, lower_s_1, lower_v_1, upper_h_1, upper_s_1, upper_v_1);
    RCLCPP_INFO(this->get_logger(), "颜色范围2 HSV:[%d,%d,%d] ~ [%d,%d,%d]",
                lower_h_2, lower_s_2, lower_v_2, upper_h_2, upper_s_2, upper_v_2);


}



private:
void img_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg)
{
  try{
  cv::Mat frame = cv_bridge::toCvCopy(msg,"bgr8")->image;
  if(frame.empty()){
    RCLCPP_WARN(this->get_logger(),"get empty frame");
    return ;
  }
  
  //cv::imshow("1",frame);
  std::vector<img_element> targets = detector_->color_detector(frame);
  if(targets.empty())
  {
    RCLCPP_WARN(this->get_logger(),"target empty");
  }

  cv::Mat result = frame.clone();
  for(auto target : targets)
  {
   cv::circle(result,target.center_,5,cv::Scalar(255,0,0),-1);
    cv::rectangle(result,target.Rect_,cv::Scalar(255,0,0),3);
    double center_x = frame.cols/2;
    double center_y = frame.rows/2;
  pinholecamera_ = std::make_shared<PinholeCamera>(center_x,center_y,0.5,target.center_.x,target.center_.y);
    coordinate coordinate_ = pinholecamera_->CoordinateDetector();
    rm_interfaces::msg::TargetInfo targetcoordinate_;
    targetcoordinate_.x = coordinate_.x;
    targetcoordinate_.y = coordinate_.y;
    targetcoordinate_.z = coordinate_.z;
    RCLCPP_INFO(this->get_logger(),"%f %f %f",coordinate_.x,coordinate_.y,coordinate_.z);
    targetinfo_publisher_->publish(targetcoordinate_);
  }


try{
    auto cv_image = cv_bridge::CvImage(
      std_msgs::msg::Header(),
      "bgr8",
      result
    );
      cv_image.header.stamp = this->get_clock()->now();
      cv_image.header.frame_id = "result frame";

    sensor_msgs::msg::Image::SharedPtr ros_image = cv_image.toImageMsg();
    vision_publisher_->publish(*ros_image);
    RCLCPP_INFO(this->get_logger(),"publishtime: %lld",cv_image.header.stamp.sec);
  }
  catch(cv_bridge::Exception &a){
    RCLCPP_INFO(this->get_logger(),"cv_bridge excharge failure :%s",a.what());
  }


  }
//publish result
catch(cv_bridge::Exception &e){
RCLCPP_ERROR(this->get_logger(), "cv_bridge excharge failure: %s", e.what());
}
catch (std::exception& e)
    {
      RCLCPP_ERROR(this->get_logger(), "deal image failure: %s", e.what());
    }
//deal frame 


}

private:
rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr vision_subscricption;
std::shared_ptr<Detector> detector_;
rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr vision_publisher_;
rclcpp::Publisher<rm_interfaces::msg::TargetInfo>::SharedPtr targetinfo_publisher_;
std::shared_ptr<PinholeCamera> pinholecamera_;
};


int main(int argc , char** argv)
{
  rclcpp::init(argc,argv);
  auto node = std::make_shared<VisionDetectorNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  cv::destroyAllWindows();
  return 0;
}

