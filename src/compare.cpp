#include <cmath> 
#include <stdio.h>
#include <stdlib.h> 
#include "ros/ros.h"
#include <string>
#include <iostream>
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>

// ros::Publisher pub;
geometry_msgs::Point p_x;

void callback(const nav_msgs::Odometry& msg)
{ 
  p_x.x = msg.pose.pose.position.x;
}

void encoder_callback(nav_msgs::Odometry msg2)
{
  geometry_msgs::Point pos;
  pos.x = p_x.x - msg2.pose.pose.position.x;

  std::cout << "True localization pose x : " << p_x.x <<"\n";
  std::cout << "Fake localization pose x : " << msg2.pose.pose.position.x << "\n" ;
  std::cout << "Diff at pose x : " << pos.x << "\n";


}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "compare_position");
  ros::NodeHandle nh;
  ros::Subscriber sub1;
  ros::Subscriber sub2;

  sub1 = nh.subscribe("/odometry/filtered", 1, callback);
  sub2 = nh.subscribe("/odometry/filtered/tests", 1, encoder_callback);

  ros::spin();

  return 0;
}
