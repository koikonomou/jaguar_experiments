#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from sensor_msgs.msg import PointCloud2
from geometry_msgs.msg import Point

pub = None


def callback(msg):
    with open('testfile.txt', 'a') as file :
        file.write('{}\n'.format(msg.x))
        file.close()

# Initialization
def init():
    rospy.init_node('test')
    rospy.Subscriber("pose_x/difference", Point, callback)
    rospy.spin()

if __name__ == '__main__':
    init()

