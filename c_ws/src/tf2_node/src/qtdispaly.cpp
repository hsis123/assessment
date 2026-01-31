#include "rclcpp/rclcpp.hpp"
#include "rm_interfaces/msg/target_info.hpp"
#include <QApplication>
#include <QLabel>
#include <QString>

class dispaly :public rclcpp::Node
{
public :
dispaly() : Node("dispaly")
{
Subscription_ = this->create_subscription<rm_interfaces::msg::TargetInfo>
("/target_info",10,
    [&](std::shared_ptr<const rm_interfaces::msg::TargetInfo> msg)->
void{label_->setText(get_qstr_from_msg(msg));} );

label_ = new QLabel(get_qstr_from_msg(std::make_shared<rm_interfaces::msg::TargetInfo>()));
label_->show();
}



QString get_qstr_from_msg(std::shared_ptr<const rm_interfaces::msg::TargetInfo> msg){
std::stringstream show_str;
show_str
<<"target cooridnate in base_link\n"
<<"x :"<<msg->x<<"\n"
<<"y :"<<msg->y<<"\n"
<<"z :"<<msg->z<<"\n"
<<"================";

return QString::fromStdString(show_str.str());
}
private :

QLabel* label_;
rclcpp::Subscription<rm_interfaces::msg::TargetInfo>::SharedPtr Subscription_;
};

int main(int agrc,char **agrv){
rclcpp::init(agrc,agrv);
QApplication app(agrc,agrv);
auto node = std::make_shared<dispaly>();
std::thread spin_thread([&]()-> void{rclcpp::spin(node);});
spin_thread.detach();
app.exec();
rclcpp::shutdown();
return 0;
}