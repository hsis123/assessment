#!/bin/bash

source /opt/ros/humble/setup.bash
source /home/liker/Desktop/camera1/c_ws/install/setup.bash --extend

ROS_DISTRO="humble"
WORKSPACE="/home/liker/Desktop/camera1/c_ws/src"
LAUNCH_COMMAND="ros2 launch my_launch camera_detector.launch.py"
LOG_DIR="$WORKSPACE/log"
LOG_FILE="$LOG_DIR/ros2_project.log"

# 确保日志目录存在
mkdir -p $LOG_DIR

# 加载ROS 2基础环境
source /opt/ros/$ROS_DISTRO/setup.bash

# 进入工作空间（修复语法错误）
cd $WORKSPACE || {
  echo "Workspace not found!"
  exit 1
}

# 编译工作空间（先编译，再source）
echo "开始编译..."
colcon build 2>> $LOG_FILE
if [ $? -ne 0 ]; then
  echo "colcon build failed!" >> $LOG_FILE
  exit 1
fi

# 加载编译后的环境
source install/setup.bash

# 启动launch
echo "启动机器人项目..."
exec $LAUNCH_COMMAND >> $LOG_FILE 2>&1
