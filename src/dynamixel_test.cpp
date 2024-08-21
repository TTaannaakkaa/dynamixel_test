#include <dynamixel_test/dynamixel_test.h>

DynamixelTest::DynamixelTest(void) : private_nh_("~")
{
  private_nh_.param<double>("hz", HZ_, 10.0);
  private_nh_.param<bool>("is_use_joy", is_use_joy_, true);
  private_nh_.param("file_name", file_name_, std::string("roll_pitch.csv"));

  is_roll_pitch_received_ = true;

  roll_pitch_sub_ = nh_.subscribe("/roll_pitch", 1, &DynamixelTest::RollPitchCallback, this);
  dynamixel_cmd_pub_ = nh_.advertise<trajectory_msgs::JointTrajectory>("dynamixel_workbench/joint_trajectory", 1);

  dynamixel_cmd_.joint_names.resize(1);
  dynamixel_cmd_.points.resize(1);
  dynamixel_cmd_.points[0].positions.resize(1);
  dynamixel_cmd_.points[0].velocities.resize(1);
  dynamixel_cmd_.points[0].accelerations.resize(1);

  dynamixel_cmd_.joint_names[0] = "Motor10";
  dynamixel_cmd_.points[0].positions[0] = M_PI / 2.0;
  dynamixel_cmd_.points[0].velocities[0] = 0.0;
  dynamixel_cmd_.points[0].accelerations[0] = 0.0;
  dynamixel_cmd_.points[0].time_from_start = ros::Duration(0.1);
}

void DynamixelTest::process()
{
  ros::Rate loop_rate(HZ_);
  FILE *fp;
  fp = fopen(file_name_.c_str(), "w");
  double roll = M_PI / 2.0;
  double time = 0.1;

  while (ros::ok())
  {
    if (is_roll_pitch_received_ )
    {
      if(is_use_joy_) {
        roll = roll_to_rad(roll_pitch_msg_.roll);
        // ROS_INFO_STREAM("Roll: " << roll);
        dynamixel_cmd_.points[0].positions[0] = roll;
      }
      else {
        roll = roll_to_rad(M_PI/18.0 * sin(time)); 
        // ROS_INFO_STREAM("Roll: " << roll);
        dynamixel_cmd_.points[0].positions[0] = roll;
        time += 0.1;
      }
      dynamixel_cmd_.header.stamp = ros::Time::now();
      double time = ros::Time::now().toSec();
      fprintf(fp, "%lf, %f, %f\n", time, roll_pitch_msg_.roll, dynamixel_cmd_.points[0].positions[0]);
      dynamixel_cmd_pub_.publish(dynamixel_cmd_);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
}

void DynamixelTest::RollPitchCallback(const sq2_ccv_roll_pitch_msgs::RollPitch::ConstPtr &msg)
{
  roll_pitch_msg_ = *msg;
  is_roll_pitch_received_ = true;
}

double DynamixelTest::roll_to_rad(double roll)
{
  double roll_angle = roll + M_PI / 2.0;
  if (roll_angle > M_PI)
  {
    roll_angle -= 2*M_PI;
  }
  return roll_angle;
}


  