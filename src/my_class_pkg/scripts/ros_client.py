#!/usr/bin/env python3
import rospy
from my_class_pkg.srv import MyServiceMsg
rospy.init_node("my_service_client")
rospy.wait_for_service("my_service")
client=rospy.ServiceProxy("my_service",MyServiceMsg)
try:
	resp=client.call(2)
	rospy.loginfo("Serviceresponse:%d",resp.output)
except rospy.ServiceException as e:
	rospy.logerr("Servicecall failed:%s",e)
