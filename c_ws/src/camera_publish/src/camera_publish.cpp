#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "sensor_msgs/msg/image.hpp"
#include <cv_bridge/cv_bridge.h>

class CameraPublishNode : public rclcpp::Node
{
public:
  explicit CameraPublishNode() : Node("camerapublish"){
    camerapublish = this -> create_publisher<sensor_msgs::msg::Image>("/image_raw",10);
    std::string path="/home/liker/Desktop/oyoyo.mp4";
    cup_.open(path);
    if(!cup_.isOpened()){
        RCLCPP_ERROR(this->get_logger(),"donn't get");
      rclcpp::shutdown();
      return;}

    timer_ = this->create_wall_timer(std::chrono::milliseconds(33),std::bind(&CameraPublishNode::cpublish,this));

  }

  private:
  void cpublish(){
    cv::Mat frame;
    bool ret = cup_.read(frame);
    if(!ret||frame.empty()){
      RCLCPP_WARN(this->get_logger(),"failue");
      timer_->cancel();
      return;
    }
    try{
    auto cv_image = cv_bridge::CvImage(
      std_msgs::msg::Header(),
      "bgr8",
      frame
    );
      cv_image.header.stamp = this->get_clock()->now();
      cv_image.header.frame_id = "camera frame";

    sensor_msgs::msg::Image::SharedPtr ros_image = cv_image.toImageMsg();
    camerapublish->publish(*ros_image);
    RCLCPP_INFO(this->get_logger(),"publishtime: %lld",cv_image.header.stamp.sec);
  }
  catch(cv_bridge::Exception &a){
    RCLCPP_INFO(this->get_logger(),"cv_bridge excharge failure :%s",a.what());
  }
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr camerapublish;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cup_;
};

int main(int argc,char** argv)
{
  rclcpp::init(argc,argv);
  auto node = std::make_shared<CameraPublishNode>();
  if(rclcpp::ok()){
  rclcpp::spin(node);
  }
  rclcpp::shutdown();
  return 0;
  

}