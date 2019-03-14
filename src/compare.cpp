#include <cmath> 
#include <stdio.h>
#include <stdlib.h> 
#include "ros/ros.h"
#include <string>
#include <iostream>
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>

ros::Publisher pub;
geometry_msgs::Point p_x;
geometry_msgs::Point pos;

void callback(const nav_msgs::Odometry& msg)
{ 
  p_x.x = msg.pose.pose.position.x;
}

void encoder_callback(nav_msgs::Odometry msg2)
{
  pos.x = std::abs( p_x.x) - std::abs( msg2.pose.pose.position.x);

  std::cout << "True localization pose x : " << p_x.x <<"\n";
  std::cout << "Fake localization pose x : " << msg2.pose.pose.position.x << "\n" ;
  std::cout << "Diff at pose x : " << pos.x << "\n";
  if (std::abs(pos.x) > 0.21){
    ROS_WARN("Don't do it");
    }
    else {
        ROS_WARN("GOOOO");
    }
    pub.publish(pos);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "compare_position");
  ros::NodeHandle nh;
  ros::Subscriber sub1;
  ros::Subscriber sub2;

  std::string in_topic, out_topic;
  nh.param("out_topic", out_topic, std::string("pose_x/difference"));

  sub1 = nh.subscribe("/odometry/filtered", 1, callback);
  sub2 = nh.subscribe("/odometry/filtered/tests", 1, encoder_callback);

  pub = nh.advertise<geometry_msgs::Point> (out_topic, 1);

  ros::spin();

  return 0;
}
