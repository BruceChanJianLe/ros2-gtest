#!/usr/bin/env python3

import os
import launch
import launch_ros
import launch_testing
import unittest


def generate_test_description():
    test_binary_dir_arg = launch.actions.DeclareLaunchArgument(name='TEST_DIR',
                                             description='Binary directory of package '
                                                         'containing test executables')

    source_dir_arg = launch.actions.DeclareLaunchArgument(name='SRC_DIR',
                                             description='Source directory of package '
                                                         'containing test files')

    pkg_name_arg = launch.actions.DeclareLaunchArgument(name='PKG_NAME',
                                             description='name of package')

    test_node = launch_ros.actions.Node(
        executable=launch.substitutions.PathJoinSubstitution(
            [launch.substitutions.LaunchConfiguration('TEST_DIR'), 'std_msgs_sub_test']
        ),
        output='screen',
        # prefix="kitty gdb -e run --args"
    )

    pub2_node = launch_ros.actions.Node(
        package=launch.substitutions.LaunchConfiguration('PKG_NAME'),
        executable='pub2_node',
        parameters=[launch.substitutions.PathJoinSubstitution([launch.substitutions.LaunchConfiguration('SRC_DIR'), 'config', 'std_msgs_sub_test.yaml'])],
        output='screen',
    )

    return launch.LaunchDescription([
        test_binary_dir_arg,
        pub2_node,
        test_node,
        launch_testing.actions.ReadyToTest()
    ]), {'test_node': test_node}

class TestGTestWaitForCompletion(unittest.TestCase):
    # Waits for test to complete, then waits a bit to make sure result files are generated
    def test_gtest_run_complete(self, test_node):
        self.proc_info.assertWaitForShutdown(test_node, timeout=4000.0)

@launch_testing.post_shutdown_test()
class TestGTestProcessPostShutdown(unittest.TestCase):

    def test_gtest_pass(self, proc_info, test_node):
        launch_testing.asserts.assertExitCodes(proc_info, process=test_node)