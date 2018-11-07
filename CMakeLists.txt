cmake_minimum_required(VERSION 2.8.3)
project(jaguar_experiments)

find_package(catkin REQUIRED 
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  sensor_msgs)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS})

add_executable(cmd_vel_pub src/cmd_vel_pub.cpp)
target_link_libraries(cmd_vel_pub ${catkin_LIBRARIES})

add_executable(compare src/compare.cpp)
target_link_libraries(compare ${catkin_LIBRARIES})

add_executable(change_pose_x src/change_pose_x.cpp)
target_link_libraries(change_pose_x ${catkin_LIBRARIES})