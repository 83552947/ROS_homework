#!/usr/bin/env python3
import rospy
import actionlib
from my_class_pkg.msg
import MyActionAction,MyActionGoal,MyActionResult,MyActionFeedback
def feedback_cb(feedback):
rospy.loginfo('Progress:{}'.format(feedback.progress))
if __name__=='__main__':
rospy.init_node('my_client')
client=actionlib.SimpleActionClient('my_action',MyActionAction)
client.wait_for_server()
goal=MyActionGoal()
goal.object_name='world'
rospy.loginfo('Sendinggoal...')
client.send_goal(goal,feedback_cb=feedback_cb)
client.wait_for_result()
result=client.get_result()
if result.success:
rospy.loginfo('Actionsucceeded')
else:
rospy.loginfo('Actionfailed')
