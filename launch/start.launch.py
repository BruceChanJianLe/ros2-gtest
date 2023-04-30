from launch import LaunchDescription
from launch_ros.actions import Node
# Launch Args
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
# Load Params Yaml
import os
from ament_index_python.packages import get_package_share_directory

ARGUMENTS = [
    DeclareLaunchArgument(
        'data',
        default_value='true',
        description='The data arguement, by default has value true',
    ),
    DeclareLaunchArgument(
        'rate',
        default_value='1',
        description='The double arguement, by default has value 1.0',
    ),
]

def generate_launch_description():
        # Launch args
        data = LaunchConfiguration('data')
        rate = LaunchConfiguration('rate')

        talker_node = Node(
            package='ros2-gtest',
            executable='pub2_node',
            name='pub2_node',
            parameters=[os.path.join(get_package_share_directory('ros2-gtest'), 'config', 'params.yaml')],
        )

        listener_node = Node(
            package='ros2-gtest',
            executable='sub2_node',
            name='sub2_node',
        )

        # Define launch description
        ld = LaunchDescription(ARGUMENTS)
        ld.add_action(talker_node)
        ld.add_action(listener_node)

        # Return launch description
        return ld