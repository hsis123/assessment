#include <memory>
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

class StaticTFBroadcaster : public rclcpp::Node
{
  public:
  StaticTFBroadcaster() : Node("static_tf_publish"){
    broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
    this->publish_tf();
  }
  
  void  publish_tf()
  {
    geometry_msgs::msg::TransformStamped transform_;
    transform_.header.stamp=rclcpp::Time(0);
    transform_.header.frame_id="base_link";
    transform_.child_frame_id="camera_link";
    transform_.transform.translation.x = 0.1;
    transform_.transform.translation.y = 0.0;
    transform_.transform.translation.z = 0.0;
    transform_.transform.rotation.x = 0.0;
    transform_.transform.rotation.y = 0.0;
    transform_.transform.rotation.z = 0.0;
    transform_.transform.rotation.w = 1.0;

    broadcaster_->sendTransform(transform_);
    
  }
  private:
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster_;
};


    int main(int argc , char** argv)
{
  rclcpp::init(argc,argv);
  auto node = std::make_shared<StaticTFBroadcaster>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

