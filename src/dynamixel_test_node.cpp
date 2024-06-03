#include <dynamixel_test/dynamixel_test.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "dynamixel_test_node");
  DynamixelTest dynamixel_test;
  dynamixel_test.process();
  return 0;
}