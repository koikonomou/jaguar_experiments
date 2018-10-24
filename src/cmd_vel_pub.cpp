#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include "std_msgs/String.h"
#include <sstream>

ros::Publisher pub;
float x, z;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "velocity");
    ros::NodeHandle nh;
    pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    nh.param("velocity/linear_x", x, 0.1f);
    nh.param("velocity/angular_z", z, 0.0f);
    // ros::Rate loop_rate(10);

    while (ros::ok()){
        geometry_msgs::Twist msg;
        msg.linear.x = x;
        msg.angular.z = z;
        pub.publish(msg);
        ros::spinOnce();
        // loop_rate.sleep();
    }

  return 0;

}