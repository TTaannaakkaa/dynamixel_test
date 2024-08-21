#ifndef DYNA_TEST_H
#define DYNA_TEST_H

#include <ros/ros.h>
#include <sq2_ccv_roll_pitch_msgs/RollPitch.h>
#include <dynamixel_workbench_msgs/DynamixelStateList.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <math.h>

class DynamixelTest
{
public:
  DynamixelTest();

  void process();

private:
  void RollPitchCallback(const sq2_ccv_roll_pitch_msgs::RollPitch::ConstPtr &msg);

  double roll_to_rad(double roll);

  double HZ_;
  bool is_roll_pitch_received_;
  bool is_use_joy_;
  std::string file_name_;

  ros::NodeHandle nh_;
  ros::NodeHandle private_nh_;
  ros::Subscriber roll_pitch_sub_;
  ros::Publisher dynamixel_cmd_pub_;

  sq2_ccv_roll_pitch_msgs::RollPitch roll_pitch_msg_;
  trajectory_msgs::JointTrajectory dynamixel_cmd_;

};

#endif // DYNA_TEST_H