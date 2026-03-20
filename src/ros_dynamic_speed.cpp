#include <ros/ros.h>  
#include <dynamic_reconfigure/server.h> 
#include <my_class_pkg/TutorialsConfig.h> 
#include <geometry_msgs/Twist.h> 
double robot_speed = 0;
void callback(my_class_pkg::TutorialsConfig &config, uint32_t level) 
{ 
ROS_INFO("Reconfigure Request: %d %f %s %s %d", 
	config.int_param, config.double_param, 
	config.str_param.c_str(), 
	config.bool_param?"True":"False", 
	config.size); 
robot_speed = config.double_param; 
} 
int main(int argc, char **argv) 
{ 
	ros::init(argc, argv, "dynamic_tutorials"); 
	ros::NodeHandle(nh); 
	dynamic_reconfigure::Server<my_class_pkg::TutorialsConfig> server; 
	dynamic_reconfigure::Server<my_class_pkg::TutorialsConfig>::CallbackType f; 
	ros::Publisher cmd_pub_ = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10); 
	f = boost::bind(&callback, _1, _2); 
	server.setCallback(f); 
	ROS_INFO("Spinning node"); ros::Rate rate(10); 
	while(ros::ok()) 
	{ 
		geometry_msgs::Twist cmd_vel; 
		cmd_vel.linear.x = robot_speed; 
		cmd_pub_.publish(cmd_vel); 
		ros::spinOnce(); 
		rate.sleep(); 
	} 
return 0; 
}
