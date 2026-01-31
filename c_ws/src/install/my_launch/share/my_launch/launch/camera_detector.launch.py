import launch
import launch_ros
import os
from ament_index_python.packages import get_package_share_directory
def generate_launch_description():
    action_node_camera_publish = launch_ros.actions.Node(
        package='camera_publish',
        executable='camera_publish',
        output='log'
    )

    action_node_vision_detector = launch_ros.actions.Node(
        package='vision_detector',
        executable='vision_detector',
        output = 'both'

    )
    action_node_static_tf_publish = launch_ros.actions.Node(
        package='tf2_node',
        executable='static_tf_publish',
        output = 'log'
    )
    action_node_TFListener = launch_ros.actions.Node(
        package='tf2_node',
        executable='TFListener',
        output = 'log'
    )
    action_node_qt = launch_ros.actions.Node(
        package='tf2_node',
        executable='qtdispaly',
        output = 'screen'
    )
    rviz2_process = launch.actions.ExecuteProcess(
        cmd=['rviz2','-d',
             os.path.join(get_package_share_directory("my_launch"),
                          "config","image_processed.rviz")],
        output='screen',
        name='rviz2_image_viewer'
    )

    
    
   
    launch_description = launch.LaunchDescription([
        action_node_camera_publish,
        action_node_vision_detector,
        action_node_static_tf_publish,
        action_node_TFListener,
        action_node_qt,
        rviz2_process
    ])
    return launch_description