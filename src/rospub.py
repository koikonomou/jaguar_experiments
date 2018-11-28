#!/usr/bin/env python
import rospy
import roslib
import time 
import rosbag
import genpy
from std_msgs.msg import Int32 , String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Quaternion , Twist


pub1 = None

# Initialization
def init():
    # global pub
    rospy.init_node('rospub')

    pub1 = rospy.Publisher("/cmd_vel", Twist, queue_size=1)

    test_msg = Twist()
    test_msg.linear.x = 0.3
    test_msg.linear.y = 0.0
    test_msg.linear.z = 0.0
    # rate = rospy.Rate(10)
    # while not rospy.is_shutdown():
    timeout = 0.3
    timeout_start = time.time() 
    while time.time() < timeout_start + timeout:
        pub1.publish(test_msg)
        # rate.sleep()
    rospy.spin()

if __name__ == '__main__':
    init()
