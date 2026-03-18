#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_datatypes.h>
#include <cmath>
ros::Publisher vel_pub;        
geometry_msgs::Twist cmd_vel;    
double init_yaw = 0.0;         
double current_yaw = 0.0;      
bool is_rotating = false;       
const double TARGET_ANGLE = M_PI; 
const double ANGLE_THRESHOLD = 0.035;
const double ROTATE_SPEED = 0.5;  
double quaternion2yaw(const sensor_msgs::Imu::ConstPtr& imu_msg)
{
    tf::Quaternion quat;
    tf::quaternionMsgToTF(imu_msg->orientation, quat);
    double roll, pitch, yaw;
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
    return yaw;
}
void imu_callback(const sensor_msgs::Imu::ConstPtr& imu_msg)
{
    current_yaw = quaternion2yaw(imu_msg);
    if (!is_rotating)
    {
        init_yaw = current_yaw;
        is_rotating = true;
        ROS_INFO("自旋开始，初始偏航角：%.2f rad", init_yaw);
        cmd_vel.linear.x = 0.0;
        cmd_vel.linear.y = 0.0;
        cmd_vel.linear.z = 0.0;
        cmd_vel.angular.x = 0.0;
        cmd_vel.angular.y = 0.0;
        cmd_vel.angular.z = ROTATE_SPEED;
    }
    double delta_yaw = current_yaw - init_yaw;
    delta_yaw = atan2(sin(delta_yaw), cos(delta_yaw)); 
    double abs_delta = fabs(delta_yaw);
    ROS_INFO("当前偏航角：%.2f rad，已旋转：%.2f rad，目标：%.2f rad",
             current_yaw, abs_delta, TARGET_ANGLE);
    if (abs_delta >= TARGET_ANGLE - ANGLE_THRESHOLD)
    {
        cmd_vel.angular.z = 0.0; 
        vel_pub.publish(cmd_vel);
        ROS_INFO("自旋完成！实际旋转角度：%.2f rad（≈%.1f°）",
                 abs_delta, abs_delta * 180 / M_PI);
        ros::shutdown();
    }
    vel_pub.publish(cmd_vel);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "imu_spin_controller");
    ros::NodeHandle nh;
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Subscriber imu_sub = nh.subscribe<sensor_msgs::Imu>("/imu/data", 10, imu_callback);
    ROS_INFO("IMU自旋控制节点已启动，等待IMU数据...");
    ros::spin();
    return 0;
}
