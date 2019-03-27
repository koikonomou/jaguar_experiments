#include <cmath> 
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <navigation_srv/navigation_srv.h>


bool running = false ;
bool b = true;

ros::Publisher pub;
ros::Publisher vel_pub;

ros::NodeHandle *n;

ros::Subscriber sub1;
ros::Subscriber sub2;

geometry_msgs::Point p_x;
geometry_msgs::Point pos;


void callback(const nav_msgs::Odometry& msg)
{
  p_x.x = msg.pose.pose.position.x;
}

void encoder_callback(const nav_msgs::Odometry msg2)
{
  pos.x = std::abs( p_x.x) - std::abs( msg2.pose.pose.position.x);

  std::cout << "True localization pose x : " << p_x.x <<"\n";
  std::cout << "Fake localization pose x : " << msg2.pose.pose.position.x << "\n" ;
  std::cout << "Diff at pose x : " << pos.x << "\n";

  if (std::abs(pos.x) > 0.21 ){
    ROS_WARN("Don't do it");
    }
    else {
        ROS_WARN("GOOOO");
    }
    pub.publish(pos);
}


bool service_cl (navigation_srv::navigation_srv::Request &req , navigation_srv::navigation_srv::Response &res){
  if (req.command == 0 and running ){
    running = false ; 
    sub1.shutdown();
    sub2.shutdown();

  }
  else if (req.command == 1 and !running ){
    if ( !running ){
      sub1 = n->subscribe("/odometry/filtered", 1, callback);
      sub2 = n->subscribe("/odometry/filtered/tests", 1, encoder_callback);
      running = true ;
      ROS_WARN("Started comparing node ");
    }
  }
  res.answer = running;
  return true;

}

int main(int argc, char **argv)
{
  int rate_b = 1; 
  ros::init(argc, argv, "compare_position");
  ros::NodeHandle nh;
  n = &nh;

  std::string in_topic, out_topic, service_topic ;
  nh.param("out_topic", out_topic, std::string("pose_x/difference"));
  nh.param("service_topic", service_topic, std::string("/service/compare_position"));


  if ( running ){
    sub1 = nh.subscribe("/odometry/filtered", 1, callback);
    sub2 = nh.subscribe("/odometry/filtered/tests", 1, encoder_callback);
  }

  pub = nh.advertise<geometry_msgs::Point> (out_topic, 1);

  ros::ServiceServer service = nh.advertiseService(service_topic, service_cl);
  while (ros::ok){
    ros::spinOnce();
      if (b){
        ROS_WARN("Call rosservise with command: 1 to start node and command: 0 to shutdown");
        b = false;
      }
  }

  return 0;
}
