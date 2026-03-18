#include"ros/ros.h"
#include"my_class_pkg/MyServiceMsgRequest.h"
#include"my_class_pkg/MyServiceMsgResponse.h"
#include"my_class_pkg/MyServiceMsg.h"
bool myServiceCallback(my_class_pkg::MyServiceMsgRequest&req,my_class_pkg::MyServiceMsgResponse&res){
	res.output=req.input*2;
	ROS_INFO("Request: input=%d,output=%d",req.input,res.output);
	return true;
}
int main(int argc,char** argv){
	ros::init(argc,argv,"my_service_node");
	ros::NodeHandle nh;
	ros::ServiceServer service=nh.advertiseService("my_service",myServiceCallback);
	ROS_INFO("Readytoreceiveservicerequests.");
 	ros::spin();
	return 0;
}
