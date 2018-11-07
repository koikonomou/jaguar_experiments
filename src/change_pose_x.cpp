#include <sstream>
#include <cmath>
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>

ros::Publisher pub;

void callback(const nav_msgs::Odometry& msg){
    geometry_msgs::PoseWithCovarianceStamped ps;

    ps.header.stamp = msg.header.stamp;
    ps.header.frame_id = "odom";
    ps.pose.pose.position.x =  msg.pose.pose.position.x;
    ps.pose.pose.position.y = msg.pose.pose.position.y;
    ps.pose.pose.position.z = msg.pose.pose.position.z;
    ps.pose.pose.orientation.x = msg.pose.pose.orientation.x ;
    ps.pose.pose.orientation.y = msg.pose.pose.orientation.y ;
    ps.pose.pose.orientation.z = msg.pose.pose.orientation.z ;
    ps.pose.pose.orientation.w = msg.pose.pose.orientation.w ;
    ps.pose.covariance = msg.pose.covariance ;

    pub.publish(ps);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "change_pose_x");
    ros::NodeHandle nh;
    ros::Subscriber sub;

    sub = nh.subscribe("/odometry/filtered", 1, callback);
    pub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("/set_pose/tests", 1);
    ros::spin();

  return 0;

}