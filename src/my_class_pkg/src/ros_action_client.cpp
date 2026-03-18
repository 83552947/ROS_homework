#include<ros/ros.h>
#include<actionlib/client/simple_action_client.h>
#include<actionlib/client/terminal_state.h>
#include<my_class_pkg/MyActionAction.h>
int main(int argc,char**argv){
	ros::init(argc,argv,"cre_client");
	ros::NodeHandle nh;
	actionlib::SimpleActionClient<my_class_pkg::MyActionAction> client("my_action",true);
	ROS_INFO("Waitingforactionservertostart...");
	client.waitForServer();
	my_class_pkg::MyActionGoal goal;
	goal.object_name="world";
	ROS_INFO("Sendinggoal...");
	client.sendGoal(goal);
	bool finished_before_timeout=client.waitForResult(ros::Duration(30.0));
	if (finished_before_timeout){
		actionlib::SimpleClientGoalState state=client.getState();
		ROS_INFO("Actionfinished:%s",state.toString().c_str());
	}else{
		ROS_INFO("Actiondidnotfinishbeforethetimeout.");
	}
	return 0;
}
