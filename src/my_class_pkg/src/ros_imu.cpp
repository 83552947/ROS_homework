#include<ros/ros.h>
#include<sensor_msgs/Imu.h>
void imu_callback(const sensor_msgs::Imu::ConstPtr& imu_msg){
geometry_msgs::Vector3 linear_acceleration=imu_msg->linear_acceleration;
geometry_msgs::Vector3 angular_velocity=imu_msg->angular_velocity;
geometry_msgs::Quaternion orientation=imu_msg->orientation;
ROS_INFO("Linear acceleration: x=%f, y=%f, z=%f", linear_acceleration.x,linear_acceleration.y,linear_acceleration.z);
ROS_INFO("Angular velocity: x=%f, y=%f, z=%f", angular_velocity.x,angular_velocity.y,angular_velocity.z);
ROS_INFO("Orientation: x=%f, y=%f, z=%f, w=%f", orientation.x, orientation.y,orientation.z,orientation.w);
}
int main(int argc,char** argv){
ros::init(argc,argv,"imu_listener");
ros::NodeHandle nh;
ros::Subscriber imu_sub = nh.subscribe<sensor_msgs::Imu>("/imu/data", 10,
imu_callback);
ros::spin();
return 0;
}
