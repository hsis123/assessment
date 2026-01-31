#include <memory>
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/utils.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include <chrono>
#include "rm_interfaces/msg/target_info.hpp"
using namespace std::chrono_literals;

class TFlistener : public rclcpp::Node
{
public:
TFlistener() : Node("TFListener_"){
    buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_,this);
    timer_ = this->create_wall_timer(500ms,std::bind(&TFlistener::getTransform,this));
    targetinfo_subscription_ = this->create_subscription<rm_interfaces::msg::TargetInfo>(
 "target_in_camera", 10, std::bind(&TFlistener::callback,this,std::placeholders::_1));
    targetinfo_publish_ = this->create_publisher<rm_interfaces::msg::TargetInfo>("/target_info",10);

}

void getTransform()
{
    try
    {
        auto transform = buffer_->lookupTransform(
            "base_link","camera_link",this->get_clock()->now());
        rclcpp::Duration::from_seconds(1.0f);
       
        
    }
    catch(tf2::TransformException &e){
        RCLCPP_WARN(this->get_logger(),"error:%s",e.what());
    }
}

private:
void callback( std::shared_ptr<const rm_interfaces::msg::TargetInfo> msg){
  RCLCPP_INFO(this->get_logger(),"%f %f %f",msg->x,msg->y,msg->z);
  geometry_msgs::msg::PointStamped point_crame;
  point_crame.header.frame_id="camera_link";
  point_crame.header.stamp = this->get_clock()->now();
  point_crame.point.x = msg->x;
  point_crame.point.y = msg->y;
  point_crame.point.z = msg->z;
  try
  {
    geometry_msgs::msg::PointStamped point_base;
    buffer_->transform(point_crame,point_base,"base_link",tf2::durationFromSec(0.5) );

    rm_interfaces::msg::TargetInfo target_info_;
    target_info_.x = point_base.point.x;
    target_info_.y = point_base.point.y;
    target_info_.z = point_base.point.z;
    targetinfo_publish_->publish(target_info_);

    
  }
  catch(tf2::TransformException& e)
  {
    RCLCPP_WARN(get_logger(),"tranform error:%s",e.what());
  }
  
}
private:
std::shared_ptr<tf2_ros::Buffer> buffer_;
std::shared_ptr<tf2_ros::TransformListener> listener_;
rclcpp::TimerBase::SharedPtr timer_;
rclcpp::Publisher<rm_interfaces::msg::TargetInfo>::SharedPtr targetinfo_publish_;
rclcpp::Subscription<rm_interfaces::msg::TargetInfo>::SharedPtr targetinfo_subscription_;
};

int main(int argc , char** argv)
{
  rclcpp::init(argc,argv);
  auto node = std::make_shared<TFlistener>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}